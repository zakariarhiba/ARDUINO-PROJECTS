---
title: "Mesurer la température et l'humidité avec un DHT11"
slug: "capteur-dht11"
order: 4
level: "Débutant"
duration: "20 min"
board: "Arduino Uno ou Mega"
description: "On lit la température et l'humidité avec un capteur DHT11 et on les affiche sur le moniteur série toutes les 2 secondes."
notions: ["bibliothèques Arduino", "capteur numérique", "moniteur série"]
components: ["Arduino Uno ou Mega", "capteur DHT11 (ou module DHT11)", "résistance 10 kΩ si capteur nu", "breadboard et fils"]
tags: ["capteur", "température", "humidité", "dht11"]
youtube: ""
code: "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/TEMPERATURE_Sensor_dht/TEMPERATURE_Sensor_dht.ino"
resources:
  - label: "Bibliothèque DHT sensor library (Adafruit)"
    url: "https://github.com/adafruit/DHT-sensor-library"
  - label: "Bibliothèque Adafruit Unified Sensor"
    url: "https://github.com/adafruit/Adafruit_Sensor"
github: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/TEMPERATURE_Sensor_dht"
author: "RHIBA Zakaria"
updated: "2026-10-24"
---

# **Mesurer la température et l'humidité avec un DHT11**

```
Projet Arduino n°4 : capteur DHT11
Écrit par RHIBA Zakaria, Zakpy Academy
```

*Dans ce projet on utilise un capteur DHT11 pour mesurer la température et l'humidité. Les valeurs s'affichent sur le moniteur série toutes les 2 secondes. Il faut donc ouvrir le moniteur série de l'IDE Arduino après avoir téléversé le programme.*

## **Ce qu'on va apprendre**

___

- Installer et utiliser une bibliothèque Arduino.
- Lire un capteur numérique.
- Vérifier qu'une mesure a bien marché avec `isnan()`.

## **Le matériel**

___

- Une carte Arduino Uno ou Mega
- Un capteur DHT11 (ou un module DHT11 sur petite carte)
- Une résistance de 10 kΩ si le capteur est nu (le module l'a déjà)
- Une breadboard et des fils

## **Les bibliothèques**

___

Dans l'IDE Arduino, ouvre le gestionnaire de bibliothèques et installe :

- **DHT sensor library** d'Adafruit : [github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
- **Adafruit Unified Sensor** : [github.com/adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

## **Le câblage**

___

Le DHT11 a 3 broches utiles : VCC, GND, et DATA qui envoie les mesures. On branche DATA sur la broche 5.

| DHT11 | Arduino |
|---|---|
| VCC | 5 V |
| DATA | broche 5 (avec 10 kΩ vers le 5 V si capteur nu) |
| GND | GND |

## **Initialiser le capteur**

___

On inclut la bibliothèque, on indique la broche et le type de capteur, puis on crée l'objet `dht` :

```C++
#include "DHT.h"

#define DHTPIN  5        // la broche DATA
#define DHTTYPE DHT11    // DHT11, DHT21 ou DHT22

DHT dht(DHTPIN, DHTTYPE);
```

## **La fonction setup()**

___

On démarre la communication série et le capteur :

```C++
void setup() {
  Serial.begin(9600);
  dht.begin();
}
```

## **La fonction loop()**

___

On lit la température (en °C) et l'humidité (en %) :

```C++
float t = dht.readTemperature();
float h = dht.readHumidity();
```

Si la lecture a raté, la valeur est `NaN` (pas un nombre). On le vérifie avec `isnan()` et on affiche un message d'erreur :

```C++
if (isnan(t) || isnan(h)) {
  Serial.println("Erreur de lecture du DHT11 !");
  delay(2000);
  return;
}
```

Sinon on affiche les mesures, et on attend 2 secondes : le DHT11 a besoin de ce temps entre deux mesures.

## **Le code complet**

___

```C++
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
```

## **Pour aller plus loin**

___

- Affiche la température sur un écran LCD à la place du moniteur série.
- Passe au DHT22, plus précis : il suffit de changer `DHT11` en `DHT22`.
- Compare avec le capteur LM35 du projet [Thermomètre numérique avec alarme](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35).

___

Tous les cours et les vidéos sont sur **[Zakpy Academy](https://academy.zakpy.com)**.

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zakariarhiba.tech)
