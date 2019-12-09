int button = 7; // imposta la porta del pulsante
int led1= 8; // imposta la porta del primo led
int led2= 9; // imposta la porta del secondo led

void setup(){
  pinMode(button, INPUT);
  pinMode(led2, OUTPUT);
}
void loop() {
  if(digitalRead(button)==HIGH){ // verifica se il pulsante è premuto
  digitalWrite(led2, LOW); // spegne il secondo led
  digitalWrite(led1, HIGH); // accende il primo led
  }
  else{
   digitalWrite(led1, LOW); // spegne il primo led  
   digitalWrite(led2, HIGH); // accende il secondo led
  }
}
