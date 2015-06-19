// Auduino, the Lo-Fi granular synthesiser
//
// by Peter Knight, Tinker.it http://tinker.it
//
// Help:      http://code.google.com/p/tinkerit/wiki/Auduino
// More help: http://groups.google.com/group/auduino
//
// Analog in 0: Grain 1 pitch
// Analog in 1: Grain 2 decay
// Analog in 2: Grain 1 decay
// Analog in 3: Grain 2 pitch
// Analog in 4: Grain repetition frequency
//
// Digital 3: Audio out (Digital 11 on ATmega8)
//
// Changelog:
// 19 Nov 2008: Added support for ATmega8 boards
// 21 Mar 2009: Added support for ATmega328 boards
// 7 Apr 2009: Fixed interrupt vector for ATmega328 boards
// 8 Apr 2009: Added support for ATmega1280 boards (Arduino Mega)
// 8 July 2009: Mod'ed for Prototypers. By Takao Takahashi.

#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t syncPhaseAcc;
uint16_t syncPhaseInc;
uint16_t grainPhaseAcc;
uint16_t grainPhaseInc;
uint16_t grainAmp;
uint8_t grainDecay;
uint16_t grain2PhaseAcc;
uint16_t grain2PhaseInc;
uint16_t grain2Amp;
uint8_t grain2Decay;

uint8_t  stp_cnt;

// Map Analogue channels
#define SYNC_CONTROL         (4) // For ribbon controler(SoftPot)
#define GRAIN_FREQ_CONTROL   (0)
#define GRAIN_DECAY_CONTROL  (2)
#define GRAIN2_FREQ_CONTROL  (1)
#define GRAIN2_DECAY_CONTROL (3)
#define FUNC_SELECTOR        (5)

// Sequencer Steps.
#define  SEQ_STP1            12
#define  SEQ_STP2            11
#define  SEQ_STP3            10
#define  SEQ_STP4            9
#define  SEQ_STP5            8
#define  SEQ_STP6            7
#define  SEQ_STP7            6
#define  SEQ_STP8            5

#define  BPM_SEL              2
#define  SCL_SEL              4

// Changing these will also requires rewriting audioOn()

#if defined(__AVR_ATmega8__)
//
// On old ATmega8 boards.
//    Output is on pin 11
//
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       5
#define PWM_PIN       11
#define PWM_VALUE     OCR2
#define PWM_INTERRUPT TIMER2_OVF_vect
#elif defined(__AVR_ATmega1280__)
//
// On the Arduino Mega
//    Output is on pin 3
//
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       7
#define PWM_PIN       3
#define PWM_VALUE     OCR3C
#define PWM_INTERRUPT TIMER3_OVF_vect
#else
//
// For modern ATmega168 and ATmega328 boards
//    Output is on pin 3
//
#define PWM_PIN       3
#define PWM_VALUE     OCR2B
#define LED_PIN       13
#define LED_PORT      PORTB
#define LED_BIT       5
#define PWM_INTERRUPT TIMER2_OVF_vect
#endif

// Smooth logarithmic mapping
//

uint16_t antilogTable[] = {
  64830,64132,63441,62757,62081,61413,60751,60097,59449,58809,58176,57549,56929,56316,55709,55109,
  54515,53928,53347,52773,52204,51642,51085,50535,49991,49452,48920,48393,47871,47356,46846,46341,
  45842,45348,44859,44376,43898,43425,42958,42495,42037,41584,41136,40693,40255,39821,39392,38968,
  38548,38133,37722,37316,36914,36516,36123,35734,35349,34968,34591,34219,33850,33486,33125,32768
};
uint16_t mapPhaseInc(uint16_t input) {
  return (antilogTable[input & 0x3f]) >> (input >> 6);
}

uint16_t midiTable[] = {
// Caution: 1st actual data is 17, but 0 for note off data here.
// C     C#    D     D#    E     F     F#    G     G#    A     A#    B
    0,   18,   19,   20,   22,   23,   24,   26,   27,   29,   31,   32, //0
   34,   36,   38,   41,   43,   46,   48,   51,   54,   58,   61,   65, //12
   69,   73,   77,   82,   86,   92,   97,  103,  109,  115,  122,  129, //24
  137,  145,  154,  163,  173,  183,  194,  206,  218,  231,  244,  259, //36
  274,  291,  308,  326,  346,  366,  388,  411,  435,  461,  489,  518, //48
  549,  581,  616,  652,  691,  732,  776,  822,  871,  923,  978, 1036, //60
 1097, 1163, 1232, 1305, 1383, 1465, 1552, 1644, 1742, 1845, 1955, 2071, //72
 2195, 2325, 2463, 2610, 2765, 2930, 3104, 3288, 3484, 3691, 3910, 4143, //84
 4389, 4650, 4927, 5220, 5530, 5859, 6207, 6577, 6968, 7382, 7821, 8286, //96
 8779, 9301, 9854,10440,11060,11718,12415,13153,13935,14764,15642,16572, //108
 17557,18601,19708,20879,22121,23436,24830,26306
};

uint16_t mapMidi(uint16_t input) {
  return (midiTable[(input) >> 3]);
}

uint16_t octaveTable[] = {
  0,12,24,48,60,72,84,96,108
};

uint16_t minPentaTable[] = {
   0,  3,  5,  7, 10,
  12, 15, 17, 19, 22,
  24, 27, 29, 31, 34,
  36, 39, 41, 43, 46,
  48, 51, 53, 55, 58,
  60, 63, 65, 67, 70,
  72, 75, 77, 79, 82,
  84, 87, 89, 91, 94,
  96
};

uint16_t majPentaTable[] = {
    0,  2,  4,  7,  9,
   12, 14, 16, 19, 21,
   24, 26, 28, 31, 33,
   36, 38, 40, 43, 45,
   48, 50, 52, 55, 57,
   60, 62, 64, 67, 69,
   72, 74, 76, 79, 81,
   84, 86, 88, 91, 93,
   96
};

uint16_t RyukyuTable[55] = {
    0,  4,  5,  7, 11,
   12, 16, 17, 19, 23,
   24, 28, 29, 31, 35,
   36, 40, 41, 43, 47,
   48, 52, 53, 55, 59,
   60, 64, 65, 67, 71,
   72, 76, 77, 79, 83,
   84, 88, 89, 91, 95,
   96
};

uint16_t ChromaTable[73] = {
    0, 
    24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71,
    72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83,
    84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
};

uint8_t SelectTable[]={0,1,2,3,4,5,6,7,8,9,10,11,12};


uint16_t ScaleSelect(uint16_t input) {
  uint8_t value = (input) / (1024/5);
  return (SelectTable[value]);
}

uint16_t mapOctave(uint16_t input) {
  uint8_t value = (input) / (1024/11);
  return(octaveTable[value]);
}

uint16_t mapMinPenta(uint16_t input) {
  uint8_t value = (input) / (1024/40);
  return(minPentaTable[value]);
}

uint16_t mapMajPenta(uint16_t input) {
  uint8_t value = (input) / (1024/40);
  return (majPentaTable[value]);
}

uint16_t mapRyukyu(uint16_t input) {
  uint8_t value = (input) / (1024/40);
  return(RyukyuTable[value]);
}

uint16_t mapChromatic(uint16_t input) {
  uint8_t value = (input) / (1024/74);
  return(ChromaTable[value]);
}

void audioOn() {
#if defined(__AVR_ATmega8__)
  // ATmega8 has different registers
  TCCR2 = _BV(WGM20) | _BV(COM21) | _BV(CS20);
  TIMSK = _BV(TOIE2);
#elif defined(__AVR_ATmega1280__)
  TCCR3A = _BV(COM3C1) | _BV(WGM30);
  TCCR3B = _BV(CS30);
  TIMSK3 = _BV(TOIE3);
#else
  // Set up PWM to 31.25kHz, phase accurate
  TCCR2A = _BV(COM2B1) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  TIMSK2 = _BV(TOIE2);
#endif
}


void setup() {
  stp_cnt = 0;
  pinMode(BPM_SEL,OUTPUT);
  pinMode(SCL_SEL,OUTPUT);
  pinMode(PWM_PIN,OUTPUT);
  pinMode(SEQ_STP1,OUTPUT);
  pinMode(SEQ_STP2,OUTPUT);
  pinMode(SEQ_STP3,OUTPUT);
  pinMode(SEQ_STP4,OUTPUT);
  pinMode(SEQ_STP5,OUTPUT);
  pinMode(SEQ_STP6,OUTPUT);
  pinMode(SEQ_STP7,OUTPUT);
  pinMode(SEQ_STP8,OUTPUT);
  audioOn();
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
    uint16_t  tmp_midi_note;  
    uint16_t  tmp_read = analogRead(SYNC_CONTROL);
    
    //Read Scale selector
    digitalWrite(BPM_SEL,LOW);
    digitalWrite(SCL_SEL, HIGH);
    uint8_t  tmp_scale = ScaleSelect(analogRead(FUNC_SELECTOR));
    
    //Read BMP Data
    digitalWrite(SCL_SEL,LOW);
    digitalWrite(BPM_SEL,HIGH);
    uint16_t tmp_bpm = analogRead(FUNC_SELECTOR);
   
  switch(tmp_scale){
     case  0:
       tmp_midi_note = mapMajPenta(tmp_read);
       break;
     case  1:
       tmp_midi_note = mapMinPenta(tmp_read);
       break;
     case  2:
       tmp_midi_note = mapRyukyu(tmp_read);
       break;
     case  3:
       tmp_midi_note = mapOctave(tmp_read);
       break;
     case  4:
       tmp_midi_note = mapChromatic(tmp_read);
     default:
     break;
  }
  syncPhaseInc = midiTable[tmp_midi_note];

  grainPhaseInc  = mapPhaseInc(analogRead(GRAIN_FREQ_CONTROL)) / 2;
  grainDecay     = analogRead(GRAIN_DECAY_CONTROL) / 8;
  grain2PhaseInc = mapPhaseInc(analogRead(GRAIN2_FREQ_CONTROL)) / 2;
  grain2Decay    = analogRead(GRAIN2_DECAY_CONTROL) / 4;
  
  //Seqencer stepping.
  digitalWrite(SEQ_STP1,LOW);
  digitalWrite(SEQ_STP2,LOW);
  digitalWrite(SEQ_STP3,LOW);
  digitalWrite(SEQ_STP4,LOW);
  digitalWrite(SEQ_STP5,LOW);
  digitalWrite(SEQ_STP6,LOW);
  digitalWrite(SEQ_STP7,LOW);
  digitalWrite(SEQ_STP8,LOW);
  
  stp_cnt = stp_cnt & 0x07;
  switch(stp_cnt){
    case  0:
      digitalWrite(SEQ_STP1,HIGH);
      break;
    case  1:
      digitalWrite(SEQ_STP2,HIGH);
      break;
    case  2:
      digitalWrite(SEQ_STP3,HIGH);
      break;
    case  3:
      digitalWrite(SEQ_STP4,HIGH);
      break;
    case  4:
      digitalWrite(SEQ_STP5,HIGH);
      break;
    case  5:
      digitalWrite(SEQ_STP6,HIGH);
      break;
    case  6:
      digitalWrite(SEQ_STP7,HIGH);
      break;
    case  7:
      digitalWrite(SEQ_STP8,HIGH);
      break;
  }

  stp_cnt++;
  
  delay(tmp_bpm);
}

SIGNAL(PWM_INTERRUPT)
{
  uint8_t value;
  uint16_t output;

  syncPhaseAcc += syncPhaseInc;
  if (syncPhaseAcc < syncPhaseInc) {
    // Time to start the next grain
    grainPhaseAcc = 0;
    grainAmp = 0x7fff;
    grain2PhaseAcc = 0;
    grain2Amp = 0x7fff;
    LED_PORT ^= 1 << LED_BIT; // Faster than using digitalWrite
  }
  
  // Increment the phase of the grain oscillators
  grainPhaseAcc += grainPhaseInc;
  grain2PhaseAcc += grain2PhaseInc;

  // Convert phase into a triangle wave
  value = (grainPhaseAcc >> 7) & 0xff;
  if (grainPhaseAcc & 0x8000) value = ~value;
  // Multiply by current grain amplitude to get sample
  output = value * (grainAmp >> 8);

  // Repeat for second grain
  value = (grain2PhaseAcc >> 7) & 0xff;
  if (grain2PhaseAcc & 0x8000) value = ~value;
  output += value * (grain2Amp >> 8);

  // Make the grain amplitudes decay by a factor every sample (exponential decay)
  grainAmp -= (grainAmp >> 8) * grainDecay;
  grain2Amp -= (grain2Amp >> 8) * grain2Decay;

  // Scale output to the available range, clipping if necessary
  output >>= 9;
  if (output > 255) output = 255;

  // Output to PWM (this is faster than using analogWrite)  
  PWM_VALUE = output;
}

