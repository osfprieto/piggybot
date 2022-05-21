int in1 = 6; // Right - Forward speed
int in2 = 7; // Right - Backward speed
int in3 = 8; // Left - Backward speed
int in4 = 9; // Left - Forward speed
int ENA = 5; // Right - Enable movement
int ENB = 11; // Left - Enable movement

int state = 0;

void _mMove(int vel)
{ // Maximo: 255
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  analogWrite(in1,255);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,vel);
  Serial.println("Ahead");
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
  _mMove(127);
}

void loop()
{
  // _mMove(state++);
  // state %= 1024;
  // delay(10);
}
