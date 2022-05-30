#include <IRremote.h>

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

int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long IRSignal = IR1;


void setup() 
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
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
}
