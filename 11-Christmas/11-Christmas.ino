#include "Pitches.h"
#include "IRremote.h"


int receiver = 11;
int rele = 7;
int buzzer = 6;
int minima = 500;
int semibreve = minima*2;
int semiminima = minima/2;
int croma = minima/4;


/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); digitalWrite(rele, !digitalRead(rele)); break;

  case 0xFF629D: Serial.println("Relé ON"); digitalWrite(rele, LOW); break;

  case 0xFFA857: Serial.println("Relé OFF"); digitalWrite(rele, HIGH); break;

  case 0xFFE21D: Serial.println("STOP"); noTone(buzzer); break;

  case 0xFF02FD: Serial.println("Start Jingle Bells");
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, D6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, G5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semibreve); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, D6); delay(minima); noTone(buzzer);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, D6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, G5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semibreve); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, B5); delay(minima); noTone(buzzer); delay(5);
    tone(buzzer, D6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, D6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, C6); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, A5); delay(semiminima); noTone(buzzer); delay(5);
    tone(buzzer, G5); delay(semibreve); noTone(buzzer); break;

 

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
  digitalWrite(rele, HIGH);

} /*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
