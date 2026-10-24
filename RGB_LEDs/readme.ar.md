---
title: "تغيير لون مصباحين RGB باستخدام struct"
description: "نجعل مصباحين RGB ينتقلان من الأحمر إلى الأخضر ثم إلى الأزرق، وننظم الشيفرة باستخدام struct ودوال."
board: "Arduino Uno أو Mega"
notions: ["مصباح RGB", "struct", "دوال بمعاملات"]
components: ["لوحة Arduino Uno أو Mega", "مصباحا RGB بمهبط مشترك", "6 مقاومات 220 أوم", "لوحة تجارب وأسلاك توصيل"]
---

# **تغيير لون مصباحين RGB باستخدام struct**

```
مشروع Arduino رقم 2: مصابيح RGB و struct
إعداد: RHIBA Zakaria، Zakpy Academy
```

*في هذا المشروع نغير لون مصباحين RGB في الوقت نفسه: الأحمر، ثم الأخضر، ثم الأزرق. ولكي تبقى الشيفرة منظمة حتى مع عدة مصابيح، نستخدم struct.*

مصباح RGB هو في الحقيقة ثلاثة مصابيح في غلاف واحد: أحمر وأخضر وأزرق. للحصول على اللون الأحمر نشغل منفذ اللون الأحمر ونطفئ منفذي الأخضر والأزرق.

## **ما الذي سنتعلمه**

___

- طريقة عمل مصباح RGB.
- تجميع عدة متغيرات داخل `struct`.
- كتابة دوال تستقبل معاملًا، حتى لا نكرر الشيفرة نفسها.

## **المكونات**

___

- لوحة Arduino Uno أو Mega
- مصباحا RGB بمهبط مشترك
- 6 مقاومات 220 أوم (واحدة لكل لون)
- لوحة تجارب وأسلاك توصيل

## **التوصيل**

___

| المصباح | الأحمر | الأخضر | الأزرق | المشترك |
|---|---|---|---|---|
| المصباح 1 | المنفذ 9 | المنفذ 10 | المنفذ 11 | GND |
| المصباح 2 | المنفذ 5 | المنفذ 6 | المنفذ 7 | GND |

> كل لون يمر عبر مقاومة خاصة به قيمتها 220 أوم. الساق الأطول في المصباح هي المنفذ المشترك.

## **البنية struct**

___

تسمح `struct` بإنشاء نوع متغير خاص بنا يجمع عدة قيم. ولأن لمصباح RGB ثلاثة منافذ دائمًا، فهي الأداة المناسبة:

```C++
struct RGB {
  int red;
  int green;
  int blue;
};
```

بعد ذلك ننشئ المصباحين ونحدد منفذ كل لون:

```C++
RGB led1 = {9, 10, 11};
RGB led2 = {5, 6, 7};
```

## **الدوال**

___

نكتب دالة لكل لون. تستقبل الدالة المصباح كمعامل، فتعمل الدالة نفسها مع المصباحين:

```C++
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}
```

ونفعل الشيء نفسه مع `setup`: دالة واحدة تجعل المنافذ الثلاثة لمصباح ما مخارج.

```C++
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}
```

> إذا أضفنا مصباحًا ثالثًا لاحقًا، يكفي أن نضيف سطرًا واحدًا `RGB led3 = {...};`، ولا تتغير الدوال.

## **الدالتان setup() و loop()**

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

## **الشيفرة الكاملة**

___

التعليقات داخل الشيفرة باللغة الفرنسية، كما في ملف `.ino` الذي يمكنك تحميله.

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

## **للتعمق أكثر**

___

- امزج الألوان: الأحمر مع الأخضر يعطي الأصفر، والأحمر مع الأزرق يعطي البنفسجي.
- استخدم `analogWrite()` بدل `digitalWrite()` للحصول على درجات من الألوان. انتبه، تحتاج إلى منافذ PWM (في لوحة Uno المنفذ 7 ليس من نوع PWM).
- إذا كان مصباحك بمصعد مشترك، يوصل المنفذ المشترك بـ 5 فولت ويجب عكس HIGH و LOW.
