/*
 * Questo codice permette di inviare un segnale IR
 * ogni volta che si preme un pulsante.
 * Il pin del led IR è sempre e in 
 * ogni caso il PIN digitale 3.
 * NEC è il tipo di decodifica.
 */

#include <IRremote.h> // include la libreria IRremote

IRsend irsend; 

#define led 5 // definisce il pin del led che si illumina alla pressione di un pulsante
#define ledint 50 // definisce l'intensità del led

void setup()
{
  pinMode(3, OUTPUT); // imposta il pin 3 come output
  pinMode(8, INPUT); // imposta il pin 8 come input
  pinMode(9, INPUT); // imposta il pin 9 come input
  pinMode(10, INPUT); // impoista il pin 10 come input 
  pinMode(11, INPUT); // imposta il pin 11 come input
  pinMode(12, INPUT); // imposta il pin 12 come input
  pinMode(led, OUTPUT); // imposta il led come output
}

void loop() {
  if(digitalRead(8)==HIGH){ // controlla se il pulsante è premuto
    analogWrite(led, ledint); // accede il led 
    irsend.sendNEC(0x20DF807F, 32); // invia il segnale NEC
    digitalWrite(led, LOW); // spegne il led
  }
  if(digitalRead(9)==HIGH){ // controlla se il pulsante è premuto
    analogWrite(led, ledint); // accede il led 
    irsend.sendNEC(0x20DF00FF, 32); // invia il segnale NEC
    digitalWrite(led, LOW); // spegne il led
  }
  if(digitalRead(10)==HIGH){ // controlla se il pulsante è premuto
    analogWrite(led, ledint); // accede il led 
    irsend.sendNEC(0x20DFC03F, 32); // invia il segnale NEC
    digitalWrite(led, LOW); // spegne il led
  }
  if(digitalRead(11)==HIGH){ // controlla se il pulsante è premuto
    analogWrite(led, ledint); // accede il led 
    irsend.sendNEC(0x20DF40BF, 32); // invia il segnale NEC
    digitalWrite(led, LOW); // spegne il led
  }
  if(digitalRead(12)==HIGH){ // controlla se il pulsante è premuto
    analogWrite(led, ledint); // accede il led 
    irsend.sendNEC(0x20DF10EF, 32); // invia il segnale NEC
    digitalWrite(led, LOW); // spegne il led 
  }  
}
