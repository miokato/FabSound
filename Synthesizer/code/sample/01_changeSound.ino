PEAKER_PIN 9

int durationTime = 100;

int d = 1;

void setup(){
    pinMode(SPEAKER_PIN, OUTPUT);
}


void loop()
{
    durationTime+=d;
    if(durationTime > 1000 || durationTime <= 1) d = -d;

    digitalWrite(SPEAKER_PIN, HIGH);
    delayMicroseconds(durationTime);
    digitalWrite(SPEAKER_PIN, LOW);
    delayMicroseconds(durationTime);
}

