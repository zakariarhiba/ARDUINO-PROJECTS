---
title: "نبدلو اللون ديال جوج LED RGB ب struct"
description: "كنخليو جوج LED RGB يدوزو من الحمر للخضر من بعد للزرق، وكننظمو الكود ب struct و فونكسيونات."
board: "Arduino Uno ولا Mega"
notions: ["LED RGB", "struct", "فونكسيونات ب paramètres"]
components: ["Arduino Uno ولا Mega", "جوج LED RGB ب cathode commune", "6 résistances ديال 220 Ω", "breadboard وفيلات"]
---

# **نبدلو اللون ديال جوج LED RGB ب struct**

```
مشروع Arduino رقم 2: LED RGB و struct
كتبو RHIBA Zakaria، Zakpy Academy
```

*ف هاد المشروع كنبدلو اللون ديال جوج LED RGB ف نفس الوقت: الحمر، من بعد الخضر، من بعد الزرق. باش الكود يبقى نقي حتى ملي يكونو بزاف ديال LED، كنخدمو ب struct.*

LED RGB هي ف الحقيقة ثلاثة ديال LED ف بواطة وحدة: وحدة حمرا، وحدة خضرا ووحدة زرقا. باش نجيبو الحمر، كنشعلو الـ pin الحمر وكنطفيو الـ pin الخضر والزرق.

## **شنو غادي نتعلمو**

___

- كيفاش خدامة LED RGB.
- نجمعو بزاف ديال variables ف `struct`.
- نكتبو فونكسيونات كتاخد paramètre، باش مانعاودوش نفس الكود.

## **الماتيريال**

___

- كارطة Arduino Uno ولا Mega
- جوج LED RGB ب cathode commune
- 6 résistances ديال 220 Ω (وحدة لكل لون)
- breadboard وفيلات

## **التوصيل**

___

| LED | الحمر | الخضر | الزرق | Commun |
|---|---|---|---|---|
| LED 1 | pin 9 | pin 10 | pin 11 | GND |
| LED 2 | pin 5 | pin 6 | pin 7 | GND |

> كل لون كيدوز من résistance ديالو ديال 220 Ω. الرجل الطويلة ديال LED هي الـ pin المشترك.

## **الـ struct**

___

`struct` كتخلينا نصاوبو نوع ديال variable ديالنا، كيجمع بزاف ديال القيم. LED RGB ديما عندها 3 pins، إذن هي الأداة المناسبة:

```C++
struct RGB {
  int red;
  int green;
  int blue;
};
```

من بعد كنصاوبو جوج LED ديالنا وكنعطيو الـ pin ديال كل لون:

```C++
RGB led1 = {9, 10, 11};
RGB led2 = {5, 6, 7};
```

## **الفونكسيونات**

___

كنكتبو فونكسيون لكل لون. كتاخد LED ك paramètre، يعني نفس الفونكسيون كتخدم مع جوج LED:

```C++
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}
```

كنديرو نفس الحاجة ل `setup`: فونكسيون وحدة كتدير 3 pins ديال LED ك sortie.

```C++
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}
```

> إلى زدنا غدا LED ثالثة، كنزيدو غير سطر واحد `RGB led3 = {...};`. الفونكسيونات ماكتبدلش.

## **الفونكسيونات setup() و loop()**

___

```C++
void setup() {
  SetupLed(led1);
  SetupLed(led2);
}

void loop() {
  red(led1);    red(led2);    delay(1000);
  green(led1);  green(led2);  delay(1000);
  blue(led1);   blue(led2);   delay(1000);
}
```

## **الكود كامل**

___

الكومنتيرات ف الكود بالفرنسية، بحال الفيشي `.ino` اللي كتيليشارجي.

```C++
/*
 * Projet : changer la couleur de deux LED RGB avec une struct
 * Zakpy Academy - RHIBA Zakaria
 * Carte : Arduino Uno ou Mega
 *
 * LED RGB à cathode commune : la broche commune va au GND,
 * et chaque couleur passe par une résistance de 220 ohms.
 */

// Une LED RGB, c'est 3 broches : rouge, vert et bleu
struct RGB {
  int red;
  int green;
  int blue;
};

RGB led1 = {9, 10, 11};   // broches de la première LED
RGB led2 = {5, 6, 7};     // broches de la deuxième LED

// Met les 3 broches d'une LED en sortie
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}

// Allume la couleur rouge seulement
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}

// Allume la couleur verte seulement
void green(RGB led) {
  digitalWrite(led.red, LOW);
  digitalWrite(led.green, HIGH);
  digitalWrite(led.blue, LOW);
}

// Allume la couleur bleue seulement
void blue(RGB led) {
  digitalWrite(led.red, LOW);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, HIGH);
}

void setup() {
  SetupLed(led1);
  SetupLed(led2);
}

void loop() {
  red(led1);    red(led2);    delay(1000);   // rouge pendant 1 s
  green(led1);  green(led2);  delay(1000);   // vert pendant 1 s
  blue(led1);   blue(led2);   delay(1000);   // bleu pendant 1 s
}
```

## **باش تمشي كثر**

___

- خلط الألوان: الحمر + الخضر كيعطي الصفر، الحمر + الزرق كيعطي الموف.
- خدم ب `analogWrite()` بلاصة `digitalWrite()` باش تجيب درجات ديال الألوان. رد البال، خاصك pins PWM (ف Uno، الـ pin 7 ماشي PWM).
- إلى كانت LED ديالك ب anode commune، الـ pin المشترك كيمشي ل 5 V وخاصك تبدل HIGH ب LOW.
