/*
 * Projet : mesurer la température et l'humidité avec un DHT11
 * Zakpy Academy - RHIBA Zakaria
 * Carte : Arduino Uno ou Mega
 *
 * Bibliothèques à installer (gestionnaire de bibliothèques de l'IDE Arduino) :
 *   - DHT sensor library (Adafruit)
 *   - Adafruit Unified Sensor
 */

#include "DHT.h"

#define DHTPIN  5        // la broche DATA du DHT11
#define DHTTYPE DHT11    // DHT11, DHT21 ou DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Test du DHT11");
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();   // température en °C
  float h = dht.readHumidity();      // humidité en %

  // si la lecture a raté, on affiche un message et on recommence
  if (isnan(t) || isnan(h)) {
    Serial.println("Erreur de lecture du DHT11 !");
    delay(2000);
    return;
  }

  Serial.print("Temperature : ");
  Serial.print(t);
  Serial.print(" C   Humidite : ");
  Serial.print(h);
  Serial.println(" %");

  delay(2000);   // le DHT11 a besoin d'environ 2 s entre deux mesures
}
