//22/06/2019 
//Amesis Project 
//https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?view_as=subscriber
//https://create.arduino.cc/projecthub/AmesisProject/001-amesis-clean-solenoid-d1f4ee
//Amesis_clean_solenoid_V2.0

//*************************
// Constantes
//*************************
#define K_TIME_COEF   25  // Coefficient de multiplication du temps d'activation des relais
#define PIN_LED       13  // Led Temoin elle indique que le relai 1 est a ON et que le relais2 et a OFF
#define PIN_RELAIS_1  4   // Relais Arduino 5v ouveture normal (quand la led est allume le relais est a ON)
#define PIN_RELAIS_2  7   // Relais Arduino 5v ouverture inverse (quand la led est eteinte le relais est a ON)
#define PIN_POTAR     A2  // Potentiometre pour fair varier le TI entre 0 et 10 seconde par palier d'une seconde

//*************************
//Declaration des variables globales
//*************************
float TI;                 // Temps d'ouverture et de fermeture de l'injecteur
float PotarValeur;        // Valeur brute de lecture [0;1023]

//*****************
//Setup
//*****************

void setup() {
 
  Serial.begin(9600);             // Ouverture port Serie
  pinMode(PIN_LED, OUTPUT);       // Led en sortie
  pinMode(PIN_RELAIS_1, OUTPUT);  // relais 1 en sortie
  pinMode(PIN_RELAIS_2, OUTPUT);  // relais 2 en sortie
  pinMode(PIN_POTAR, INPUT);      // pontentiometre en entre

  //Temoin d'initialisation de la fin du setup
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  digitalWrite(PIN_LED, LOW);
  delay(200);
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  digitalWrite(PIN_LED, LOW);
  delay(200);
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  digitalWrite(PIN_LED, LOW);
  delay(200);
  digitalWrite(PIN_LED, HIGH);
  delay(1000);
  digitalWrite(PIN_LED, LOW);
  delay(1000);
}

//****************
//Loop
//*****************
void loop() {
  PotarValeur = analogRead(PIN_POTAR);  //lecture du potentiometre valeur de 0 = 1023
  TI = map(PotarValeur,0,1023,1,50);    // convertion proportionnelle de 0-1023 a 1-50
  Serial.println(TI);                   //envoie la valeur TI sur le port serie
  digitalWrite(PIN_LED, HIGH);          // Allume la led
  digitalWrite(PIN_RELAIS_1, HIGH);     // Relais 1 en action
  digitalWrite(PIN_RELAIS_2, LOW);      // relais 2 en repos
  delay (TI * K_TIME_COEF);             //Valeur pour regler la rapidité d'ouverture
  digitalWrite(PIN_LED, LOW);           // Extinction de la led
  digitalWrite(PIN_RELAIS_1, LOW);      // relais 1 en repos
  digitalWrite(PIN_RELAIS_2, HIGH);     // relais 2 en action
  delay (TI * K_TIME_COEF);             //Valeur pour regler la rapidité de fermeture
}
