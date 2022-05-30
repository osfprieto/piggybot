#include <IRremote.h>

// If LT_ returns true it means it found a white stripe.
// 0 for white, 1 elsewise
// TEST THIS ON THE SCENE!!!
#define LTL digitalRead(10) // Left - Tagged with label 2 - Port 3 in  Tracking module of the custom the board
#define LTR digitalRead(2) // Right - Tagged with label 3 - Port 5 in  Tracking module of the custom the board

// For the motor driver module
#define MAX_SPEED 255

// Infrared signal codes
#define IRL 16720605 // Left
#define IRR 16761405 // Right
#define IRF 16736925 // Forward
#define IRB 16754775 // Backwards
#define IRS 16712445 // OK - Stop
#define IRH 4294967295 // Hold any button
#define IR1 16738455 // number one
#define IR2 16750695 // number two
#define IR3 16756815 // number three
#define IR4 16724175 // number four
#define IR5 16718055 // number five
#define IR6 16743045 // number six

#define RIGHT 0
#define LEFT 1

#define ATTACK_DISTANCE 50
#define CHASE_DISTANCE 5

// Ultrasonic ports
int Echo = A4;
int Trig = A5;

// Engine output
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 150;

int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long IRSignal = IR1;

int distance = 0;
int turnDirection = RIGHT;
bool movingForward = false;

// Manual override through A0 port.
int readSignal = 0;
bool charging = false;

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

void _mTurn()
{
  if(turnDirection==RIGHT)
  {
    _mRotateRight();
  }
  else
  {
    _mRotateLeft();
  }
}

/**
 * Tries to get out of the way so the other bot takes itself out of the ring.
 */
void _jiuJitsu(int dir)
{
  if(dir == LEFT)
  {
    _mRotateRight();
  }
  else
  {
    _mRotateLeft();
  }
  delay(200);
  _mCurve(MAX_SPEED, dir, /* radious */ 200, /* reverse */ true); // TEST THIS ON THE SCENE!!!
  delay(2500);
}

void _switchDirection()
{
  if(turnDirection==RIGHT)
  {
    turnDirection=LEFT;
  }
  else
  {
    turnDirection=RIGHT;
  }
}

 /*Ultrasonic distance measurement Sub function*/
int _measureDistance() // TEST THIS ON THE SCENE!!!
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);
  Fdistance= Fdistance/58;
  return (int)Fdistance;
}

/**
 * @deprecated
 */
void _avoidTheLineAndAttack(bool leftTrackerTouchingLine, bool rightTrackerTouchingLine){
   if (leftTrackerTouchingLine){
     _mRotateRight();
     delay(200);
     // curve backward left
     _mCurve(MAX_SPEED, LEFT, /* radious */ 5, /* reverse */ true);

   }
   else if (rightTrackerTouchingLine){
     _mRotateLeft();
     delay(200);
     // curve backward right
     _mCurve(MAX_SPEED, RIGHT, /* radious */5, /* reverse */ true);
   }
   // Test delay duration
   delay(500);
   _mStop();
}

/**
 * @deprecated
 */
void _avoidTheLine()
{
  _mBackward();
  delay(200);
  if(!LTL && LTR) // Touching the line with the left line tracke
  {
    _mRotateRight();
    while(!LTL);
    delay(200);
    _mForward();
    delay(400);
  }
  else if (LTL && !LTR) // Touching the line with the right line tracker
  {
    _mRotateLeft();
    while(!LTR);
    delay(200);
    _mForward();
    delay(400);
  }

  // Serial.println("Avoid");
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
  turnDirection = random(1,3);
}

void _mAttack(){
  if(!movingForward)
  {
    _switchDirection();
    _mTurn(); // When we start moving forward we come back a bit on the other direction to compensate for the momentum we had while rotating
    delay(10);
    //_mStop();
  }
  
  _mForward();
  movingForward = true;
}

void _mChaseOnly(){
  if(distance <= ATTACK_DISTANCE)
  {
    if (distance >= CHASE_DISTANCE){
      _mAttack();
    }
    else {
      _mStop();
      movingForward = false;
    }
  }
}

unsigned long trackingTimeStart = 0;
void _trackLineBackwardsAndGoToCenter(int timeToTrack, int side)
{
  trackingTimeStart = millis();

  if(side == LEFT)
  {
    _mRotateLeft();
    delay(200);
  }
  else if(side == RIGHT)
  {
    _mRotateRight();
    delay(200);
  }

  // Track the line
  while(millis() - trackingTimeStart < timeToTrack)
  {
    if(side == LEFT && !LTL)
    {
      _mRotateLeft();
      delay(50);
    }
    else if(side == RIGHT && !LTR)
    {
      _mRotateRight();
      delay(50);
    }
    _mBackward();
    delay(10);
  }
  
  // Reset the timer.
  trackingTimeStart = 0;

  // Now, let's look for the center.
  if(side == LEFT)
  {
    _mRotateRight();
  }
  else if(side == RIGHT && !LTR)
  {
    _mRotateRight();
  }
  delay(200);
  _mForward();
  delay(800);
}

void loop()
{
  // The A0 port receives 0-3.3V of energy, we expect a signal ranging from int 0 through 667.
  // 250 is a good measure for the center
  readSignal = analogRead(A0);
  if(readSignal > 99)
  {
    charging = true;
    if(readSignal > 200 && readSignal < 300)
    {
      _mStop();
    }
    else
    {
      _mMove(readSignal > 250 ? MAX_SPEED : -MAX_SPEED, readSignal > 250 ? -MAX_SPEED : MAX_SPEED);
    }
    // Serial.println("Processed signal");
  }
  else if (charging)
  {
    _mForward();
    delay(500);
    charging = false;
    // Serial.println("Charge");
  }
  else if(irrecv.decode(&results))
  {
    if(results.value != IRH)
    {
      IRSignal = results.value;
    }
    irrecv.resume();
    // Serial.println(IRSignal);
  }
  else if (IRSignal == IR1)
  {
    distance = _measureDistance();

    if(distance<=ATTACK_DISTANCE)
    {
      _mAttack();
      // Serial.println("Attacking");
    }
    else if (!LTL || !LTR)
    {
      movingForward = false;
      _trackLineBackwardsAndGoToCenter(/* timeToTrack */ 1500, !LTL ? LEFT : RIGHT);
      // Serial.println("Trackers");
    }
    else
    {
      movingForward = false;
      _mTurn();
      // Serial.println("Turn");
    }
  }
  else if(IRSignal == IRS){
    _mStop();
  }
  else if(IRSignal == IRF){
    _mForward();
  }
  else if(IRSignal == IRB){
    _mBackward();
  }
  else if(IRSignal == IRR){
    _mRotateRight();
  }
  else if(IRSignal == IRL){
    _mRotateLeft();
  }
  else if(IRSignal == IR4){
    _jiuJitsu(LEFT);
    IRSignal = IR1;
  }
  else if(IRSignal == IR6){
    _jiuJitsu(RIGHT);
    IRSignal = IR1;
  }
  else
  {
    IRSignal = IR1;
  }
}
