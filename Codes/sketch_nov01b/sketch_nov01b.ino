// faire clignoter l'affichage sur l'afficheur LCD

//....entete déclarative
#include <LiquidCrystal.h>

// déclaration des broches de l'afficheur
const int R5=2; // broche R5
const int E=3;  // broche E
const int D4=4; // broche D4
const int D5=5; // broche D5
const int D6=6; // broche D6
const int D7=7; // broche D7

LiquidCrystal lcd(R5,E,D4,D5,D6,D7); // déclaration d'un objet représentant lcd

//.....la fonction setup(): éxécutée en premier et en une seule fois
void setup() {
  
  lcd.begin(16,2); // initialise LCD ( colonnes X lignes )
  lcd.clear();     // efface LCD et se place en 0.0
  lcd.print("Display/noDispl"); // affiche le message
  
} // fin de la fonction setup()

//....la fonction loop(): éxécutée en boucle sans fin
void loop() {
  
  lcd.display(); // active l'affichage LCD (sans modifier le message)
  delay(1000); // pause
  
  lcd.noDisplay(); // désactive l'affichage LCD (sans modifier le message)
  delay(1000); // pause
  
} // fin de la fonction loop()


