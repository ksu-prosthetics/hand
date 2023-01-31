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

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

int micro1;
int micro2;
int micro3;
int micro4;
int micro5;
const int NumReadings  = 3;
int readingsAvg[NumReadings] = {0};
int temp[NumReadings] = {0};
int count = 0;
int sum = 0;
int flexed = 0;
int lowerLim = 230
;
int upperLim = 300;
int raw = 0;


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
    
    micro1 = 0;
    micro2 = 0;
    micro3 = 0;
    micro4 = 0;
    micro5 = 0;
    
    servo1.writeMicroseconds(micro1);
    servo2.writeMicroseconds(micro2);
    servo3.writeMicroseconds(micro3);
    servo4.writeMicroseconds(micro4);
    servo5.writeMicroseconds(micro5);
    
    Serial.begin(9600);
}

/*void loop(){
    micro1 = (int)((float)analogRead(sensor1) * 20000.0 / 1023.0);
    servo1.writeMicroseconds(micro1);
    Serial.print(" micro 1= ");
     Serial.println(micro1);  
} */ 

/*void setup() 
{
  Serial.begin(9600);
}*/
 
void loop() 
{
  //Sliding average (still needs magnitude shift and testing)
  //Consider a calibration period to zero out dc offset
  //implement hard endpoints for servo control
  //later on implement soft endpoints/ analog contorl
  //do a gui
  //above is in order of decreasing priority
  raw = analogRead(A0);
  int i;
  sum = 0;
  if(count < NumReadings){
    readingsAvg[count] = raw;
    count++;
  }
  else{
    int temp[NumReadings];
    for(i = 0; i < NumReadings; i++){
      temp[i] = readingsAvg[i];
    }
    for(i = 0; i < NumReadings - 1; i++){
      readingsAvg[i+1] = temp[i];
    }
    readingsAvg[NumReadings - 1] = raw;
    for(i = 0; i < NumReadings; i++){
      sum = sum + readingsAvg[i];
    }
    int out = (sum / NumReadings);
    
    if(out > lowerLim){
      flexed = 1;
    }
    else if(out < upperLim){
      flexed = 0;
    }

    Serial.println(flexed);
    //servo1.write(...); IN DEGREES
    delay(10);
  }
  
  /*float sensorValue = analogRead(A1);
  float millivolt = (sensorValue/1023)*5;
  
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  Serial.print("Voltage: ");
  Serial.print(millivolt*1000);
  Serial.println(" mV");
  Serial.println("");
  delay(1);       */
}

     /* micro2= (int)((float)analogRead(sensor2) * 3000.0 / 1023.0);
    servo2.writeMicroseconds(micro2);
       Serial.print(" micro 2= ");
    Serial.println(micro2);
  
      micro3 = (int)((float)analogRead(sensor3) * 3000.0 / 1023.0);
    servo3.writeMicroseconds(micro3);
    Serial.print(" micro 3= ");
   Serial.println(micro3);
    
     micro4 = (int)((float)analogRead(sensor4) * 3000.0 / 1023.0);
     servo4.writeMicroseconds(micro4);
      Serial.print(" micro 4= ");
    Serial.println(micro4);
   delay(100);
    micro5 = (int)((float)analogRead(sensor5) * 3000.0 / 1023.0);
     servo5.writeMicroseconds(micro5);
      Serial.print(" micro 5= ");
    Serial.println(micro5);
   delay(100);
   */
