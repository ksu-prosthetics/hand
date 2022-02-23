#include <Servo.h>

#define button 30
#define servoPin 36

Servo servo;
int micro;
bool cw;


void setup(){
    servo.attach(36);
    pinMode(button, INPUT);
    micro = 0;
    cw = false;
}

void loop(){
    if (micro < 2400 && cw){
        micro += 100;
    }
    if (micro >= 2400 && cw){
        cw = !cw;
        micro -= 100;
    }
    else if (micro > 0 && !cw){
        micro -= 100;
    }
    else if (micro <= 0 && !cw){
        cw = !cw;
        micro += 100;
    }
    servo.writeMicroseconds(micro);
    delay(200);
}