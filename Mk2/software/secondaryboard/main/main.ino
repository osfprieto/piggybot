// The higher the values, the better signal we get but the longer it takes.
#define SIGNAL_SAMPLE_SIZE 1000
// Sample of 1000 with rate of 50 gives us about +-9% variation in 50ms (0.05s)
// Sample of 1000 with rate of 100 gives us about +-1% variation in 100ms (0.1s)
#define SIGNAL_PROCESSING_RATE_MICROSECONDS 50

// Motors
#define PIN_Motor_STBY 3
#define PIN_Motor_PWMA 5
#define PIN_Motor_AIN_1 7
// #define PIN_Motor_PWMB 6
// #define PIN_Motor_BIN_1 8

#define MAX_SPEED 255

int vel = MAX_SPEED;

/**
 * Process the signal on a specific port and returns the
 * percentage of HIGH found in the samples (between 0 and 1.0)
 */
double _processSignal()
{
  int counter = 0;
  for(int i = 0; i < SIGNAL_SAMPLE_SIZE; i++)
  {
    if(digitalRead(A5) == HIGH)
    {
      counter++;
    }
    delayMicroseconds(SIGNAL_PROCESSING_RATE_MICROSECONDS);
  }
  return (1.0*counter)/(1.0*SIGNAL_SAMPLE_SIZE);
}

void _move(int vel){
  digitalWrite(PIN_Motor_STBY, HIGH);

  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, vel);
  // digitalWrite(PIN_Motor_BIN_1, HIGH);
  // analogWrite(PIN_Motor_PWMB, vel);
}


void setup() {
  Serial.begin(9600);
  // pinMode(PIN_Motor_PWMB, OUTPUT);
  // pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
}

void loop() {
  vel = round(_processSignal()*MAX_SPEED);
  if(vel < 20 || vel > MAX_SPEED-20)
  {
    vel = MAX_SPEED;
  }
  Serial.println(vel);
  _move(vel);
}
