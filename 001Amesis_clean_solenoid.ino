//22/06/2019 
//Amesis Project 
//https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?view_as=subscriber
//https://create.arduino.cc/projecthub/AmesisProject/001-amesis-clean-solenoid-d1f4ee
//Amesis_clean_solenoid_V2.0

//*************************
//Declaration des variables
//*************************

float TI ;        // Temps d'ouverture et de fermeture de l'injecteur
int Led = 13 ;    // Led Temoin elle indique que le relai 1 est a ON et que le relais2 et a OFF
int Relais1 = 4 ; // Relais 5v arduino ouveture normal (quand la led est allume le relais est a ON)
int Relais2 = 7 ; // Relais Arduino 5 v ouverture inverse (quand la led est eteinte le relais est a ON)
long Potar = A2 ; // Potentiometre pour fair varier le TI entre 0 et 10 seconde par palier d'une seconde
float PotarValeur ;

//*****************
//Setup
//*****************

void setup() {
 
  Serial.begin(9600);         // Ouverture port Serie
  pinMode(Led, OUTPUT);       // Led en sortie
  pinMode(Relais1, OUTPUT);   // relais 1 en sortie
  pinMode(Relais2, OUTPUT);   // relais 2 en sortie
  pinMode(Potar, INPUT);      // pontentiometre en entre

  //Temoin d'initialisation de la fin du setup
  digitalWrite(Led, HIGH);
  delay(100);
  digitalWrite(Led, LOW);
  delay(200);
  digitalWrite(Led, HIGH);
  delay(100);
  digitalWrite(Led, LOW);
  delay(200);
  digitalWrite(Led, HIGH);
  delay(100);
  digitalWrite(Led, LOW);
  delay(200);
  digitalWrite(Led, HIGH);
  delay(1000);
  digitalWrite(Led, LOW);
  delay(1000);
}

//****************
//Loop
//*****************
void loop() {
  PotarValeur = analogRead (Potar);    //lecture du potentiometre valeur de 0 = 1023
  TI = map(PotarValeur,0,1023,1,50);  // convertion proportionnelle de 0-1023 a 1-50
  Serial.println(TI);                  //envoie la valeur TI sur le port serie
  digitalWrite(Led, HIGH);             // Allume la led
  digitalWrite(Relais1, HIGH);         // Relais 1 en action
  digitalWrite(Relais2, LOW);          // relais 2 en repos
  delay (TI*25);                       //Valeur pour regler la rapidité d'ouverture
  digitalWrite(Led, LOW);              // Extinction de la led
  digitalWrite(Relais1, LOW);          // relais 1 en repos
  digitalWrite(Relais2, HIGH);         // relais 2 en action
  delay (TI*25);                       //Valeur pour regler la rapidité de fermeture
}
