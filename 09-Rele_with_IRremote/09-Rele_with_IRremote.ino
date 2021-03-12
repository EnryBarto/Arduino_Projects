#include "IRremote.h"


int receiver = 11;
int rele = 7;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() {
    // takes action based on IR code received

    // describing Remote IR codes
    switch (results.value) {
        case 0xFFA25D: Serial.println("POWER"); digitalWrite(rele, !digitalRead(rele)); break;

        case 0xFF629D: Serial.println("Relé ON"); digitalWrite(rele, LOW); break;

        case 0xFFA857: Serial.println("Relé OFF"); digitalWrite(rele, HIGH); break;

        default: Serial.println("Unrecognized command");
    }

    // Do not get immediate repeat
    delay(500);
}

void setup() {
    Serial.begin(9600);
    Serial.println("IR Receiver Button Decode"); 
    irrecv.enableIRIn(); // Start the receiver
    pinMode(rele, OUTPUT);
    digitalWrite(rele, HIGH);
}

void loop() {
    // have we received an IR signal?
    if (irrecv.decode(&results)) {
        translateIR(); 
        irrecv.resume(); // receive the next value
    }
}
