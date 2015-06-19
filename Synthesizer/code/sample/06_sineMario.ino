#include "pitches.h"
#define SPEAKER_PIN 9
// 440Hzの音を出す

const unsigned char sineTable[] = {
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
    pinMode(SPEAKER_PIN, OUTPUT);
    TCCR1B = 0x01;
}


void loop()
{
    // 音の高さを決める
    int delayTime = (1000000 / NOTE_E4) / 256;

    // 音の長さを決める
    int soundTime = (250000) / (delayTime*128);

    // テンポ調整
    float tempo = 0.2;

    // マリヲのスタート
    // ミ ミッ ミッ ドミッ ソ ソ

    // ミ
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(10);

    // ミ
    delayTime = (1000000 / NOTE_E4) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(125);

    // ミ
    delayTime = (1000000 / NOTE_E4) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(125);

    // ド
    delayTime = (1000000 / NOTE_C4) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    // ミ
    delayTime = (1000000 / NOTE_E4) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(125);
    // ソ
    delayTime = (1000000 / NOTE_G4) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(400);
    // ソ
    delayTime = (1000000 / NOTE_G3) / 256;
    soundTime = (250000) / (delayTime*128);
    for(int i=0; i<soundTime*tempo; i++){
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);  
        }
        for(int j=0; j<255; j++){
            analogWrite(SPEAKER_PIN, (sineTable[j]));
            delayMicroseconds(delayTime);
        }
    }
    delay(1000);
}


