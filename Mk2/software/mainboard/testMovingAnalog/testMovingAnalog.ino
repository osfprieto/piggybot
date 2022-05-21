#define MAX_SPEED 255

int in1 = 6; // Right - Forward speed
int in2 = 7; // Right - Backward speed
int in3 = 8; // Left - Backward speed
int in4 = 9; // Left - Forward speed
int ENA = 5; // Right - Enable movement
int ENB = 11; // Left - Enable movement

/**
@speedLeft, @speedRight: [-255,255]
value < 0: speed backwards
value = 0: not moving
value > 0: speed forward
*/
void _mMove(int speedLeft, int speedRight)
{
  int in1Value = speedRight > 0 ? speedRight : 0;
  int in2Value = speedRight < 0 ? -speedRight : 0;
  int in3Value = speedLeft < 0 ? -speedLeft : 0;
  int in4Value = speedLeft > 0 ? speedLeft : 0;
  
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  analogWrite(in1,in1Value);
  analogWrite(in2,in2Value);
  analogWrite(in3,in3Value);
  analogWrite(in4,in4Value);
}

void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
}

void _mForward()
{
  _mMove(MAX_SPEED, MAX_SPEED);
}

void _mBackward()
{
  _mMove(-MAX_SPEED, -MAX_SPEED);
}

void _mRotateLeft()
{
  _mMove(-MAX_SPEED, MAX_SPEED);
}

void _mRotateRight()
{
  _mMove(MAX_SPEED, -MAX_SPEED);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop()
{
  _mForward();
  delay(1000);
  _mStop();
  delay(1000);
  _mBackward();
  delay(1000);
  _mStop();
  delay(1000);
  _mRotateLeft();
  delay(1000);
  _mStop();
  delay(1000);
  _mRotateRight();
  delay(1000);
  _mStop();
  delay(1000);
}
