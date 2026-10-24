---
title: "Make an LED blink"
description: "The first Arduino project: we make an LED blink with pinMode, digitalWrite and delay."
board: "Arduino Uno or Mega"
notions: ["pinMode", "digitalWrite", "delay", "#define"]
components: ["Arduino Uno or Mega", "1 LED", "1 220 Ω resistor", "breadboard and wires"]
---

# **Make an LED blink**

```
Arduino project no. 1: make an LED blink
Written by RHIBA Zakaria, Zakpy Academy
```

*This is the first project everyone builds when starting with Arduino. We connect an LED to a digital pin, here pin 8, and make it blink: on for one second, off for one second.*

## **What you will learn**

___

- Name a pin with `#define` or with a variable.
- Set a pin as an output with `pinMode()`.
- Turn an LED on and off with `digitalWrite()`.
- Wait with `delay()`.

## **What you need**

___

- An Arduino Uno or Mega board
- An LED
- A 220 Ω resistor
- A breadboard and wires

## **Wiring**

___

| From | To |
|---|---|
| Pin 8 | 220 Ω resistor |
| Resistor | long leg of the LED (anode, +) |
| Short leg of the LED (cathode, −) | GND |

> The resistor protects the LED and the Arduino pin. Without it, the current is too high.

## **Naming the pin**

___

There are two ways to give the LED pin a name. Always pick a name that says what it is (led, motor, sensor…):

- With a variable:

```C++
int led = 8;
```

- With a `#define`. This is what the project uses: the compiler replaces `LED` with `8` before compiling, so it takes no memory.

```C++
#define LED 8
```

## **The setup() function**

___

We tell the Arduino that the LED pin is an output, because the Arduino sends the signal. If the Arduino had to read a signal (a button for example), we would use `INPUT`.

```C++
void setup() {
  pinMode(LED, OUTPUT);
}
```

## **The loop() function**

___

To make the LED blink, we turn it on, wait, turn it off and wait again. Since `loop()` repeats forever, the LED keeps blinking:

```C++
void loop() {
  digitalWrite(LED, HIGH);   // on allume
  delay(1000);               // 1 seconde
  digitalWrite(LED, LOW);    // on éteint
  delay(1000);
}
```

## **The full code**

___

The comments in the code are in French, like the `.ino` file you download.

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

## **Going further**

___

- Change the `1000` to blink faster or slower.
- Add a second LED on another pin and make them blink one after the other.
- Make the LED blink with `millis()` instead of `delay()`, so the program can do something else at the same time.
