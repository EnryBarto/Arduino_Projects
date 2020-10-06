#include <LiquidCrystal.h>


int tempup = 5;
int tempdown = 6;
int tempPin = A0;
int engine = A1;
float soglia = 25;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("   TERMOSTATO");
    lcd.setCursor(0, 1);
    lcd.print("  by EnryBarto");  
    pinMode(engine, OUTPUT);

    delay(5000);
}


void loop() {   
    int tempReading = analogRead(tempPin);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    float tempC = tempK - 273.15;

    lcd.setCursor(0, 0);
    lcd.print("Temperatura:  ");  
    lcd.setCursor(0, 1);
    lcd.print("      C         ");
    lcd.setCursor(0, 1);
    lcd.print(tempC);

    if (digitalRead(tempup)==HIGH) {
        soglia=soglia+0.5; 
        lcd.setCursor(0, 0);
        lcd.print("Temp. start:    ");  
        lcd.setCursor(0, 1);
        lcd.print("      C         ");
        lcd.setCursor(0, 1);
        lcd.print(soglia);

        delay(1000);

        while (digitalRead(tempup)==HIGH) {      
            delay(250);
            soglia=soglia+0.5;
            lcd.setCursor(0, 0);
            lcd.print("Temp. start:    ");  
            lcd.setCursor(0, 1);
            lcd.print("      C         ");
            lcd.setCursor(0, 1);
            lcd.print(soglia);
        }

        delay(2000);
    }
    
    if (digitalRead(tempdown)==HIGH) {
        soglia=soglia-0.5; 
        lcd.setCursor(0, 0);
        lcd.print("Temp. start:    ");  
        lcd.setCursor(0, 1);
        lcd.print("      C         ");
        lcd.setCursor(0, 1);
        lcd.print(soglia);

        delay(1000);

        while (digitalRead(tempdown)==HIGH) {      
            delay(250);

            soglia=soglia-0.5;
            lcd.setCursor(0, 0);
            lcd.print("Temp. start:    ");  
            lcd.setCursor(0, 1);
            lcd.print("      C         ");
            lcd.setCursor(0, 1);
            lcd.print(soglia);
        }

        delay(2000);
    }
      
    if (tempC>=soglia) {
        digitalWrite(engine, HIGH);
    } else {
        digitalWrite(engine, LOW);
    }

    delay(150);  
}
