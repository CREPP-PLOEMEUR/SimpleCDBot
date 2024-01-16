//.. entête déclarative des constantes et variable globales
const int LED=3;  // constante désignant la broche de la LED
int vitesse=20;  //  variable fixant la durée de pause en msen ms
int largeur=0;   //  variable pour la largeur d'impulsion

void setup() {
  pinMode(LED, OUTPUT);  // met la broche en sortie
  
}

void loop() {
  for (int i=0; i<=100; i++) {  // boucle croissante
    largeur=map(i,0,100,0,255);  // re-échelonne i (0,100%) vers (0,255)
    analogWrite(LED, largeur);   // génère l'impulsion PWM voulue sur la broche
    delay(vitesse);              // pause
  } 
  for (int i=100; i>=0; i--) {   // boucle décroissante
    largeur=map(i,0,100,0,255);  // ré-échelonne i (0,100%) vers (0,255)
    analogWrite(LED,largeur);    // génère l'impulsion PWM voulue sur la broche
    delay(vitesse);              // pause
  }
  
}

