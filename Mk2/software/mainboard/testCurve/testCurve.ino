#define MAX_SPEED 255
#define RIGHT 0
#define LEFT 1

int in1 = 6; // Right - Forward speed
int in2 = 7; // Right - Backward speed
int in3 = 8; // Left - Backward speed
int in4 = 9; // Left - Forward speed
int ENA = 5; // Right - Enable movement
int ENB = 11; // Left - Enable movement

int currentRadius = 1;

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

/**
 * Calculates the left and right speeds (in the same direction) so the car describes a curve with a given radius parameter
 * vel: upper bound of the speeds.
 * dir: 0 ir 1, defines right or left respectively
 * radius: parameter to control how diverse are the lateral speeds
 * reverse: true means the speeds will be given in negative form (going backwards).
 */
void _mCurve(int vel, int dir, int radius, bool reverse)
{
  // VEL - VEL/(1 + RADIUS/VEL)
  // R=50 -> 34 pulgadas diametro
  // R=100 -> 45 pulgadas diametro
  // R=200 -> 79 pulgadas diametro
  // R=400 -> 124 pulgadas diametro
  // R=800 -> 172 pulgadas diametro
  double slowSpeed = round(1.0 * vel - (1.0 * vel)/(1.0 + (1.0 * radius) / (1.0 * vel) )); // VEL - VEL/(1 + RADIUS/VEL) // Radius 100 here nos da 45 pulgadas de diametro.
  int speedLeft = dir == RIGHT ? vel : slowSpeed;
  int speedRight = dir == LEFT ? vel : slowSpeed;
  _mMove(reverse ? -speedLeft : speedLeft, reverse ? -speedRight : speedRight);
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
  // _mCurve(MAX_SPEED, RIGHT, /* radious */ 800, /* reverse */ false);
}

void loop()
{
  _mCurve(MAX_SPEED, RIGHT, currentRadius++, /* reverse */ false);
  delay(100);
}
