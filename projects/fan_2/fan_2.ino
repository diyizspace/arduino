#include <Servo.h>
int value = 0; // set values you need to zero
Servo firstESC;
void setup() {
  firstESC.attach(9);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud
}
void loop() {
  firstESC.writeMicroseconds(value);
  if(Serial.available()){
    value = Serial.parseInt();
  }
}
