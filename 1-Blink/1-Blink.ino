int led = 8;
int tempo = 4000;

void setup() {
    pinMode(led,  OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);
    delay(tempo);
    digitalWrite(led, LOW);
    delay(tempo);
}
