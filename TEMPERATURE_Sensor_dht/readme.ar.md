---
title: "قياس درجة الحرارة والرطوبة بالحساس DHT11"
description: "نقرأ درجة الحرارة والرطوبة بالحساس DHT11 ونعرضهما على شاشة المراقبة التسلسلية كل ثانيتين."
board: "Arduino Uno أو Mega"
notions: ["مكتبات Arduino", "حساس رقمي", "شاشة المراقبة التسلسلية"]
components: ["لوحة Arduino Uno أو Mega", "حساس DHT11 (أو وحدة DHT11)", "مقاومة 10 كيلو أوم إذا كان الحساس بدون لوحة", "لوحة تجارب وأسلاك توصيل"]
resources:
  - label: "مكتبة DHT sensor library (Adafruit)"
    url: "https://github.com/adafruit/DHT-sensor-library"
  - label: "مكتبة Adafruit Unified Sensor"
    url: "https://github.com/adafruit/Adafruit_Sensor"
---

# **قياس درجة الحرارة والرطوبة بالحساس DHT11**

```
مشروع Arduino رقم 4: الحساس DHT11
إعداد: RHIBA Zakaria، Zakpy Academy
```

*في هذا المشروع نستخدم الحساس DHT11 لقياس درجة الحرارة والرطوبة. تظهر القيم على شاشة المراقبة التسلسلية كل ثانيتين، لذلك يجب فتح هذه الشاشة في برنامج Arduino IDE بعد رفع البرنامج إلى اللوحة.*

## **ما الذي سنتعلمه**

___

- تثبيت مكتبة Arduino واستخدامها.
- قراءة حساس رقمي.
- التحقق من نجاح القياس باستخدام `isnan()`.

## **المكونات**

___

- لوحة Arduino Uno أو Mega
- حساس DHT11 (أو وحدة DHT11 مركبة على لوحة صغيرة)
- مقاومة 10 كيلو أوم إذا كان الحساس بدون لوحة (الوحدة تحتوي عليها)
- لوحة تجارب وأسلاك توصيل

## **المكتبات**

___

في برنامج Arduino IDE، افتح مدير المكتبات وثبّت:

- مكتبة **DHT sensor library** من Adafruit: [github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
- مكتبة **Adafruit Unified Sensor**: [github.com/adafruit/Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)

## **التوصيل**

___

للحساس DHT11 ثلاثة أطراف مستعملة: VCC و GND، والطرف DATA الذي يرسل القياسات. نوصل الطرف DATA بالمنفذ 5.

| الحساس DHT11 | لوحة Arduino |
|---|---|
| VCC | 5 فولت |
| DATA | المنفذ 5 (مع مقاومة 10 كيلو أوم نحو 5 فولت إذا كان الحساس بدون لوحة) |
| GND | GND |

## **تهيئة الحساس**

___

نضيف المكتبة، ونحدد المنفذ ونوع الحساس، ثم ننشئ الكائن `dht`:

```C++
#include "DHT.h"

#define DHTPIN  5        // la broche DATA
#define DHTTYPE DHT11    // DHT11, DHT21 ou DHT22

DHT dht(DHTPIN, DHTTYPE);
```

## **الدالة setup()**

___

نبدأ الاتصال التسلسلي ونشغل الحساس:

```C++
void setup() {
  Serial.begin(9600);
  dht.begin();
}
```

## **الدالة loop()**

___

نقرأ درجة الحرارة (بالدرجة المئوية) والرطوبة (بالنسبة المئوية):

```C++
float t = dht.readTemperature();
float h = dht.readHumidity();
```

إذا فشلت القراءة تكون القيمة `NaN` (ليست عددًا). نتحقق من ذلك باستخدام `isnan()` ونعرض رسالة خطأ:

```C++
if (isnan(t) || isnan(h)) {
  Serial.println("Erreur de lecture du DHT11 !");
  delay(2000);
  return;
}
```

وإلا نعرض القياسات وننتظر ثانيتين، لأن الحساس DHT11 يحتاج إلى هذه المدة بين قياسين.

## **الشيفرة الكاملة**

___

التعليقات والرسائل داخل الشيفرة باللغة الفرنسية، كما في ملف `.ino` الذي يمكنك تحميله.

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

## **للتعمق أكثر**

___

- اعرض درجة الحرارة على شاشة LCD بدل شاشة المراقبة التسلسلية.
- انتقل إلى الحساس DHT22 الأكثر دقة: يكفي تغيير `DHT11` إلى `DHT22`.
- قارن النتائج مع الحساس LM35 في مشروع [ميزان الحرارة الرقمي مع منبه قابل للضبط](https://academy.zakpy.com/projects/arduino/thermometre-lm35-7-segments/).
