//Header block
#include <Servo.h>
#define sensor1 A0
#define sensor2 A1
#define sensor3 A2
#define sensor4 A3
#define sensor5 A4
#define servo1Pin 2
#define servo2Pin 3
#define servo3Pin 4
#define servo4Pin 5
#define servo5Pin 6

//Global variables block
Servo servo1, servo2, servo3, servo4, servo 5;
int micro1, micro2, micro3, micro4, micro5;
int Xn4, Xn3, Xn2, Xn1, Xn0, Yn, count, T, t, i, j;
int DC_check[100] = {0};
const order = 4;

//Setup block
void setup(){
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    servo3.attach(servo3Pin);
    servo4.attach(servo4Pin);
    servo5.attach(servo5Pin);
    
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);
    pinMode(sensor5, INPUT);
    
    servo1.writeMicroseconds(micro1);
    servo2.writeMicroseconds(micro2);
    servo3.writeMicroseconds(micro3);
    servo4.writeMicroseconds(micro4);
    servo5.writeMicroseconds(micro5);
    
    Serial.begin(9600);
}

//Main
void loop() 
{
  //
  //**NOTES ON WHERE TO GO FORWARD**
  //
  //implement hard endpoints for servo control
  //   - Use test data from multiple different subjects
  //  and get a good feel for what a "full" contraction reads as
  //  that is then the hard endpoint.
  //
  //   - test for depolarizing value and if it dips below zero then
  //  any dip below zero can be considered a full relaxation of the hand.
  //implement soft endpoints
  //   - IE different zones that are associated with different flexion strengths
  //  to mimic the continuoum of force output that natural human
  //  muscles can.
  //do a gui
  
  //First time calibration to remove DC offset
  //consider making a function for when we add more servos
  if(DC_check[0] == 0)
  {
    T = millis();
    t = millis();
    while((millis() - T) < 5000)
    {
      if(millis() - t) >= 200)
      {
        t = millis();
        DC_check[i] = analogRead(sensor1);
        i++;
      }
    }
    for(j = 0; j < i; j++)
    {
      DC = DC + DC_check[j];
    }
    DC = DC / i;
  }

  //Data acquisition, printing, and updating with difference equation
  T = millis();
  Xn4 = Xn3;
  Xn3 = Xn2;
  Xn2 = Xn1;
  Xn1 = Xn0;
  Xn0 = analogRead(sensor1) - DC;
    //This difference equation is meant to emulate a third order low pass filter with a corner at 5hz and gain of 5
  Yn = 5*(Xn - 15*Xn1 + 75*Xn2 - 125*Xn3) / Xn3;
  Serial.println(Yn);
  while((millis()- T) < 10){}
}
