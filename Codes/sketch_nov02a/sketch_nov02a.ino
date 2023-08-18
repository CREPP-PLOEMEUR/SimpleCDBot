const int PIEZO=2;
int DO=262;
int RE=294;
int MI=330;

const int nombreNotes=11;
int note[nombreNotes]={DO,DO,DO,RE,MI,RE,DO,MI,RE,RE,DO};
int duree[nombreNotes] = {1,1,1,1,1,2,1,1,1,1,1};

void setup() {
  pinMode(PIEZO, OUTPUT);

}

void loop() {
  for (int i=0; i<nombreNotes; i++) {
    tone(PIEZO, note[i]);
    delay(500*duree[i]);
    noTone(PIEZO);
    delay(100);
    
  }
    noTone(PIEZO);
    delay(1000);
  
  
  
  
  
}


