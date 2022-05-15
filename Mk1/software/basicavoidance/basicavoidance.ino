//www.elegoo.com
//2016.09.23
/*
Use "myservo.write (angle)" to command the micron servo 
to the angle degree which has a range from 10 to 180. 
If it exceeds the range, the micro servo won’t recognize 
this angle and will keep rotating.
*/
#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int FORWARD = 90;
int LEFT = 170;
int RIGHT = 10;
int SERVO_DELAY =  200;
int TURN_DELAY_90 = 130;
int Echo = A4;  
int Trig = A5; 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS = 150;
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;

void _lookRight()
{
  //delay(SERVO_DELAY);     
  myservo.write(RIGHT);
  delay(SERVO_DELAY);   
}

void _lookForward()
{
  //delay(SERVO_DELAY);
  myservo.write(FORWARD);
  delay(SERVO_DELAY);
}

void _lookLeft()
{
  //delay(SERVO_DELAY);
  myservo.write(LEFT);
  delay(SERVO_DELAY);
}

void _mForward()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
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

void _mleft()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
  Serial.println("Left");
}

void _mright()
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
  Serial.println("Stop!");
} 
 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
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

void setup() 
{ 
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
}

void loop() 
{
    _lookForward();
    middleDistance = Distance_test();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif

    if(middleDistance<=20)
    {     
      _mStop();
      _lookRight();   
      rightDistance = Distance_test();

      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif

      _lookForward();
      _lookLeft();
      leftDistance = Distance_test();

      #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif

      _lookRight();
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(TURN_DELAY_90);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(TURN_DELAY_90);
       }
       else if((rightDistance<=20)||(leftDistance<=20))
       {
        _mBack();
        delay(1000);
       }
       else
       {
        _mForward();
       }
    }  
    else
        _mForward();                     
}

