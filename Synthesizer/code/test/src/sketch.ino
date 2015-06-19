// Simple Sound Oscillator

// digital pins
#define SPEAKER_PIN 3
#define SW_PIN 2

// analog pins
#define SEQ_POT1 A0
#define SEQ_POT2 A1
#define SEQ_POT3 A2
#define SEQ_POT4 A3

// step count
int stp_cnt;

// change bpm using pot.
int tmp_bpm;

// tables
int frequencies[] = {
    261,293,329,349,392,440,493,543
};
int signTable[] = {
  128,131,134,137,140,143,146,150,153,156,159,162,165,168,170,173,176,179,182,185,187,190,193,195,198,
  201,203,206,208,210,213,215,217,219,221,223,225,227,229,231,233,234,236,238,239,241,242,243,244,246,
  247,248,249,249,250,251,252,252,253,253,253,254,254,254,254,254,254,254,253,253,253,252,252,251,250,
  249,249,248,247,246,244,243,242,241,239,238,236,234,233,231,229,227,225,223,221,219,217,215,213,210,
  208,206,203,201,198,195,193,190,187,185,182,179,176,173,170,168,165,162,159,156,153,150,146,143,140,
  137,134,128,125,122,119,116,113,110,106,103,100, 97, 94, 91, 88, 86, 83, 80, 77, 74, 71, 69, 66, 63,
  61, 58, 55, 53, 50, 48, 46, 43, 41, 39, 37, 35, 33, 31, 29, 27, 25, 23, 22, 20, 18, 17, 15, 14, 13,
  12, 10,  9,  8,  7,  7,  6,  5,  4,  4,  3,  3,  3,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  4,  4,
  5,  6,  7,  7,  8,  9, 10, 12, 13, 14, 15, 17, 18, 20, 22, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41,
  43, 46, 48, 50, 53, 55, 58, 61, 63, 66, 69, 71, 74, 77, 80, 83, 86, 88, 91, 94, 97,100,103,106,110,
  113,116,119,122,125,127
};

void setup(){
    // for debug
    Serial.begin(9600);

    // init
    stp_cnt = 0;
    tmp_bpm = 100;
    pinMode(SW_PIN, INPUT);

    // set frequency 32kHz
    TCCR1B = 0x01;
}


void loop(){

    boolean sw;

    int freq1;
    int freq2;
    int freq3;
    int freq4;
    int freq5;
    int freq6;
    int freq7;
    int freq8;

    // get value from pot, and adjust value.
    int rowVal1 = analogRead(SEQ_POT1);
    int tuneVal1 = map(rowVal1, 0, 1023, 0, 255);
    int rowVal2 = analogRead(SEQ_POT2);
    int tuneVal2 = map(rowVal2, 0, 1023, 0, 255);
    int rowVal3 = analogRead(SEQ_POT3);
    int tuneVal3 = map(rowVal3, 0, 1023, 0, 255);
    int rowVal4 = analogRead(SEQ_POT4);
    int tuneVal4 = map(rowVal4, 0, 1023, 0, 255);

    sw = digitalRead(SW_PIN);

    // if you change sw, you can select to set value 1-4 or 5-8 step.
    if(sw==false){
        freq1 = signTable[tuneVal1];
        freq2 = signTable[tuneVal2];
        freq3 = signTable[tuneVal3];
        freq4 = signTable[tuneVal4];
    }
    if(sw==true){
        freq5 = signTable[tuneVal1];
        freq6 = signTable[tuneVal2];
        freq7 = signTable[tuneVal3];
        freq8 = signTable[tuneVal4];
    }

    // show parameter about all steps.
    Serial.print(freq1);
    Serial.print(" : ");
    Serial.print(freq2);
    Serial.print(" : ");
    Serial.print(freq3);
    Serial.print(" : ");
    Serial.print(freq4);
    Serial.print(" : ");
    Serial.print(freq5);
    Serial.print(" : ");
    Serial.print(freq6);
    Serial.print(" : ");
    Serial.print(freq7);
    Serial.print(" : ");
    Serial.print(freq8);
    Serial.println();
    

    switch(stp_cnt){
        case 0:
            tone(9, freq1);
            break;
        case 1:
            tone(9, freq2);
            break;
        case 2:
            tone(9, freq3);
            break;
        case 3:
            tone(9, freq4);
            break;
        case 4:
            tone(9, freq5);
            break;
        case 5:
            tone(9, freq6);
            break;
        case 6:
            tone(9, freq7);
            break;
        case 7:
            tone(9, freq8);
            break;
    }

    tmp_bpm = analogRead(A4);

    if(stp_cnt>=7)stp_cnt=0;
    stp_cnt++;
    delay(tmp_bpm);
}

