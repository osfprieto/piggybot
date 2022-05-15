#include <IRremote.h>

// If LT_ returns true it means it found a white stripe.
// 0 for white, 1 elsewise

#define LTL digitalRead(10) // Left
#define LTC digitalRead(4) // Center
#define LTR digitalRead(2) // Right

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


int Echo = A4;  
int Trig = A5; 
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

int ATTACK_DISTANCE = 20;

int RIGHT = 1;
int LEFT = 2;

int distance = 0;
int turnDirection = 0;
bool movingForward = false;

void _mForward()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Ahead");
}

void _mBack()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Back");
}

void _mLeft()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  Serial.println("Left");
}

void _mRight()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Right");
}

void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop");
}

void _mTurn()
{
  if(turnDirection==RIGHT)
  {
    _mRight();
  }
  else
  {
    _mLeft();
  }
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
int _measureDistance()   
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

void _avoidTheLine()
{
  _mBack();
  delay(200);
  if(!LTC && LTR) // Touching the line with the left line tracker
  // USE THE LTC because LTL is damaged
  {
    _mRight();
    while(!LTC);
    delay(200);
    _mForward();
    delay(400);
  }
  else if (LTC && !LTR) // Touching the line with the right line tracker
  {
    _mLeft();
    while(!LTR);
    delay(200);
    _mForward();
    delay(400);
  }
  
  Serial.println("Avoid");
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
  //_mBack();
  //delay(100);
  _mForward();
  delay(300);
  _mStop();
  turnDirection = random(1,3);
}

void loop() 
{
  if(irrecv.decode(&results))
  {
    if(results.value != IRH)
    {
      IRSignal = results.value;
    }
    irrecv.resume();
    Serial.println(IRSignal);
  }
  else if (IRSignal == IR1)
  {
    distance = _measureDistance();
    
    if(distance<=ATTACK_DISTANCE)
    {
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
    else if (!LTC || !LTR)
    {
      movingForward = false;
      _avoidTheLine();
    }
    else
    {
      movingForward = false;
      _mTurn();
    }
  }
  else if(IRSignal == IRS){
    _mStop();
  }
  else if(IRSignal == IRF){
    _mForward();
  }
  else if(IRSignal == IRB){
    _mBack();
  }
  else if(IRSignal == IRR){
    _mRight();
  }
  else if(IRSignal == IRL){
    _mLeft();
  }
  else
  {
    IRSignal = IR1;
  }
}
