
#define MAX_SPEED 255

#define PIN_Motor_STBY 3
#define PIN_Motor_PWMA 5
#define PIN_Motor_AIN_1 7
// #define PIN_Motor_PWMB 6
// #define PIN_Motor_BIN_1 8

void _move(){
  // Motor Standby?
  digitalWrite(PIN_Motor_STBY, HIGH);

  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, MAX_SPEED);
  // digitalWrite(PIN_Motor_BIN_1, HIGH);
  // analogWrite(PIN_Motor_PWMB, MAX_SPEED);
}

void _stop(){
  digitalWrite(PIN_Motor_STBY, LOW);
}

void setup() {
  // A means right
  // B means left
  
  // pinMode(PIN_Motor_PWMB, OUTPUT);
  // pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
  _move();
}

void loop() {
  
}
