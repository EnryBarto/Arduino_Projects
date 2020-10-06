int button = 7; // imposta la porta del pulsante
int led1= 8; // imposta la porta del primo led
int led2motor= 9; // imposta la porta del secondo led

void setup(){
    pinMode(button, INPUT); // inizializza il pulsante
    pinMode(led1, OUTPUT); // inizializza il primo led
    pinMode(led2motor, OUTPUT); // inizializza il secondo led e il motore
    digitalWrite(led1, HIGH); // accende il primo led
    digitalWrite(led2motor, LOW); // spegne il secondo led e il motore
}
void loop() {
    // controlla se il pulsante è premuto
    if (digitalRead(button)==HIGH) {
        // inverte lo stato di accensione del led e del motore
        digitalWrite(led2motor, !digitalRead(led2motor));

        // regola il primo led inversamente al secondo led e il motore
        digitalWrite(led1, !digitalRead(led2motor));

        // finché non viene rilasciato il pulsante non continua a fare verifiche
        while(digitalRead(button)==HIGH){}
    }
}
