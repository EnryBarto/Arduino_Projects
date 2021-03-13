#include <HX711.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

HX711 loadcell;

#define BUTTON1 5 // Pin del pulsante MENU
#define BUTTON2 6 // Pin del pulsante +
#define BUTTON3 7 // Pin del pulsante -
#define BUTTON4 8 // Pin del pulsante INVIO
#define RELE 9    // Pin del relé

// PIN SENSORE PRESSIONE
const int LOADCELL_DOUT_PIN = 11;
const int LOADCELL_SCK_PIN = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Inizia la comunicazione IIC con l'LCD

// VALORI PRESSIONE
const float PRESS1 = 0.005; // Pressione base: 0 bar
const float PRESS2 = 0.1; // Pressione 1: 0,1 bar
const float PRESS3 = 0.2; // Pressione 2: 0,2 bar
const float PRESS4 = 0.3; // Pressione 3: 0,3 bar
const float PRESS5 = 0.6; // Pressione massima: 0,6 bar

// PROTOTIPI
void controlla_bottone(); // CONTROLLA SE IL PRIMO PULSANTE VIENE PREMUTO
void visualizza_pressione(); // VISUALIZZA LA PRESSIONE NELLA PAGINA INIZIALE
void rele(int t_on, int t_off); // ACCENDE E SPEGNE IL RELE
void menu(int press_iniz, int press_fin); // VISUALIZZA LE PAGINE DEL MENU
void modifica_tempi(float press_base, int *t_on, int *t_off); // MODIFICA I TEMPI DI INIEZIONE
void visualizza_modifiche(int tempo, float press_base); // DURANTE LA MODIFICA, VISUALIZZA LE PRESSIONI "SOGLIA" E I RELATIVI TEMPI
void scrivi_eeprom(int valore, int i); // SOVRASCRIVE LA EEPROM
int leggi_eeprom(int i); // LEGGE LA EEPROM
float leggi_pressione(); // LEGGE LA PRESSIONE DAL SENSORE

float pressione;  // Valore della pressione calcolata
int funzione;     // Contiene l'indice del menu in cui ci si trova 0: Pagina iniziale
unsigned long tempo, ritardo; // Contengono il tempo assegnato dalla funzione millis()
bool iniezione = false; // Vero se è in corso l'iniezione

// TEMPI INIEZIONE ATTIVA
int t_on1 = leggi_eeprom(0);
int t_on2 = leggi_eeprom(1);
int t_on3 = leggi_eeprom(2);
int t_on4 = leggi_eeprom(3);

// TEMPI INIETTORI A RIPOSO
int t_off1 = leggi_eeprom(4);
int t_off2 = leggi_eeprom(5);
int t_off3 = leggi_eeprom(6);
int t_off4 = leggi_eeprom(7);

void setup() {

  Serial.begin(9600);
  // INIZIALIZZAZIONE SENSORE DI PRESSIONE
  const long LOADCELL_OFFSET = 360000;
  const long LOADCELL_DIVIDER = 360000;
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.set_offset(LOADCELL_OFFSET);

  // INIZIALIZZAZIONE INPUT / OUTPUT
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  pinMode(RELE, OUTPUT); 

  // INIZIALIZZAZIONE DELL'LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   ACCENSIONE   ");
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print("-");
    delay(150);
  }

  funzione = 0;
  pressione = leggi_pressione();
}

void loop() { 

  // Esegue il controllo sul pulsante solo se non è in corso l'iniezione
  if (iniezione == false) {
    controlla_bottone();
  } else {
    funzione = 0; // Se si sta visualizzando il menu ed inizia l'iniezione, torna alla pagina iniziale
  }
  
  // IN BASE ALLA PRESSIONE DEL TASTO VISUALIZZA UNA PAGINA NELL'LCD
  if (funzione == 0) {
    visualizza_pressione();
  }

  // VISUALIZZA I MENU SOLO SE NON è IN CORSO L'INIEZIONE
  if (iniezione == false) {  
    if (funzione == 1) {
      menu(PRESS1, PRESS2);
      if (digitalRead(BUTTON4)==HIGH) {
        while (digitalRead(BUTTON4)==HIGH) {
          lcd.setCursor(0,0);
          lcd.print("MODIFICA        ");
        }
        modifica_tempi(PRESS1, &t_on1, &t_off1);
      }
    }                                             

    else if (funzione == 2) {
      menu(PRESS2, PRESS3);
      if (digitalRead(BUTTON4)==HIGH) {
        while (digitalRead(BUTTON4)==HIGH) {
          lcd.setCursor(0,0);
          lcd.print("MODIFICA        ");
        }
        modifica_tempi(PRESS2, &t_on2, &t_off2);
      }
    }

    else if (funzione == 3) {
      menu(PRESS3, PRESS4);
      if (digitalRead(BUTTON4)==HIGH) {
        while (digitalRead(BUTTON4)==HIGH) {
          lcd.setCursor(0,0);
          lcd.print("MODIFICA        ");
        }
        modifica_tempi(PRESS3, &t_on3, &t_off3);
      }
    }

    else if (funzione == 4) {
      menu(PRESS4, PRESS5);
      if (digitalRead(BUTTON4)==HIGH) {
        while (digitalRead(BUTTON4)==HIGH) {
          lcd.setCursor(0,0);
          lcd.print("MODIFICA        ");
        }
        modifica_tempi(PRESS4, &t_on4, &t_off4);
      }
    }

    else if (funzione == 5) {
      lcd.setCursor(0,0);
      lcd.print("5)SALVA I TEMPI ");
      if (digitalRead(BUTTON4)==HIGH) {
        while (digitalRead(BUTTON4)==HIGH) {}

        // CHIEDE LA CONFERMA PER SOVRASCRIVERE I DATI NELLA EEPROM
        while ((digitalRead(BUTTON4) == LOW) && (digitalRead(BUTTON1) == LOW)) {
          lcd.setCursor(0,0);
          lcd.print("CONFERMI?       ");
          lcd.setCursor(0,1);
          lcd.print("BT4 x CONFERMARE");
        }

        // SOVRASCRIVE I DATI NELLA EEPROM
        if (digitalRead(BUTTON4) == HIGH) {
          while (digitalRead(BUTTON4)==HIGH) {
            lcd.setCursor(0,0);
            lcd.print(" SALVATAGGIO IN ");
            lcd.setCursor(0,1);
            lcd.print("    CORSO...    ");
          }
          scrivi_eeprom(t_on1, 0);
          scrivi_eeprom(t_on2, 1);
          scrivi_eeprom(t_on3, 2);
          scrivi_eeprom(t_on4, 3);
          scrivi_eeprom(t_off1, 4);
          scrivi_eeprom(t_off2, 5);
          scrivi_eeprom(t_off3, 6);
          scrivi_eeprom(t_off4, 7);
          delay(2000);
        }

        // ESCE DAL MENU SENZA SALVARE
        else if (digitalRead(BUTTON1) == HIGH) {
          while (digitalRead(BUTTON1)==HIGH) {
            lcd.setCursor(0,0);
            lcd.print("  SALVATAGGIO   ");
            lcd.setCursor(0,1);
            lcd.print("   ANNULLATO    ");
          }
          delay(2000);
        }
        funzione = 0;
      }
    }
  }

  if (iniezione == false) {
    controlla_bottone();
  }
  
  pressione = leggi_pressione();
  
  if (funzione == 0) {
    visualizza_pressione();
  }

  // AZIONA IL RELE IN BASE ALLA PRESSIONE
  if (pressione <= PRESS1) {
    tempo = millis();
    iniezione = false;
    lcd.setCursor(0,1);
    lcd.print("INIEZIONE: OFF  ");
    digitalWrite(RELE, LOW);
    delay(5);
  }

  else if (pressione < PRESS2) {
    iniezione = true;
    lcd.setCursor(0,1);
    lcd.print("INIEZIONE: ON 1 ");
    rele(t_on1, t_off1);
  }
  
  else if (pressione < PRESS3) {
    iniezione = true;
    lcd.setCursor(0,1);
    lcd.print("INIEZIONE: ON 2 ");
    rele(t_on2, t_off2);
  }
  
  else if (pressione < PRESS4) {
    iniezione = true;
    lcd.setCursor(0,1);
    lcd.print("INIEZIONE: ON 3 ");
    rele(t_on3, t_off3);
  }

  else {
    iniezione = true;
    lcd.setCursor(0,1);
    lcd.print("INIEZIONE: ON 4 ");
    rele(t_on4, t_off4);
  }   

  if (iniezione == false) {
    controlla_bottone();
  }
}

// CONTROLLA SE IL PRIMO PULSANTE VIENE PREMUTO
void controlla_bottone() {
  if (digitalRead(BUTTON1) == true) {
  while (digitalRead(BUTTON1) == true) {
    lcd.setCursor(0,0);
    lcd.print("                ");
  }

    if (funzione >= 5) {
      funzione = 0;
    } else {
      funzione++;
    }
  }
}

// VISUALIZZA LA PRESSIONE NELLA PAGINA INIZIALE
void visualizza_pressione() {
  lcd.setCursor(0,0);
  lcd.print("PRESS:       bar");
  lcd.setCursor(8,0);
  lcd.print(pressione);
}

// ACCENDE E SPEGNE IL RELE
void rele(int t_on, int t_off) {
  ritardo = millis() - tempo;
  t_on -= ritardo;
  
  if (t_on < 0) {
    tempo = millis();
    t_on = 1;
  }
    
  Serial.println(t_on);
  digitalWrite(RELE, LOW);
  delay(t_off);
  digitalWrite(RELE, HIGH);
  delay(t_on);
  tempo = millis();
}

// VISUALIZZA LE PAGINE DEL MENU
void menu(float press_iniz, float press_fin) {
  lcd.setCursor(0,0);
  lcd.print(" )DA     A    ba");
  lcd.setCursor(0,0);
  lcd.print(funzione);
  lcd.setCursor(5,0);
  lcd.print(press_iniz, 1);
  lcd.setCursor(11,0);
  lcd.print(press_fin, 1);
}

// MODIFICA I TEMPI DI INIEZIONE
void modifica_tempi(float press_base, int *t_on, int *t_off) {
  lcd.setCursor(0, 0);
  lcd.print("  INIEZIONE ON  ");
  while (digitalRead(BUTTON4) != true) {
    if (digitalRead(BUTTON2) == true) {
      while (digitalRead(BUTTON2) == true) {}
      *t_on += 50; 
    }

    else if (digitalRead(BUTTON3) == true) {
      while (digitalRead(BUTTON3) == true) {}
      *t_on -= 50; 
    }

    visualizza_modifiche(*t_on, press_base);
  }

  while(digitalRead(BUTTON4) == true) {
    lcd.setCursor(0, 0);
    lcd.print("  INIEZIONE OFF ");
    visualizza_modifiche(*t_off, press_base);
  }
  
  while (digitalRead(BUTTON4) != true) {
    if (digitalRead(BUTTON2) == true) {
      while (digitalRead(BUTTON2) == true) {}
      *t_off += 50; 
    }

    else if (digitalRead(BUTTON3) == true) {
      while (digitalRead(BUTTON3) == true) {}
      *t_off -= 50; 
    }
    
    visualizza_modifiche(*t_off, press_base);
  }
  while (digitalRead(BUTTON4) == true) {
    lcd.setCursor(0, 0);
    lcd.print("  SALVATAGGIO   ");
  }
  funzione = 0;
}

// DURANTE LA MODIFICA, VISUALIZZA LE PRESSIONI "SOGLIA" E I RELATIVI TEMPI
void visualizza_modifiche(int tempo, float press_base) {
    lcd.setCursor(3, 1);
    lcd.print(press_base, 1);  
    lcd.setCursor(0, 1);
    lcd.print("Da ");
    lcd.setCursor(6, 1);
    lcd.print("bar ");
    lcd.setCursor(13, 1);
    lcd.print(" ms");
    lcd.setCursor(10, 1);
    lcd.print(tempo);
}

// SOVRASCRIVE LA EEPROM
void scrivi_eeprom(int valore, int i) {
  EEPROM.update(i*2, highByte(valore));
  EEPROM.update(i*2+1, lowByte(valore));
}

// LEGGE LA EEPROM
int leggi_eeprom(int i) {
  int lettura = EEPROM.read(i*2) * 256 + EEPROM.read(i*2+1);
  return lettura;
}

// LEGGE LA PRESSIONE DAL SENSORE
float leggi_pressione() {
  return loadcell.get_units(5) / 100 * 1.8;
}

