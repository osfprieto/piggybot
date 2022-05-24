// The microbit works with 3V and the Arduino works with 5V.
// This means that a 1024 from the Microbit is read as about 667 (3/5 of 1024) on the Arduino.
//
// If we want to use analog signals we should account for about 6 equally spaced signals to account for white noise and keep the proportions between boards.
// This also requires us using some of the unused analog ports (we can't read analog on the digital ports) which may mean soldering into the existing board.
//
// Another option is to just use one signal through the available digial ports or code through byte maps.

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(A0));
  Serial.print("\t");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.print("\t");
  Serial.print(analogRead(A3));
  Serial.print("\t");
  Serial.print(analogRead(A4));
  Serial.print("\t");
  Serial.print(analogRead(A5));
  Serial.println("");
}
