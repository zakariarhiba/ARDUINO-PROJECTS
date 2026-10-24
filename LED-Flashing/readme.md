---
title: "Faire clignoter une LED"
slug: "led-clignotante"
order: 1
level: "Débutant"
duration: "15 min"
board: "Arduino Uno ou Mega"
description: "Le premier projet Arduino : on fait clignoter une LED avec pinMode, digitalWrite et delay."
notions: ["pinMode", "digitalWrite", "delay", "#define"]
components: ["Arduino Uno ou Mega", "1 LED", "1 résistance 220 Ω", "breadboard et fils"]
tags: ["led", "débutant", "sorties numériques"]
youtube: ""
code: "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/LED-Flashing/LED-Flashing.ino"
resources: []
github: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/LED-Flashing"
author: "RHIBA Zakaria"
updated: "2026-10-24"
---

# **Faire clignoter une LED**

```
Projet Arduino n°1 : faire clignoter une LED
Écrit par RHIBA Zakaria, Zakpy Academy
```

*C'est le premier projet qu'on fait quand on commence avec Arduino. On branche une LED sur une broche numérique, ici la broche 8, et on la fait clignoter : allumée une seconde, éteinte une seconde.*

## **Ce qu'on va apprendre**

___

- Déclarer une broche avec `#define` ou avec une variable.
- Mettre une broche en sortie avec `pinMode()`.
- Allumer et éteindre une LED avec `digitalWrite()`.
- Attendre avec `delay()`.

## **Le matériel**

___

- Une carte Arduino Uno ou Mega
- Une LED
- Une résistance de 220 Ω
- Une breadboard et des fils

## **Le câblage**

___

| De | Vers |
|---|---|
| Broche 8 | résistance de 220 Ω |
| Résistance | patte longue de la LED (anode, +) |
| Patte courte de la LED (cathode, −) | GND |

> La résistance protège la LED et la broche de l'Arduino. Sans elle, le courant est trop fort.

## **Déclarer la broche**

___

Il y a deux façons de donner un nom à la broche de la LED. On choisit toujours un nom qui dit ce que c'est (led, moteur, capteur…) :

- Avec une variable :

```C++
int led = 8;
```

- Avec un `#define`. C'est la façon qu'on utilise dans le projet : le compilateur remplace `LED` par `8` avant de compiler, donc ça ne prend pas de place en mémoire.

```C++
#define LED 8
```

## **La fonction setup()**

___

On dit à l'Arduino que la broche de la LED est une sortie, parce que c'est l'Arduino qui envoie le signal. Si l'Arduino devait lire un signal (un bouton par exemple), on mettrait `INPUT`.

```C++
void setup() {
  pinMode(LED, OUTPUT);
}
```

## **La fonction loop()**

___

Pour faire clignoter la LED, on l'allume, on attend, on l'éteint et on attend encore. Comme `loop()` se répète à l'infini, la LED clignote sans arrêt :

```C++
void loop() {
  digitalWrite(LED, HIGH);   // on allume
  delay(1000);               // 1 seconde
  digitalWrite(LED, LOW);    // on éteint
  delay(1000);
}
```

## **Le code complet**

___

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

## **Pour aller plus loin**

___

- Change le `1000` pour faire clignoter plus vite ou plus lentement.
- Ajoute une deuxième LED sur une autre broche et fais-les clignoter chacune leur tour.
- Fais clignoter la LED avec `millis()` à la place de `delay()`, pour que le programme puisse faire autre chose en même temps.

___

Tous les cours et les vidéos sont sur **[Zakpy Academy](https://academy.zakpy.com)**.

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zakariarhiba.tech)
