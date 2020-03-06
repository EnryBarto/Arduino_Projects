#include <LiquidCrystal.h>
#include <NewPing.h>

#define maxd 100
#define echo 4
#define trigger 5

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
NewPing sonar(trigger, echo, maxd);


void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("By Enry & Teo");
}

void loop()
{
  int distance=sonar.ping_cm();
   
  lcd.setCursor(0, 0);
  lcd.print("Distanza:");
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.setCursor(13, 0);
  lcd.print("cm");
  delay(500);
}
