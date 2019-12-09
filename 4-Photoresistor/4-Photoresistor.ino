#define led 2 // definisce il numero del pin del led
#define soglia 90 // definisce la soglia dell'accensione della luce
int luce; // crea la variabile luce

void setup(){
 pinMode(led, OUTPUT); // inizializza il led come OUTPUT 
}

void loop(){
  luce = analogRead(A0); // imposta la variabile luce al valore della luminosità letta dalla fotoresistenza
  if(luce < soglia){ // controlla se la luce ambientale è minore della soglia
  digitalWrite(led, HIGH); // accende il led se la condizione è verificata
  }
  else{ // se la condizione non è rispettata
   digitalWrite(led, LOW); // spegne il led
  }
}
