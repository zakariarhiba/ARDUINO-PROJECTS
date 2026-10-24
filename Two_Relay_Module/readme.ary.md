---
title: "نتحكمو ف لامبة 220 V ب module relais"
description: "كنشعلو لامبة 220 V ب bouton، بفضل module ديال جوج relais كيتحكم فيه Arduino."
board: "Arduino Uno ولا Mega"
notions: ["module relais", "entrée ب pull-up", "digitalRead"]
components: ["Arduino Uno ولا Mega", "module ديال جوج relais 5 V", "bouton poussoir واحد", "لامبة 220 V مع douille وكابل", "فيلات"]
resources:
  - label: "كيفاش خدام module relais (Last Minute Engineers، بالنڭليزية)"
    url: "https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/"
---

# **نتحكمو ف لامبة 220 V ب module relais**

```
مشروع Arduino رقم 3: module ديال جوج relais
كتبو RHIBA Zakaria، Zakpy Academy
```

*مرات كنبغيو Arduino يتحكم ف أجهزة خدامة بالضو ديال الدار، بحال لامبة ولا ventilateur. ولكن Arduino خدام ب 5 V، مايقدرش يتحكم ف 220 V نيشان. هنا كنخدمو ب module relais: Arduino كيتحكم ف الـ relais، والـ relais كيتحكم ف 220 V.*

ف هاد المشروع، كنشعلو لامبة 220 V ملي كنبركو على bouton.

> ⚠ **رد البال، 220 V خطيرة.** دير التوصيل كامل والضو مقطوع، وعمرك ماتقيس البورنات ديال الـ relais واللامبة مبرانشية. إلى كنتي مبتدئ، بدا ب LED و pile بلاصة اللامبة.

## **شنو غادي نتعلمو**

___

- كيفاش خدام module relais.
- نقراو bouton ب `digitalRead()` و résistance de pull-up الداخلية.
- نتحكمو ف sortie على حساب الحالة ديال entrée.

## **الماتيريال**

___

- كارطة Arduino Uno ولا Mega
- module ديال جوج relais 5 V
- bouton poussoir واحد
- لامبة 220 V مع la douille والكابل ديالها
- فيلات

## **التوصيل**

___

| Module relais / bouton | Arduino |
|---|---|
| VCC ديال الـ module | 5 V |
| GND ديال الـ module | GND |
| IN1 ديال الـ module | pin 8 |
| Bouton | بين pin 9 و GND |

من جيهة 220 V: كنقطعو غير فيل واحد ديال اللامبة (la phase) وكنوصلو جوج الطرفات ب البورنات **COM** و **NO** (normalement ouvert) ديال relais 1.

باش تفهم مزيان كيفاش خدام الـ relais، تقدر تقرا هاد الدوكيمونتاسيون (بالنڭليزية): [Last Minute Engineers](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/).

## **الـ pins**

___

```C++
#define RELAY_IN1 8   // l'entrée IN1 du module relais
#define BUTTON1   9   // le bouton
```

## **الفونكسيون setup()**

___

الـ pin ديال الـ relais هي sortie. الـ bouton هو entrée، وكنشعلو résistance de pull-up الداخلية ب `INPUT_PULLUP`: الـ pin كتكون HIGH ملي الـ bouton مطلوق، و LOW ملي كنبركو عليه.

```C++
void setup() {
  pinMode(RELAY_IN1, OUTPUT);
  digitalWrite(RELAY_IN1, HIGH);    // relais au repos au démarrage
  pinMode(BUTTON1, INPUT_PULLUP);
}
```

## **الفونكسيون loop()**

___

كنقراو الـ bouton وكنتحكمو ف الـ relais. ف أغلب الـ modules ديال جوج relais، الـ relais كيخدم ملي الـ entrée ديالو تكون **LOW**:

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

## **الكود كامل**

___

الكومنتيرات ف الكود بالفرنسية، بحال الفيشي `.ino` اللي كتيليشارجي.

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

## **باش تمشي كثر**

___

- خدم بالـ relais الثاني باش تتحكم ف جهاز آخر ب bouton ثاني.
- صاوب bouton « interrupteur »: بركة كتشعل، وبركة أخرى كتطفي.
- تحكم ف الـ relais من التيليفون (Bluetooth ولا Wi-Fi). هادي هي الأساس ديال مشروع الدار المتصلة King House.
