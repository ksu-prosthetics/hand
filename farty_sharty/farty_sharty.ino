#include <Servo.h>

#define sensor1 A0
#define sensor2 2
#define sensor3 A2
#define sensor4 A3
#define sensor5 A4

#define servo1Pin A1
#define servo2Pin 3
#define servo3Pin 4
#define servo4Pin 5
#define servo5Pin 6

const int ledPin = LED_BUILTIN; // pin to use for the LED

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
int temp[NumReadings] = {0};
int readingsAvg[NumReadings] = {0};
int sum = 0;
int flexed = -1;
int lowerLim = 200;
int upperLim = 300;
int raw = 0;
int angle = 0;
int T = 0;

void setup() {
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);

  pinMode(ledPin, OUTPUT);
  
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

void loop()
{
  //  servo1.write(180);
  //  delay(1000);
  //  servo1.write(90);
  //  delay(1000);
  //  servo1.write(45);
  //  delay(1000);
  //  servo1.write(360);
  //  delay(1000);
  //  servo1.write(0);
  //  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //  delay(1000);                       // wait for a second
  //  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //  delay(1000);                       // wait for a second

         // digitalWrite(ledPin, HIGH);         // will turn the LED on

  //reads in the current time and data
  T = millis();
  raw = analogRead(A0);
  
  //evaluates a "NumReadings" point average of the signal
  int i;
  sum = 0;
  int temp[NumReadings];
  for (i = 0; i < NumReadings; i++) {
    temp[i] = readingsAvg[i];
  }
  for (i = 0; i < NumReadings - 1; i++) {
    readingsAvg[i + 1] = temp[i];
  }
  readingsAvg[NumReadings - 1] = raw;
  for (i = 0; i < NumReadings; i++) {
    sum = sum + readingsAvg[i];
  }
  int out = (sum / NumReadings);

  //changes direction of angle based on flexed or relaxed
  if (out > lowerLim) {
    flexed = 1;
  }
  else if (out < upperLim) {
    flexed = -1;
  }

  //updates the angle and prints for reference
  angle = angle + flexed;
  Serial.println(flexed);

  //moves the servo by one degree in the given direction
  if (angle < 180 || angle > 0) {
    servo1.write(angle);
  }
  //ensures a 5ms time delay between main loops
  while (millis() - T < 500) {}

 digitalWrite(ledPin, HIGH);         // will turn the LED on 
  delay(10);
digitalWrite(ledPin, LOW); // turn the LED off
delay(10); // keep it off for 900 milliseconds
}
