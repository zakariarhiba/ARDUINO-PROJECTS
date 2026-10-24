---
title: "نقيسو الحرارة والرطوبة ب DHT11"
description: "كنقراو الحرارة والرطوبة ب capteur DHT11 وكنبينوهم ف الـ moniteur série كل 2 ثواني."
board: "Arduino Uno ولا Mega"
notions: ["bibliothèques Arduino", "capteur رقمي", "moniteur série"]
components: ["Arduino Uno ولا Mega", "capteur DHT11 (ولا module DHT11)", "résistance ديال 10 kΩ إلى كان الـ capteur عريان", "breadboard وفيلات"]
resources:
  - label: "Bibliothèque DHT sensor library (Adafruit)"
    url: "https://github.com/adafruit/DHT-sensor-library"
  - label: "Bibliothèque Adafruit Unified Sensor"
    url: "https://github.com/adafruit/Adafruit_Sensor"
---

# **نقيسو الحرارة والرطوبة ب DHT11**

```
مشروع Arduino رقم 4: capteur DHT11
كتبو RHIBA Zakaria، Zakpy Academy
```

*ف هاد المشروع كنخدمو ب capteur DHT11 باش نقيسو الحرارة والرطوبة. القيم كيبانو ف الـ moniteur série كل 2 ثواني، إذن خاصك تحل الـ moniteur série ديال IDE Arduino من بعد ما تطيليفيرسي البرنامج.*

## **شنو غادي نتعلمو**

___

- نستاليو ونخدمو ب bibliothèque ديال Arduino.
- نقراو capteur رقمي.
- نتأكدو بلي القياس داز مزيان ب `isnan()`.

## **الماتيريال**

___

- كارطة Arduino Uno ولا Mega
- capteur DHT11 (ولا module DHT11 على كارطة صغيرة)
- résistance ديال 10 kΩ إلى كان الـ capteur عريان (الـ module فيه ديجا)
- breadboard وفيلات

## **الـ bibliothèques**

___

ف IDE Arduino، حل الـ gestionnaire de bibliothèques وستالي:

- **DHT sensor library** ديال Adafruit: [github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
- **Adafruit Unified Sensor**: [github.com/adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

## **التوصيل**

___

DHT11 عندو 3 pins اللي كنحتاجو: VCC، GND، و DATA اللي كيصيفط القياسات. كنوصلو DATA ب pin 5.

| DHT11 | Arduino |
|---|---|
| VCC | 5 V |
| DATA | pin 5 (مع 10 kΩ ل 5 V إلى كان الـ capteur عريان) |
| GND | GND |

## **نبداو الـ capteur**

___

كنزيدو الـ bibliothèque، كنعطيو الـ pin والنوع ديال الـ capteur، من بعد كنصاوبو الـ objet `dht`:

```C++
#include "DHT.h"

#define DHTPIN  5        // la broche DATA
#define DHTTYPE DHT11    // DHT11, DHT21 ou DHT22

DHT dht(DHTPIN, DHTTYPE);
```

## **الفونكسيون setup()**

___

كنبداو الكومونيكاسيون série والـ capteur:

```C++
void setup() {
  Serial.begin(9600);
  dht.begin();
}
```

## **الفونكسيون loop()**

___

كنقراو الحرارة (ب °C) والرطوبة (ب %):

```C++
float t = dht.readTemperature();
float h = dht.readHumidity();
```

إلى القراية فشلات، القيمة كتكون `NaN` (ماشي رقم). كنتأكدو منها ب `isnan()` وكنبينو ميساج ديال الخطأ:

```C++
if (isnan(t) || isnan(h)) {
  Serial.println("Erreur de lecture du DHT11 !");
  delay(2000);
  return;
}
```

وإلا كنبينو القياسات وكنتسناو 2 ثواني: DHT11 محتاج هاد الوقت بين جوج قياسات.

## **الكود كامل**

___

الكومنتيرات والميساجات ف الكود بالفرنسية، بحال الفيشي `.ino` اللي كتيليشارجي.

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

## **باش تمشي كثر**

___

- بين الحرارة ف écran LCD بلاصة الـ moniteur série.
- دوز ل DHT22، اللي دقيق كثر: غير بدل `DHT11` ب `DHT22`.
- قارن مع الـ capteur LM35 ديال المشروع [ترمومتر رقمي ب ألارم](https://academy.zakpy.com/projects/arduino/thermometre-lm35-7-segments/).
