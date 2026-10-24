---
title: "تشغيل وإطفاء مصباح LED بشكل متكرر"
description: "أول مشروع مع Arduino: نجعل مصباح LED يومض باستخدام الدوال pinMode وdigitalWrite وdelay."
board: "Arduino Uno أو Mega"
notions: ["pinMode", "digitalWrite", "delay", "#define"]
components: ["لوحة Arduino Uno أو Mega", "مصباح LED واحد", "مقاومة 220 أوم", "لوحة تجارب وأسلاك توصيل"]
---

# **تشغيل وإطفاء مصباح LED بشكل متكرر**

```
مشروع Arduino رقم 1: وميض مصباح LED
إعداد: RHIBA Zakaria، Zakpy Academy
```

*هذا هو المشروع الأول الذي ينجزه كل من يبدأ مع Arduino. نوصل مصباح LED بمنفذ رقمي، وهو هنا المنفذ 8، ونجعله يومض: يشتغل لمدة ثانية ثم ينطفئ لمدة ثانية.*

## **ما الذي سنتعلمه**

___

- تسمية منفذ باستخدام `#define` أو باستخدام متغير.
- جعل المنفذ مخرجًا باستخدام `pinMode()`.
- تشغيل المصباح وإطفاؤه باستخدام `digitalWrite()`.
- الانتظار باستخدام `delay()`.

## **المكونات**

___

- لوحة Arduino Uno أو Mega
- مصباح LED واحد
- مقاومة 220 أوم
- لوحة تجارب وأسلاك توصيل

## **التوصيل**

___

| من | إلى |
|---|---|
| المنفذ 8 | المقاومة 220 أوم |
| المقاومة | الساق الطويلة للمصباح (المصعد، +) |
| الساق القصيرة للمصباح (المهبط، −) | GND |

> المقاومة تحمي المصباح وتحمي منفذ لوحة Arduino. بدونها يكون التيار قويًا جدًا.

## **تسمية المنفذ**

___

هناك طريقتان لإعطاء اسم لمنفذ المصباح. نختار دائمًا اسمًا يدل على العنصر (مصباح، محرك، حساس…):

- باستخدام متغير:

```C++
int led = 8;
```

- باستخدام `#define`، وهي الطريقة المعتمدة في المشروع: يستبدل المترجم `LED` بالرقم `8` قبل الترجمة، فلا تأخذ أي مساحة من الذاكرة.

```C++
#define LED 8
```

## **الدالة setup()**

___

نخبر لوحة Arduino أن منفذ المصباح مخرج، لأن اللوحة هي التي ترسل الإشارة. ولو كان على اللوحة أن تقرأ إشارة (من زر مثلًا) لاستعملنا `INPUT`.

```C++
void setup() {
  pinMode(LED, OUTPUT);
}
```

## **الدالة loop()**

___

لكي يومض المصباح نشغله، ثم ننتظر، ثم نطفئه، ثم ننتظر من جديد. وبما أن `loop()` تتكرر دون توقف، يستمر المصباح في الوميض:

```C++
void loop() {
  digitalWrite(LED, HIGH);   // on allume
  delay(1000);               // 1 seconde
  digitalWrite(LED, LOW);    // on éteint
  delay(1000);
}
```

## **الشيفرة الكاملة**

___

التعليقات داخل الشيفرة باللغة الفرنسية، كما في ملف `.ino` الذي يمكنك تحميله.

```C++
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
```

## **للتعمق أكثر**

___

- غيّر القيمة `1000` ليصبح الوميض أسرع أو أبطأ.
- أضف مصباحًا ثانيًا على منفذ آخر واجعلهما يومضان بالتناوب.
- اجعل المصباح يومض باستخدام `millis()` بدل `delay()`، حتى يتمكن البرنامج من تنفيذ مهام أخرى في الوقت نفسه.
