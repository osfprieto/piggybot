#define MICROBIT A0

void setup() 
{
  pinMode(MICROBIT, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.println(analogRead(MICROBIT));
  delay(100);
}
