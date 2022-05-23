#include <Servo.h>

#define PIN_Servo_z 10
#define PIN_Servo_y 11

Servo myServo;

void setup(){
  // Change the pin to control the other servo.
  myServo.attach(PIN_Servo_z);
}
 
void loop(){
  myServo.write(10);
  delay(1000);
  for(int i=10; i<=180; i++){
    myServo.write(i);
    delay(10);
  }
  delay(2000);
}
