#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

int tempup = 5;
int tempdown = 6;
int engine = A1;
float soglia = 25;

//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  if( millis( ) - measurement_timestamp > 100ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


void setup(){
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   TERMOSTATO");
  lcd.setCursor(0, 1);
  lcd.print("  by EnryBarto");  
  pinMode(engine, OUTPUT);
  delay(5000);
}


void loop(){ 
  float tempC;
  float humidity;
  
  if( measure_environment( &tempC, &humidity ) == true ){
    lcd.setCursor(0, 0);
    lcd.print("Temp:    Umid:");  
    lcd.setCursor(0, 1);
    lcd.print("      C        %");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    lcd.setCursor(9, 1);
    lcd.print(humidity);
  
    if(digitalRead(tempup)==HIGH){
      soglia=soglia+0.5; 
      lcd.setCursor(0, 0);
      lcd.print("Temp. start:    ");  
      lcd.setCursor(0, 1);
      lcd.print("      C         ");
      lcd.setCursor(0, 1);
      lcd.print(soglia);
      delay(1000);
      while(digitalRead(tempup)==HIGH){      
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
    
    if(digitalRead(tempdown)==HIGH){
      soglia=soglia-0.5; 
      lcd.setCursor(0, 0);
        lcd.print("Temp. start:    ");  
        lcd.setCursor(0, 1);
        lcd.print("      C         ");
        lcd.setCursor(0, 1);
        lcd.print(soglia);
      delay(1000);
      while(digitalRead(tempdown)==HIGH){      
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
  
    if (tempC>=soglia){digitalWrite(engine, HIGH);}
    else{digitalWrite(engine, LOW);}  
  }
}
