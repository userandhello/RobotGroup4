 #define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12
unsigned long irSensorMilis = 0; //Timer to track the last report of the IR sensors

void setup() {
  //setup infrared pins
pinMode(IR_1, INPUT);
pinMode(IR_2. INPUT);
pinMode(IR_3, INPUT);
pinMode(IR_4, INPUT);
}
void readInfrared() {
  int IRvalue1 = digitalRead(IR_1);
  int IRvalue2 = digitalRead(IR_2);
  int IRvalue3 = digitalRead(IR_3);
  int IRvalue4 = digitalRead(IR_4);
  //print the read values to the serial monitor
  Serial.print("IR_1:")
  Serial.print(IRvalue1);
  Serial.print(", IR_2:");
  Serial.print(IRvalue2);
  Serial.print(", IR_3:")
  Serial.print(IRvalue3);
  Serial.print(", IR_4:");
  Serial.println(IRvalue4);  

}
void loop() {
  unsigned long currentMillis = millis();

if (currentMillis - irSensorsMillis >= 500) {
  irSensorMillis = currentMillis;
  readInfrared();
  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMilis = currentMillis;
    readColorSensor();
  }
}

}
//Library Code for main .ino file
#include <tcs3200.h>
#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_4 A4
//readColorSensor.ino file
tcs3200 tcs(COLOR_0, COLOR_1, COLOR_2, COLOR_3, COLOR_OUT);
void readColorSensor() {
  sonst int samples = 5;
  long sumRed = 0, sumGreen = 0, sumBlue = 0, sumWhite = 0;

  for (int i = 0; i < samples; i++) +{
    sumRed += tcs.colorRead('r');
    sumGreen += tcs.colorRead('g');
    sumBlue += tcs.colorRead('b');
    sumWhite += tcs.colorRead('c');
  }
  int avgRed = sumRed / samples;
  int avgGreen = sumGreen / samples;
  int avgBlue = sumBlue / samples;
  int avgWhite = sumWhite / samples;
  
  Serial.print("Average Color Sensor Readings:");
  Serial.print(" R= ");
  Serial.print(avgRed);
  Serial.print(" G= ");
  Serial.print(avgGreen);
  Serial.print(" B= ");
  Serial.print(avgBlue);
  Serial.print(" W(clear)= ");
  Serial.print(avgWhite);
}



