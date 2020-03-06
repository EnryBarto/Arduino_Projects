#include <LiquidCrystal.h>


int tempPin = 0;
int engine = 4;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup()
{
  lcd.begin(16, 2);
  pinMode(engine, OUTPUT);
}


void loop()
{
  int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
   
  lcd.setCursor(0, 0);
  lcd.print("Temp        C");
  lcd.setCursor(6, 0);
  lcd.print(tempC);
    
  if (tempC>=24){
    digitalWrite(engine, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Raffreddamento");
  }
  
  else{
    digitalWrite(engine, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Ventola spenta");
  }
  delay(500);
}
