// Etalonnage des servomoteurs à rotation continue du Simple CD-Bot

// Entête déclarative = variables et constantes globales

// inclusion de librairies
#include <Servo.h>
#include <Utils.h>
#include <SimpleCDbot.h>

// variables pour réception chaîne sur port Série
// int octetReception=0; // variable de reception octet
// char caracterReception=0; // variable de reception caractere
String chaineReception=""; // déclare un objet String vide

// variables et constantes pour les servomoteurs
const int Droit=0; // servo Droit à l'indice 0
const int Gauche=1; // servo Gauche à l'indice 1

const int neutre=1420; // largeur impulsion arrêt
const int maxAV[2]={1220, 1620}; // largeur impulsion vitesse max en avant
const int maxAR[2]={1620, 1220}; // largeur impulsion vitesse max en arrière

const int brocheServo[2]={14, 15}; // broches des servomoteur

// int impulsServo=0; // largeur impulsion des servomoteurs en µsecondes
// Servo servo[2]; // déclaration d'un objet servomoteur

Utils utils;

SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit], brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre);

// la fonction setup(): exécutée en premier et une seule fois
void setup() {
  
  Serial.begin(115200); // initialise la vitesse de la communication série
                        // utilise la même vitesse dans le Terminal Serie
       
  robot.infosAnalyseChaine(); //infos sur les chaines reconnues par la fonction analyse chaine
  
}  // fin de la fonction setup()

// la fonction loop(): exécutée en boucle sans fin
void loop() {
  
  // réception de chaine sur le port série et analyse de chaine
  
  chaineReception=utils.waitingString(true); // appelle la fonction de reception sur le port série
  if (chaineReception!="") robot.analyseChaine(chaineReception); // appelle la fonction d'analyse de la chaine en reception
  
}  // fin de la fonction loop()




