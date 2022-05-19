// If LT_ returns true it means it found a white stripe.
// 0 for white, 1 elsewise

#define LTL digitalRead(10) // Left
#define LTC digitalRead(4) // Center
#define LTR digitalRead(2) // Right

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  Serial.print("L: ");
  Serial.print(LTL);
  Serial.print("\tC: ");
  Serial.print(LTC);
  Serial.print("\tR: ");
  Serial.println(LTR);
}
