// If LT_ returns true it means it found a white stripe.
// 0 for white, 1 elsewise
#define LTL digitalRead(10) // Left - Tagged with label 2 - Port 3 in  Tracking module of the custom the board
#define LTR digitalRead(2) // Right - Tagged with label 3 - Port 5 in  Tracking module of the custom the board

// For the motor driver module
#define MAX_SPEED 255

#define RIGHT 0
#define LEFT 1

// Engine output
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 150;


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
  double slowSpeed = round(1.0 * vel - (1.0 * vel)/(1.0 + (1.0 * radius) / (1.0 * vel) )); // VEL - VEL/(1 + RADIUS/VEL)
  int speedLeft = dir == RIGHT ? vel : slowSpeed;
  int speedRight = dir == LEFT ? vel : slowSpeed;
  _mMove(reverse ? -speedLeft : speedLeft, reverse ? -speedRight : speedRight);
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

void _avoidTheLineAndAttack(bool leftTrackerTouchingLine, bool rightTrackerTouchingLine){
  if (leftTrackerTouchingLine){
    _mRotateLeft();
    delay(400);
    _mCurve(MAX_SPEED, RIGHT, /* radious */ 175, /* reverse */ true);
  }
  else if (rightTrackerTouchingLine){
    _mRotateRight();
    delay(400);
    _mCurve(MAX_SPEED, LEFT, /* radious */ 175, /* reverse */ true);
  }
  delay(1500);
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
  _mStop();
}

bool touchingLeft = false;
bool touhingRight = false;

void loop()
{
  bool touchingLeft = !LTL;
  bool touchingRight = !LTR;
  if (touchingLeft || touchingRight)
  {
    _avoidTheLineAndAttack(touchingLeft, touchingRight);
  }
  _mStop();
}
