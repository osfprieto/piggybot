// The higher the values, the better signal we get but the longer it takes.
#define SIGNAL_SAMPLE_SIZE 1000
// Sample of 1000 with rate of 50 gives us about +-9% variation in 50ms (0.05s)
// Sample of 1000 with rate of 100 gives us about +-1% variation in 100ms (0.1s)
#define SIGNAL_PROCESSING_RATE_MICROSECONDS 50

// It'd be worth looking at using hardware instead to save the processing time.

/**
 * Process the signal on a specific port and returns the
 * percentage of HIGH found in the samples.
 */
double processSignal()
{
  int counter = 0;
  for(int i = 0; i < SIGNAL_SAMPLE_SIZE; i++)
  {
    if(digitalRead(A0) == HIGH)
    {
      counter++;
    }
    delayMicroseconds(SIGNAL_PROCESSING_RATE_MICROSECONDS);
  }
  return (1.0*counter)/(1.0*SIGNAL_SAMPLE_SIZE);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println(processSignal());
}
