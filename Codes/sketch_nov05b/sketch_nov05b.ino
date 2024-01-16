// Test de fonctionnement des servomoteurs par le port série

//  Inclusion de librairies

#include <SimpleCDbot.h>
#include <Utils.h>
#include <Servo.h>

//  Variables pour réception chaine sur port série
// int octetReception=0; // variable de réception octet
// char caractereReception=0; // variable de réception caractère

String chaineReception=""; // déclare un objet réception vide

// variables et constantes pour les servomoteurs

const int Droit=0; // servo Droit à l'indice 0
const int Gauche=1; // servo Gauche à l'indice 1

const int neutre=1395; // largeur impulsion arrêt
const int maxAV[2]={1220, 1620}; // largeur impulsion max vitesse en avant
const int maxAR[2]={1620, 1220}; // largeur impulsion max vitesse en arrière

const int brocheServo[2]={14, 15}; // broches des servomoteurs

// int impulsServo=0; // largeur de l'impulsion servomoteur en µsecondes
// Servo servo[2]; // déclaration d'un objet servomoteur

Utils utils;

SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit], brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre);

// la fonction setup(): exécutée au début et en une seule fois
void setup() {
  
  Serial.begin(115200); // initialise la vitesse de la connexion série
                        // utilise la même vitese dans le terminal série
  robot.infosAnalyseChaine();  // infos sur les chaines reconnues par la fonction analyse chaine
  
}  // fin de la fonction setup()

// la fonction loop(): exécutée en boucle sans fin
void loop() {
  
  // réception chaine sur le port série et analyse de la chaine
  
  chaineReception=utils.waitingString(true); // appelle la fonction réception sur le port série
  
  if (chaineReception!="") robot.analyseChaine(chaineReception);  // appelle la fonction d'analyse de la chaine en réception
  
} // fin de la fonction loop()




