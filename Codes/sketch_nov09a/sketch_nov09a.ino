// controle de 2 servomoteurs par capteur GP2D12

// inclusion de librairies

#include <Servo.h>        // inclut la librairie Utils librairie personnelle avec plusieurs fonctions utiles

#include <Utils.h>        // inclut la librairie Servo

#include <SimpleCDbot.h>  // inclut la librairie Simple CDbot librairie personnelle avec fonctions de controle d'un robot à 2 servo RC

 // variables pour réception chaines sur port Serie
int octetReception=0; // variable de reception octet
char caractereReception=0; // variable de reception caractere
String chaineReception=""; // declare un objet string vide

// variables et constantes pour les servomoteurs
const int Droit=0; // servo Droit à l'indice 0
const int Gauche=1; // servo Gauche à l'indice 1

const int neutre=1420; // largeur de l'impulsion arret
const int maxAV[2]={1220,1620}; // largeur impulsion vitesse max en Avant
const int maxAR[2]={1620,1220}; // largeur impulsion vitesse max en Arriere

const int brocheServo[2]={14,15}; // broches des servomoteurs

// pour le GP2D12

const int GP2D12=A2; // déclaration constante de broche analogique

// déclaration des variables globales
int mesure_brute=0; // variable pour acquisition résultat brut de conversion analogique numérique
float mesuref=0.0; // variable pour calcul résultat décimal de conversion analogique numérique

int distance; // distance référence
 
// tableau des valeurs en millivolts pour distance de 5 en 5 cm de 10 à 80 cm pour le capteur GP2D12
// 1ère valeur à l'index 0
int calibrage[]={  // valeurs en mV
2370,  // 10 cm - index 0
1700,  // 15 cm - index 1
1300,  // 20 cm - index 2
1100,  // 25 cm - index 3
950,   // 30 cm - index 4
830,   // 35 cm - index 5
720,   // 40 cm - index 6
650,   // 45 cm - index 7
580,   // 50 cm - index 8
540,   // 55 cm - index 9
500,   // 60 cm - index 10
480,   // 65 cm - index 11
450,   // 70 cm - index 12
430,   // 75 cm - index 13
410,   // 80 cm - index 14
400,   // au delà de 80 cm - index 15
}; // fin du tableau

int impulsServo=0; // largeur impulsion servomoteur en µsecondes

Servo servo[2]; // déclaration d'un objet servomoteur
Utils utils;
SimpleCDbot robot(brocheServo[Droit], maxAR[Droit], maxAV[Droit], brocheServo[Gauche], maxAR[Gauche], maxAV[Gauche], neutre);

boolean debug=true;
boolean etatMoteurs=false; // temoin etat moteur
boolean detectObstacle=false; // temoin détection obstacle

//....la fonction setup(): éxécutée au début et une seule fois
void setup() {
  
  Serial.begin(115200); // initialise la vitesse de la connection série
                        // utilise la mme vitesse dans le terminal Série
       
  robot.infosAnalyseChaine(); // infos sur les chaines reconnues par analyseChaine
  
} // fin de la fonction setup()

// .....la fonction loop(): exécutée en boucle sans fin
void loop() {
  
  // réception de chaine sur le port Série et analyse de la chaine
  
  chaineReception=utils.waitingString(true); // appelle la fonction de réception sur le port Série
  // if (chaineReception!="") analyseChaine(chaineReception); // analyse la fonction d'analyse de la chaine en réception
  // if (chaineReception!="") robot.analyseChaine(chaineReception); // appelle la fonction d'analyse de la chaine en reception
  
  // la fonction analyse chaine "décode" la chaine et appelle la fonction de la lib. RobotCCx2 voulue si la chaine est valide
  
   if (chaineReception!="") robot.analyseChaine(chaineReception); // appelle la fonction d'analyse de la chaine en réception
   
  mesuref = moyenneMesure(30, GP2D12); // réalise la moyenne de 30 mesure analogiques sur voie GP2D12
  distance = distanceGP2D12(mesuref); // renvoie la valeur de la distance correspondante à la valeur tension
  
  //.....affichage du résultat...
  
  if (distance==0) {  // si la valeur ne correspond pas au calibrage
    if (debug) Serial.println("Distance hors plage de mesure");
    
    if ( (etatMoteurs==false) || (detectObstacle==true) ) {  // allume moteurs
      robot.enAvant(100);
      etatMoteurs=true;
      detectObstacle=false;
    }
  }
  
  else {  // si la valeur distance calculée
    if (debug) Serial.print("Distance comprise entre"), Serial.print(distance), Serial.print(" cm et ");
    if (debug) Serial.print(distance+5), Serial.println(" cm ");
    if (distance<30) {
      
      if (etatMoteurs==true) { // si moteur allumé
        robot.arret(1000);
        robot.enArriere(50,1000); // recule pendant 1 seconde
        etatMoteurs=false; // on laisse à true jusqu'à distance sup 30 suivante
        detectObstacle=true;
      } // fin de moteurs==true
      
    } // fin de if < à 30
    
    else if (distance>=20) {
      
         if (detectObstacle==true) {  // si moteurs allumés = si gestion distance <30 toujours en cours
           robot.tourneDroite(50, 1000);
           etatMoteurs=false;
           detectObstacle=false; // plus d'obstacle
         } // fin de if
         
         if (etatMoteurs==false) {  // allume moteirs
           robot.enAvant(100);
           etatMoteurs=true;
         } // fin de if moteurs false
         
    } // fin de else if distance
    
  } // fin de else
  
  delay(250); // pause entre 2 mesures
  
} // fin de la fonction loop()

//======autres fonctions=======

//...fonction réalisant une moyenne de n mesures analogiques sur voie analogique

 float moyenneMesure(int nombreMesure, int voie) {  // fonction réalisant une moyenne de n mesures analogiques
 
 //...variables locales...
 
 int mesure_can=0;
 long cumul_can=0;
 int moyenne_can=0;
 float mesure_canf=0;
 
 //... calcul d'une moyenne de plusieurs mesures...
 
 for (int i=0; i<nombreMesure; i++) { // répète la mesure n fois
 
  mesure_can=analogRead(voie);
  cumul_can=cumul_can+mesure_can;
 }
 
 if (debug) Serial.print("cumul="), Serial.println(cumul_can);
 
 // calcul de la moyenne
 
 moyenne_can=cumul_can/nombreMesure;
 cumul_can=0; // RAZ cumul...
  if (debug) Serial.print("moyenne="), Serial.println(moyenne_can);
  
 // mesure de la tension correspondante en mV
 
 mesure_canf=float(moyenne_can);
 mesure_canf=mesure_canf*5000.0;
 mesure_canf=mesure_canf/1023.0;
 
   if (debug) Serial.print("tension="), Serial.print(mesure_canf);
   
   return (mesure_canf); // valeur renvoyée par la fonction
   
 } // fin de la fonction moyenneMesure
 
//...fonction renvoyant la distance en fonction de la mesure analogique GP2D12....

// cette fonction est nécessaire car la fonction analogique du GP2D12 n'est la linéaire

  int distanceGP2D12(float mesure_float) {
    int dist=0; // raz variable locale distance
    
// ....détermination de la distance à partir du tableau de référence

  for (int j=0; j<=14; j++) { // teste les valeurs de calibrage
  
    if ((int(mesure_float)<=calibrage[j]) && (int(mesure_float)>calibrage[j+1])) { // si la mesure comprise entre 2 valeurs
       dist=10+(j*5);  // calcule la distance en cm à partir de l'index courant
    }
  } // fin de la boucle test de calibrage
  
  return (dist);  // valeur renvoyée par la fonction
  
  }  // ..............fin de la fonction analyse distance GP2D12....
 




