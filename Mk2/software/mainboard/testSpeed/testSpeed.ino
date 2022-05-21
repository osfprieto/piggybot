int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;

int state = 0;

void _mMove(int vel)
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  analogWrite(in1,vel);
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
}

void loop()
{
  _mMove(state++);
  state %= 1024;
  delay(10);
}
