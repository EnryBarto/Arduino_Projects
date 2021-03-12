/*
 * Questo codice permette di inviare un segnale IR
 * ogni volta che si preme un pulsante
 */

#include <IRremote.h>


IRsend irsend;

void setup() {
    pinMode(8, INPUT);
    pinMode(3, OUTPUT);
}

void loop() {
    if (digitalRead(8)==HIGH) {
        irsend.sendSAMSUNG(0xE0E008F7, 32); // SAMSUNG è il tipo di decodifica
    }
}
