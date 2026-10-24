---
title: "Control a 220 V lamp with a relay module"
description: "We turn on a 220 V lamp with a button, thanks to a 2-relay module driven by the Arduino."
board: "Arduino Uno or Mega"
notions: ["relay module", "input with pull-up", "digitalRead"]
components: ["Arduino Uno or Mega", "5 V 2-relay module", "1 push button", "1 220 V lamp with socket and cable", "wires"]
resources:
  - label: "How a relay module works (Last Minute Engineers)"
    url: "https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/"
---

# **Control a 220 V lamp with a relay module**

```
Arduino project no. 3: 2-relay module
Written by RHIBA Zakaria, Zakpy Academy
```

*Sometimes we want the Arduino to control devices that run on mains power, like a lamp or a fan. But the Arduino works at 5 V, it cannot drive 220 V directly. That is where a relay module comes in: the Arduino controls the relay, and the relay controls the 220 V.*

In this project, we turn on a 220 V lamp when we press a button.

> ⚠ **Careful, 220 V is dangerous.** Do all the wiring with the power off, and never touch the relay terminals while the lamp is plugged in. If you are a beginner, start with an LED and a battery instead of the lamp.

## **What you will learn**

___

- How a relay module works.
- Read a button with `digitalRead()` and the internal pull-up resistor.
- Drive an output from the state of an input.

## **What you need**

___

- An Arduino Uno or Mega board
- A 5 V 2-relay module
- A push button
- A 220 V lamp with its socket and cable
- Wires

## **Wiring**

___

| Relay module / button | Arduino |
|---|---|
| Module VCC | 5 V |
| Module GND | GND |
| Module IN1 | pin 8 |
| Button | between pin 9 and GND |

220 V side: cut only one wire of the lamp (the live wire) and connect both ends to the **COM** and **NO** (normally open) terminals of relay 1.

To understand how the relay works, you can read this guide: [Last Minute Engineers](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/).

## **The pins**

___

```C++
#define RELAY_IN1 8   // l'entrée IN1 du module relais
#define BUTTON1   9   // le bouton
```

## **The setup() function**

___

The relay pin is an output. The button is an input, and we turn on the internal pull-up resistor with `INPUT_PULLUP`: the pin is HIGH when the button is released, and LOW when it is pressed.

```C++
void setup() {
  pinMode(RELAY_IN1, OUTPUT);
  digitalWrite(RELAY_IN1, HIGH);    // relais au repos au démarrage
  pinMode(BUTTON1, INPUT_PULLUP);
}
```

## **The loop() function**

___

We read the button and drive the relay. On most 2-relay modules, the relay switches on when its input is **LOW**:

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

## **The full code**

___

The comments in the code are in French, like the `.ino` file you download.

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

## **Going further**

___

- Use the second relay to control a second device with a second button.
- Make a toggle button: one press turns on, the next press turns off.
- Control the relay from your phone (Bluetooth or Wi-Fi). This is the base of the King House smart home project.
