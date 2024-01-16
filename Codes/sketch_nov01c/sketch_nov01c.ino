// modifie l'aspect du curseur d'un afficheur LCD

// ....entete déclarative...
#include <LiquidCrystal.h> // inclusion de la librairie LCD

// déclaration des broches de l'afficheur
const int R5=2; // broche R5
const int E=3;  // broche E
const int D4=4; // broche D4
const int D5=5; // broche D5
const int D6=6; // broche D6
const int D7=7; // broche D7

LiquidCrystal lcd(R5,E,D4,D5,D6,D7); // déclare un objet représentant lcd

//....la fonction setup(): éxécutée en prepier et en une seule fois
void setup() {
  
  lcd.begin(16, 2); // initialise LCD ( colonnes x lignes )
  lcd.clear();      // efface LCD et se place en 0.0
  delay(10);    // courte pause après clear()
  lcd.print("LCD OK!"); // affiche le message
  delay(1000);  // pause
  
} // fin de la fonction setup()

// ...la fonction loop(): éxécutée en boucle sans fin
void loop() {
  
  lcd.clear();  // efface LCD et se place en 0.0
  delay(10);    // courte pause après clear()
  lcd.noCursor(); // désactive le trait de base
  lcd.noBlink(); // désactive le clignotement
  lcd.print("noCursor+noBlink"); // affiche le message
  delay(4000); // pause
  
  lcd.clear(); // efface LCD et se place en 0.0
  delay(10); // courte pause après clear()
  lcd.cursor(); // active le trait de base
  lcd.print("Cursor seul"); // affiche le message
  delay(4000);  // pause
  
  lcd.clear(); // efface LCD et se place en 0.0
  delay(10);   // courte pause après clear()
  lcd.noCursor(); // désactive le trait de base
  lcd.blink(); // active le clignotement
  lcd.print("Blink seul"); // affiche le message
  delay(4000); // pause
  
  lcd.clear(); // efface LCD et se place en 0.0
  delay(10); // courte pause après clear()
  lcd.cursor(); // active le trait de base
  lcd.blink(); // active le clignotement
  lcd.print("Cursor+Blink"); // affiche le message
  delay(4000); // pause
  
} // fin de la fonction loop()


