#include <Servo.h>

#define sensor A0
#define servoPin 2

Servo servo;
int micro;

void setup(){
    servo.attach(servoPin);
    pinMode(sensor, INPUT);
    micro = 0;
    servo.writeMicroseconds(micro);
}

void loop(){
    micro = analogRead(sensor);
    servo.writeMicroseconds(micro);
    delay(200);
}