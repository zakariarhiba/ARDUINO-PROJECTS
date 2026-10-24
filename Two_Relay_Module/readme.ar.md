---
title: "التحكم في مصباح 220 فولت بواسطة وحدة مرحّل"
description: "نشغل مصباحًا يعمل بجهد 220 فولت بالضغط على زر، بفضل وحدة مرحّلين تتحكم فيها لوحة Arduino."
board: "Arduino Uno أو Mega"
notions: ["وحدة المرحّل", "مدخل بمقاومة رفع داخلية", "digitalRead"]
components: ["لوحة Arduino Uno أو Mega", "وحدة مرحّلين 5 فولت", "زر ضاغط واحد", "مصباح 220 فولت مع القاعدة والسلك", "أسلاك توصيل"]
resources:
  - label: "طريقة عمل وحدة المرحّل (Last Minute Engineers، بالإنجليزية)"
    url: "https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/"
---

# **التحكم في مصباح 220 فولت بواسطة وحدة مرحّل**

```
مشروع Arduino رقم 3: وحدة مرحّلين
إعداد: RHIBA Zakaria، Zakpy Academy
```

*نريد أحيانًا أن تتحكم لوحة Arduino في أجهزة تعمل بكهرباء الشبكة، مثل مصباح أو مروحة. لكن اللوحة تعمل بجهد 5 فولت، ولا يمكنها التحكم مباشرة في جهد 220 فولت. هنا نستخدم وحدة المرحّل: اللوحة تتحكم في المرحّل، والمرحّل يتحكم في دائرة 220 فولت.*

في هذا المشروع نشغل مصباحًا يعمل بجهد 220 فولت عندما نضغط على زر.

> ⚠ **انتبه، جهد 220 فولت خطير.** أنجز كل التوصيلات والكهرباء مفصولة، ولا تلمس أطراف المرحّل أبدًا والمصباح موصول بالشبكة. إذا كنت مبتدئًا، ابدأ بمصباح LED وبطارية بدل المصباح.

## **ما الذي سنتعلمه**

___

- طريقة عمل وحدة المرحّل.
- قراءة زر باستخدام `digitalRead()` ومقاومة الرفع الداخلية.
- التحكم في مخرج حسب حالة مدخل.

## **المكونات**

___

- لوحة Arduino Uno أو Mega
- وحدة مرحّلين بجهد 5 فولت
- زر ضاغط واحد
- مصباح 220 فولت مع القاعدة والسلك
- أسلاك توصيل

## **التوصيل**

___

| وحدة المرحّل / الزر | لوحة Arduino |
|---|---|
| طرف VCC في الوحدة | 5 فولت |
| طرف GND في الوحدة | GND |
| طرف IN1 في الوحدة | المنفذ 8 |
| الزر | بين المنفذ 9 و GND |

من جهة 220 فولت: نقطع سلكًا واحدًا فقط من سلكي المصباح (سلك الطور) ونوصل طرفيه بالطرفين **COM** و **NO** (مفتوح في الوضع العادي) في المرحّل الأول.

لفهم طريقة عمل المرحّل بشكل أفضل، يمكنك قراءة هذا الشرح (بالإنجليزية): [Last Minute Engineers](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/).

## **المنافذ**

___

```C++
#define RELAY_IN1 8   // l'entrée IN1 du module relais
#define BUTTON1   9   // le bouton
```

## **الدالة setup()**

___

منفذ المرحّل مخرج. أما الزر فهو مدخل، ونفعّل مقاومة الرفع الداخلية باستخدام `INPUT_PULLUP`: تكون قيمة المنفذ HIGH عندما يكون الزر غير مضغوط، و LOW عند الضغط عليه.

```C++
void setup() {
  pinMode(RELAY_IN1, OUTPUT);
  digitalWrite(RELAY_IN1, HIGH);    // relais au repos au démarrage
  pinMode(BUTTON1, INPUT_PULLUP);
}
```

## **الدالة loop()**

___

نقرأ حالة الزر ونتحكم في المرحّل. في معظم وحدات المرحّلين، يعمل المرحّل عندما تكون قيمة مدخله **LOW**:

```C++
void loop() {
  int button1Value = digitalRead(BUTTON1);

  if (button1Value == LOW) {
    digitalWrite(RELAY_IN1, LOW);    // bouton appuyé : lampe allumée
  } else {
    digitalWrite(RELAY_IN1, HIGH);   // bouton relâché : lampe éteinte
  }
}
```

## **الشيفرة الكاملة**

___

التعليقات داخل الشيفرة باللغة الفرنسية، كما في ملف `.ino` الذي يمكنك تحميله.

```C++
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
```

## **للتعمق أكثر**

___

- استخدم المرحّل الثاني للتحكم في جهاز ثانٍ بزر ثانٍ.
- اصنع زرًا يعمل كمفتاح: ضغطة تشغل المصباح، والضغطة التالية تطفئه.
- تحكم في المرحّل من الهاتف (Bluetooth أو Wi-Fi). هذا هو أساس مشروع المنزل الذكي King House.
