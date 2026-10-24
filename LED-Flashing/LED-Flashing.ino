/*
 * Projet : faire clignoter une LED
 * Zakpy Academy - RHIBA Zakaria
 * Carte : Arduino Uno ou Mega
 *
 * La LED est branchée sur la broche 8, avec une résistance de 220 ohms.
 */

#define LED 8              // la broche de la LED

void setup() {
  pinMode(LED, OUTPUT);    // la broche de la LED est une sortie
}

void loop() {
  digitalWrite(LED, HIGH); // on allume la LED
  delay(1000);             // on attend 1 seconde
  digitalWrite(LED, LOW);  // on éteint la LED
  delay(1000);             // on attend 1 seconde
}
