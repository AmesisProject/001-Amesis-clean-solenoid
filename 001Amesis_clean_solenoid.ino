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
float         PotarValeur;        // Valeur brute de lecture [0;1023]
unsigned long g_time_cycle_start; // Temps lors du demarrage du cycle
unsigned long g_delay;            // Temps d'ouverture et de fermeture de l'injecteur
unsigned int  g_cycle;            // identification du cycle [0;1]

//*****************
//Setup
//*****************

void setup() {
 
  Serial.begin(9600);             // Ouverture port Serie
  pinMode(PIN_LED, OUTPUT);       // Led en sortie
  pinMode(PIN_RELAIS_1, OUTPUT);  // relais 1 en sortie
  pinMode(PIN_RELAIS_2, OUTPUT);  // relais 2 en sortie
  pinMode(PIN_POTAR, INPUT);      // pontentiometre en entre

  g_cycle = LOW;
  g_time_cycle_start = millis();

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
  long  l_act_time = millis();

  PotarValeur = analogRead(PIN_POTAR);  // lecture du potentiometre valeur de 0 = 1023
  g_delay = map(PotarValeur * PotarValeur,0,1056529,20,2000); // convertion quadratique ramenant entre 20ms et 2s de temporisation (de 50Hz a 0.5Hz)

  if (g_time_cycle_start + g_delay < l_act_time)
  {
    g_time_cycle_start = l_act_time;
    g_cycle = !g_cycle;                   // Inversion de la valeur des relais
    Serial.println(g_delay);              // envoie la valeur de la temporisation sur le port serie
    digitalWrite(PIN_LED, g_cycle);       // Allume la led
    digitalWrite(PIN_RELAIS_1, g_cycle);  // Relais 1 en action
    digitalWrite(PIN_RELAIS_2, !g_cycle); // relais 2 en repos
  }
}
