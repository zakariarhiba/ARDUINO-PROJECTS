---
title: "نشعلو ونطفيو LED"
description: "أول مشروع ف Arduino: كنخليو LED تشعل وتطفى ب pinMode و digitalWrite و delay."
board: "Arduino Uno ولا Mega"
notions: ["pinMode", "digitalWrite", "delay", "#define"]
components: ["Arduino Uno ولا Mega", "LED وحدة", "résistance ديال 220 Ω", "breadboard وفيلات"]
---

# **نشعلو ونطفيو LED**

```
مشروع Arduino رقم 1: نشعلو ونطفيو LED
كتبو RHIBA Zakaria، Zakpy Academy
```

*هادا هو أول مشروع كيديرو كاع اللي كيبداو ب Arduino. كنوصلو LED ب pin رقمي، هنا pin 8، وكنخليوها تشعل وتطفى: شاعلة ثانية، طافية ثانية.*

## **شنو غادي نتعلمو**

___

- نعطيو سمية ل pin ب `#define` ولا ب variable.
- نديرو pin ك sortie ب `pinMode()`.
- نشعلو ونطفيو LED ب `digitalWrite()`.
- نتسناو ب `delay()`.

## **الماتيريال**

___

- كارطة Arduino Uno ولا Mega
- LED وحدة
- résistance ديال 220 Ω
- breadboard وفيلات

## **التوصيل**

___

| من | ل |
|---|---|
| Pin 8 | résistance ديال 220 Ω |
| Résistance | الرجل الطويلة ديال LED (anode، +) |
| الرجل القصيرة ديال LED (cathode، −) | GND |

> الـ résistance كتحمي LED وكتحمي الـ pin ديال Arduino. بلا بيها، الكورون كيكون قوي بزاف.

## **نعطيو سمية للـ pin**

___

كاينين جوج طرق باش نعطيو سمية للـ pin ديال LED. ديما ختار سمية كتقول شنو هو (led، moteur، capteur…):

- ب variable:

```C++
int led = 8;
```

- ب `#define`. هادي هي الطريقة اللي خدمنا بيها ف المشروع: الكومبيلاتور كيبدل `LED` ب `8` قبل ما يكومبيلي، يعني ماكتاخدش بلاصة ف الميموار.

```C++
#define LED 8
```

## **الفونكسيون setup()**

___

كنقولو ل Arduino بلي الـ pin ديال LED هي sortie، حيت Arduino هو اللي كيصيفط السينيال. إلى كان Arduino خاصو يقرا سينيال (بحال bouton)، كنديرو `INPUT`.

```C++
void setup() {
  pinMode(LED, OUTPUT);
}
```

## **الفونكسيون loop()**

___

باش LED تشعل وتطفى، كنشعلوها، كنتسناو، كنطفيوها وكنتسناو عاوتاني. وحيت `loop()` كتعاود بلا حبس، LED كتبقى تشعل وتطفى ديما:

```C++
void loop() {
  digitalWrite(LED, HIGH);   // on allume
  delay(1000);               // 1 seconde
  digitalWrite(LED, LOW);    // on éteint
  delay(1000);
}
```

## **الكود كامل**

___

الكومنتيرات ف الكود بالفرنسية، بحال الفيشي `.ino` اللي كتيليشارجي.

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

## **باش تمشي كثر**

___

- بدل `1000` باش LED تشعل وتطفى بالزربة ولا بشوية.
- زيد LED ثانية ف pin آخر وخليهم يشعلو واحد من بعد الآخر.
- خلي LED تشعل وتطفى ب `millis()` بلاصة `delay()`، باش البرنامج يقدر يدير حاجة أخرى ف نفس الوقت.
