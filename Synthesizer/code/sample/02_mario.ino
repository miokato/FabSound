#include "pitches.h"
#define SPEAKER_PIN 9
// 440Hzの音を出す


void setup(){
    pinMode(SPEAKER_PIN, OUTPUT);
}


void loop()
{
    // 音の高さを決める
    int delayTime = (1000000 / NOTE_E4) / 2;

    // 音の長さを決める
    int soundTime = (250000) / (delayTime*2);

    // テンポ調整
    float tempo = 0.5;

    // マリヲのスタート
    // ミ ミッ ミッ ドミッ ソ ソ

    // ミ
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(10);

    // ミ
    delayTime = (1000000 / NOTE_E4) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(125);

    // ミ
    delayTime = (1000000 / NOTE_E4) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(125);

    // ド
    delayTime = (1000000 / NOTE_C4) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }

    // ミ
    delayTime = (1000000 / NOTE_E4) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(125);

    // ソ
    delayTime = (1000000 / NOTE_G4) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(400);

    // ソ
    delayTime = (1000000 / NOTE_G3) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(1000);
}


