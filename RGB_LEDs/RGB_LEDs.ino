/*
 * Projet : changer la couleur de deux LED RGB avec une struct
 * Zakpy Academy - RHIBA Zakaria
 * Carte : Arduino Uno ou Mega
 *
 * LED RGB à cathode commune : la broche commune va au GND,
 * et chaque couleur passe par une résistance de 220 ohms.
 */

// Une LED RGB, c'est 3 broches : rouge, vert et bleu
struct RGB {
  int red;
  int green;
  int blue;
};

RGB led1 = {9, 10, 11};   // broches de la première LED
RGB led2 = {5, 6, 7};     // broches de la deuxième LED

// Met les 3 broches d'une LED en sortie
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}

// Allume la couleur rouge seulement
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}

// Allume la couleur verte seulement
void green(RGB led) {
  digitalWrite(led.red, LOW);
  digitalWrite(led.green, HIGH);
  digitalWrite(led.blue, LOW);
}

// Allume la couleur bleue seulement
void blue(RGB led) {
  digitalWrite(led.red, LOW);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, HIGH);
}

void setup() {
  SetupLed(led1);
  SetupLed(led2);
}

void loop() {
  red(led1);    red(led2);    delay(1000);   // rouge pendant 1 s
  green(led1);  green(led2);  delay(1000);   // vert pendant 1 s
  blue(led1);   blue(led2);   delay(1000);   // bleu pendant 1 s
}
