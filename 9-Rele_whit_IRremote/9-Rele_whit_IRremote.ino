//www.elegoo.com
//2016.12.9

#include "IRremote.h"

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int rele = 7;


/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {

  case 0xFF629D: Serial.println("Relé ON"); digitalWrite(rele, HIGH); break;

  case 0xFFA857: Serial.println("Relé OFF"); digitalWrite(rele, LOW); break;
 

  default: 
    Serial.println("Unrecognized command");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  pinMode(rele, OUTPUT);

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
