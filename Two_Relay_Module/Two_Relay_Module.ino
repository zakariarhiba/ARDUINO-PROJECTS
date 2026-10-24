/*
 * Projet : commander une lampe 220 V avec un module relais et un bouton
 * Zakpy Academy - RHIBA Zakaria
 * Carte : Arduino Uno ou Mega
 *
 * Le module relais s'active quand son entrée IN1 est à LOW (c'est le cas
 * de la plupart des modules 2 relais). Le bouton est branché entre la
 * broche 9 et le GND, avec la résistance de pull-up interne de l'Arduino :
 * bouton appuyé = LOW, bouton relâché = HIGH.
 *
 * ATTENTION : le côté 220 V du relais est dangereux. On câble tout
 * hors tension, et on ne touche jamais aux bornes quand c'est branché.
 */

#define RELAY_IN1 8   // l'entrée IN1 du module relais
#define BUTTON1   9   // le bouton qui commande le relais

void setup() {
  pinMode(RELAY_IN1, OUTPUT);
  digitalWrite(RELAY_IN1, HIGH);    // relais au repos au démarrage
  pinMode(BUTTON1, INPUT_PULLUP);   // pull-up interne
}

void loop() {
  int button1Value = digitalRead(BUTTON1);   // on lit l'état du bouton

  if (button1Value == LOW) {
    digitalWrite(RELAY_IN1, LOW);    // bouton appuyé : relais activé, lampe allumée
  } else {
    digitalWrite(RELAY_IN1, HIGH);   // bouton relâché : relais au repos, lampe éteinte
  }
}
