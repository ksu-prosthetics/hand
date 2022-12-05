/*
This code allows reading from the mussles in the body wich becomes very noisy.
To read the data it use servopins to read the input 
it will transfer the pins to the global servo variables, and after that it will calculate the micros. 

*/
#include <Servo.h>

/*
This will define global varibles for sensors and servos 


A0-A3 are pins used for analoging the values and saving them 
Declares a servo global variable with its pin locations
*/
#define sensor1 A0
#define sensor2 A1
#define sensor3 A2
#define sensor4 A3

#define servo1Pin 2
#define servo2Pin 3
#define servo3Pin 4
#define servo4Pin 5

/*
Declares the actual objects that will used to control the electronic 
*/
Servo servo1;
Servo servo2;
Servo servo3;
//Servo servo4;


/*
Declares the 4 varibles in charge of saving calculations  
*/
int micro1;
int micro2;
int micro3;
int micro4;


void setup(){
    
    /*
    ServosPins is now having the the actual value based on the servo 
    */
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);
    servo3.attach(servo3Pin);
    //servo4.attach(servo4Pin);
    
    /*
    Reads input 
    */
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(sensor3, INPUT);
    pinMode(sensor4, INPUT);
    
    /*
    Intiallizes the micros
    */
    micro1 = 0;
    micro2 = 0;
    micro3 = 0;
    micro4 = 0;
    
    /*
    Writes output, should be zero 
    */
    servo1.writeMicroseconds(micro1);
    servo2.writeMicroseconds(micro2);
    servo3.writeMicroseconds(micro3);
    //servo4.writeMicroseconds(micro4);
    
    Serial.begin(9600);
}

void loop(){
    
    /*
    This allows the procram to compute the volatages for the micros
    */
    micro1 = (int)((float)analogRead(sensor1) * 3000.0 / 1023.0);
    servo1.writeMicroseconds(micro1);
    Serial.print(" micro 1= ");
    Serial.println(micro1);
   

      micro2= (int)((float)analogRead(sensor2) * 3000.0 / 1023.0);
    servo2.writeMicroseconds(micro2);
       Serial.print(" micro 2= ");
    Serial.println(micro2);
  
      micro3 = (int)((float)analogRead(sensor3) * 3000.0 / 1023.0);
    servo3.writeMicroseconds(micro3);
    Serial.print(" micro 3= ");
    Serial.println(micro3);
    
     //micro4 = (int)((float)analogRead(sensor4) * 3000.0 / 1023.0);
    //servo4.writeMicroseconds(micro4);
    //Serial.println(" micro 4= " + micro4);
delay(100);
}
