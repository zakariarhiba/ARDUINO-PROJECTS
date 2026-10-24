---
title: "Change the colour of two RGB LEDs with a struct"
description: "We switch two RGB LEDs from red to green to blue, and organise the code with a struct and functions."
board: "Arduino Uno or Mega"
notions: ["RGB LED", "struct", "functions with parameters"]
components: ["Arduino Uno or Mega", "2 common cathode RGB LEDs", "6 220 Ω resistors", "breadboard and wires"]
---

# **Change the colour of two RGB LEDs with a struct**

```
Arduino project no. 2: RGB LEDs and struct
Written by RHIBA Zakaria, Zakpy Academy
```

*In this project we change the colour of two RGB LEDs at the same time: red, then green, then blue. To keep the code clean even with several LEDs, we use a struct.*

An RGB LED is really three LEDs in one package: a red one, a green one and a blue one. To get red, we turn on the red pin and turn off the green and blue pins.

## **What you will learn**

___

- How an RGB LED works.
- Group several variables in a `struct`.
- Write functions that take a parameter, so we do not repeat the same code.

## **What you need**

___

- An Arduino Uno or Mega board
- 2 common cathode RGB LEDs
- 6 220 Ω resistors (one per colour)
- A breadboard and wires

## **Wiring**

___

| LED | Red | Green | Blue | Common |
|---|---|---|---|---|
| LED 1 | pin 9 | pin 10 | pin 11 | GND |
| LED 2 | pin 5 | pin 6 | pin 7 | GND |

> Each colour goes through its own 220 Ω resistor. The longest leg of the LED is the common pin.

## **The struct**

___

A `struct` lets us create our own type of variable that groups several values. An RGB LED always has 3 pins, so it is the right tool:

```C++
struct RGB {
  int red;
  int green;
  int blue;
};
```

Then we create our two LEDs by giving the pin of each colour:

```C++
RGB led1 = {9, 10, 11};
RGB led2 = {5, 6, 7};
```

## **The functions**

___

We write one function per colour. It receives the LED as a parameter, so the same function works for both LEDs:

```C++
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}
```

We do the same for the `setup`: one function sets the 3 pins of an LED as outputs.

```C++
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}
```

> If we add a third LED tomorrow, we only add one line `RGB led3 = {...};`. The functions do not change.

## **The setup() and loop() functions**

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

## **The full code**

___

The comments in the code are in French, like the `.ino` file you download.

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

## **Going further**

___

- Mix the colours: red + green gives yellow, red + blue gives purple.
- Use `analogWrite()` instead of `digitalWrite()` to get shades of colour. Careful, you need PWM pins (on the Uno, pin 7 is not PWM).
- If your LED is common anode, the common pin goes to 5 V and you must swap HIGH and LOW.
