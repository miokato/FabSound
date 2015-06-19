#include "pitches.h"

#define SPEAKER_PIN 9
#define SENSOR_PIN A0


void setup(){
    pinMode(SPEAKER_PIN, OUTPUT);
}


void loop()
{
    // 音の高さを決める
    int delayTime;
    // 音の長さを決める
    int soundTime;
    // テンポ調整
    float tempo = 0.3;

    // マリヲのスタート
    // ミ ミッ ミッ ドミッ ソ ソ

    // シ
    delayTime = (1000000 / NOTE_B6) / 2;
    soundTime = (250000) / (delayTime*2);
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(10);

    // ミ
    delayTime = (1000000 / NOTE_E7) / 2;
    soundTime = (250000) / (delayTime*2)*analogRead(SENSOR_PIN)/1023.0;
    for(int i=0; i<soundTime*tempo; i++){
        digitalWrite(SPEAKER_PIN, HIGH);
        delayMicroseconds(delayTime);
        digitalWrite(SPEAKER_PIN, LOW);
        delayMicroseconds(delayTime);
    }
    delay(10);

}


