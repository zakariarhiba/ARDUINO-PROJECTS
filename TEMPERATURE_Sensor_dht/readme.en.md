---
title: "Measure temperature and humidity with a DHT11"
description: "We read the temperature and humidity with a DHT11 sensor and show them on the serial monitor every 2 seconds."
board: "Arduino Uno or Mega"
notions: ["Arduino libraries", "digital sensor", "serial monitor"]
components: ["Arduino Uno or Mega", "DHT11 sensor (or DHT11 module)", "10 kΩ resistor for a bare sensor", "breadboard and wires"]
resources:
  - label: "DHT sensor library (Adafruit)"
    url: "https://github.com/adafruit/DHT-sensor-library"
  - label: "Adafruit Unified Sensor library"
    url: "https://github.com/adafruit/Adafruit_Sensor"
---

# **Measure temperature and humidity with a DHT11**

```
Arduino project no. 4: DHT11 sensor
Written by RHIBA Zakaria, Zakpy Academy
```

*In this project we use a DHT11 sensor to measure the temperature and the humidity. The values show on the serial monitor every 2 seconds, so open the serial monitor of the Arduino IDE after uploading the program.*

## **What you will learn**

___

- Install and use an Arduino library.
- Read a digital sensor.
- Check that a measurement worked with `isnan()`.

## **What you need**

___

- An Arduino Uno or Mega board
- A DHT11 sensor (or a DHT11 module on a small board)
- A 10 kΩ resistor if the sensor is bare (the module already has it)
- A breadboard and wires

## **The libraries**

___

In the Arduino IDE, open the library manager and install:

- **DHT sensor library** by Adafruit: [github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
- **Adafruit Unified Sensor**: [github.com/adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

## **Wiring**

___

The DHT11 has 3 useful pins: VCC, GND, and DATA, which sends the measurements. We connect DATA to pin 5.

| DHT11 | Arduino |
|---|---|
| VCC | 5 V |
| DATA | pin 5 (with 10 kΩ to 5 V for a bare sensor) |
| GND | GND |

## **Starting the sensor**

___

We include the library, give the pin and the sensor type, then create the `dht` object:

```C++
#include "DHT.h"

#define DHTPIN  5        // la broche DATA
#define DHTTYPE DHT11    // DHT11, DHT21 ou DHT22

DHT dht(DHTPIN, DHTTYPE);
```

## **The setup() function**

___

We start the serial communication and the sensor:

```C++
void setup() {
  Serial.begin(9600);
  dht.begin();
}
```

## **The loop() function**

___

We read the temperature (in °C) and the humidity (in %):

```C++
float t = dht.readTemperature();
float h = dht.readHumidity();
```

If the reading failed, the value is `NaN` (not a number). We check it with `isnan()` and print an error message:

```C++
if (isnan(t) || isnan(h)) {
  Serial.println("Erreur de lecture du DHT11 !");
  delay(2000);
  return;
}
```

Otherwise we print the measurements and wait 2 seconds: the DHT11 needs that time between two measurements.

## **The full code**

___

The comments and messages in the code are in French, like the `.ino` file you download.

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

## **Going further**

___

- Show the temperature on an LCD screen instead of the serial monitor.
- Move to the DHT22, which is more accurate: just change `DHT11` to `DHT22`.
- Compare with the LM35 sensor of the project [Digital thermometer with an alarm](https://academy.zakpy.com/projects/arduino/thermometre-lm35-7-segments/).
