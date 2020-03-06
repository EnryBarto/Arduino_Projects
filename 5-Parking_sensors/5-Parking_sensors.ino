#include <NewPing.h> // richiama la libreria NewPing
#define maxd 100 // imposta la distanza massima che il sensore deve leggere
#define allarm 6 // imposta il pin dell'avvisatore acustico
#define echo 7 // imposta il pin che riceverà il segnale del sensore
#define trigger 8 // imposta il pin che trasmetterà il segnale al sensore
#define ledv 9 // imposta il pin del led verde
#define ledg 10 // imposta il pin del led giallo
#define ledr 11 // imposta il pin del led rosso
#define distanza1 30 // imposta la prima distanza in cm
#define distanza2 15 // imposta la seconda distanza in cm
#define distanza3 8 // imposta la terza distanza in cm

NewPing sonar(trigger, echo, maxd); // assegna i ruoli ai pin del sensore

void setup(){
pinMode(ledv, OUTPUT); // imposta il led verde come output
pinMode(ledg, OUTPUT); // imposta il led giallo come output
pinMode(ledr, OUTPUT); // imposta il led rosso come output
pinMode(allarm, OUTPUT); // imposta l'avvisatore acustico come output
Serial.begin(9600);
}

void loop(){

  int lettura=sonar.ping_cm(); // imposta il valore della lettura uguale al valore letto dal sonar in cm
    if(lettura<distanza1){ // controlla se il sonar rileva un oggetto a distanza minore della distanza 1
      digitalWrite(ledv, LOW); // spegne il led verde
      digitalWrite(ledg, HIGH); // accende il pin giallo
      digitalWrite(ledr, LOW); // spegne il led rosso
      digitalWrite(allarm, LOW); // spegne l'avvisatore acustico
      if(lettura==0){ // controlla se il sonar non rileva alcun oggetto
       digitalWrite(ledv, HIGH); // accende il led verde 
       digitalWrite(ledg, LOW); // spegne il led giallo
       digitalWrite(ledr, LOW); // spegne il led rosso
       digitalWrite(allarm, LOW); // spegne l'avvisatore acustico
      }
      else{ // se la lettura è diversa da 0...
        if(lettura<distanza2){ // controlla se il sonar rileva un oggetto a distanza minore della distanza 2
         digitalWrite(ledv, LOW); // spegne il led verde
         digitalWrite(ledg, LOW); // spegne il led giallo
         digitalWrite(ledr, HIGH); // accende il led rosso
         digitalWrite(allarm, LOW); // spegne l'avvisatore acustico
         if(lettura<distanza3){ // controlla se il sonar rileva un oggetto a distanza minore della distanza 3
           digitalWrite(ledv, LOW); // spegne il led verde
           digitalWrite(ledg, LOW); // spegne il led giallo
           digitalWrite(ledr, HIGH); // accende il led rosso
           digitalWrite(allarm, HIGH); // accende l'avvisatore acustico
        }
        }
      }
    }
    else{ // se la lettura non è minore della distanza 1...
      digitalWrite(ledv, HIGH); // accende il led verde
      digitalWrite(ledg, LOW); // spegne il led giallo
      digitalWrite(ledr, LOW); // spegne il led rosso
      digitalWrite(allarm, LOW); // spegne l'avvisatore acustico
  }  
 Serial.println(lettura);
 delay(50);
  }
