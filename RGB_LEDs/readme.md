---
title: "Changer la couleur de deux LED RGB avec une struct"
slug: "led-rgb-struct"
order: 2
level: "Débutant"
duration: "20 min"
board: "Arduino Uno ou Mega"
description: "On fait passer deux LED RGB du rouge au vert puis au bleu, et on organise le code avec une struct et des fonctions."
notions: ["LED RGB", "struct", "fonctions avec paramètres"]
components: ["Arduino Uno ou Mega", "2 LED RGB à cathode commune", "6 résistances 220 Ω", "breadboard et fils"]
tags: ["led", "rgb", "struct", "débutant"]
youtube: ""
code: "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/RGB_LEDs/RGB_LEDs.ino"
resources: []
github: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/RGB_LEDs"
author: "RHIBA Zakaria"
updated: "2026-10-24"
---

# **Changer la couleur de deux LED RGB avec une struct**

```
Projet Arduino n°2 : LED RGB et struct
Écrit par RHIBA Zakaria, Zakpy Academy
```

*Dans ce projet on fait changer la couleur de deux LED RGB en même temps : rouge, puis vert, puis bleu. Pour que le code reste propre même avec plusieurs LED, on utilise une struct.*

Une LED RGB, c'est en fait trois LED dans un seul boîtier : une rouge, une verte et une bleue. Pour avoir du rouge, on allume la broche rouge et on éteint les broches verte et bleue.

## **Ce qu'on va apprendre**

___

- Comment marche une LED RGB.
- Regrouper plusieurs variables dans une `struct`.
- Écrire des fonctions qui prennent un paramètre, pour ne pas répéter le même code.

## **Le matériel**

___

- Une carte Arduino Uno ou Mega
- 2 LED RGB à cathode commune
- 6 résistances de 220 Ω (une par couleur)
- Une breadboard et des fils

## **Le câblage**

___

| LED | Rouge | Vert | Bleu | Commun |
|---|---|---|---|---|
| LED 1 | broche 9 | broche 10 | broche 11 | GND |
| LED 2 | broche 5 | broche 6 | broche 7 | GND |

> Chaque couleur passe par sa propre résistance de 220 Ω. La patte la plus longue de la LED est la broche commune.

## **La struct**

___

Une `struct` permet de créer notre propre type de variable, qui regroupe plusieurs valeurs. Une LED RGB a toujours 3 broches, donc c'est le bon outil :

```C++
struct RGB {
  int red;
  int green;
  int blue;
};
```

Ensuite on crée nos deux LED en donnant les broches de chaque couleur :

```C++
RGB led1 = {9, 10, 11};
RGB led2 = {5, 6, 7};
```

## **Les fonctions**

___

On écrit une fonction pour chaque couleur. Elle reçoit la LED en paramètre, donc la même fonction marche pour les deux LED :

```C++
void red(RGB led) {
  digitalWrite(led.red, HIGH);
  digitalWrite(led.green, LOW);
  digitalWrite(led.blue, LOW);
}
```

On fait pareil pour le `setup` : une seule fonction met les 3 broches d'une LED en sortie.

```C++
void SetupLed(RGB led) {
  pinMode(led.red, OUTPUT);
  pinMode(led.green, OUTPUT);
  pinMode(led.blue, OUTPUT);
}
```

> Si demain on ajoute une troisième LED, on ajoute juste une ligne `RGB led3 = {...};`. Les fonctions ne changent pas.

## **Les fonctions setup() et loop()**

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

## **Le code complet**

___

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

## **Pour aller plus loin**

___

- Mélange les couleurs : rouge + vert donne du jaune, rouge + bleu donne du violet.
- Utilise `analogWrite()` à la place de `digitalWrite()` pour avoir des nuances de couleur. Attention, il faut des broches PWM (sur la Uno, la broche 7 n'est pas PWM).
- Si ta LED est à anode commune, la broche commune va au 5 V et il faut inverser HIGH et LOW.

___

Tous les cours et les vidéos sont sur **[Zakpy Academy](https://academy.zakpy.com)**.

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zakariarhiba.tech)
