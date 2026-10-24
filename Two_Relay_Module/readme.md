---
title: "Commander une lampe 220 V avec un module relais"
slug: "module-relais"
order: 3
level: "Débutant"
duration: "20 min"
board: "Arduino Uno ou Mega"
description: "On allume une lampe 220 V avec un bouton, grâce à un module 2 relais commandé par l'Arduino."
notions: ["module relais", "entrée avec pull-up", "digitalRead"]
components: ["Arduino Uno ou Mega", "module 2 relais 5 V", "1 bouton poussoir", "1 lampe 220 V avec douille et câble", "fils"]
tags: ["relais", "220V", "bouton", "domotique"]
youtube: ""
code: "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/Two_Relay_Module/Two_Relay_Module.ino"
resources:
  - label: "Comment marche un module relais (Last Minute Engineers)"
    url: "https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/"
github: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Two_Relay_Module"
author: "RHIBA Zakaria"
updated: "2026-10-24"
---

# **Commander une lampe 220 V avec un module relais**

```
Projet Arduino n°3 : module 2 relais
Écrit par RHIBA Zakaria, Zakpy Academy
```

*Parfois on veut que l'Arduino commande des appareils qui marchent sur le secteur, comme une lampe ou un ventilateur. Mais l'Arduino travaille en 5 V, il ne peut pas commander directement du 220 V. C'est là qu'on utilise un module relais : l'Arduino commande le relais, et le relais commande le 220 V.*

Dans ce projet, on allume une lampe 220 V quand on appuie sur un bouton.

> ⚠ **Attention, le 220 V est dangereux.** On fait tout le câblage hors tension, et on ne touche jamais les bornes du relais quand la lampe est branchée. Si tu débutes, commence avec une LED et une pile à la place de la lampe.

## **Ce qu'on va apprendre**

___

- Comment marche un module relais.
- Lire un bouton avec `digitalRead()` et la résistance de pull-up interne.
- Commander une sortie selon l'état d'une entrée.

## **Le matériel**

___

- Une carte Arduino Uno ou Mega
- Un module 2 relais 5 V
- Un bouton poussoir
- Une lampe 220 V avec sa douille et son câble
- Des fils

## **Le câblage**

___

| Module relais / bouton | Arduino |
|---|---|
| VCC du module | 5 V |
| GND du module | GND |
| IN1 du module | broche 8 |
| Bouton | entre la broche 9 et GND |

Côté 220 V : on coupe un seul fil de la lampe (la phase) et on branche les deux bouts sur les bornes **COM** et **NO** (normalement ouvert) du relais 1.

Pour bien comprendre le fonctionnement du relais, tu peux lire cette documentation : [Last Minute Engineers](https://lastminuteengineers.com/two-channel-relay-module-arduino-tutorial/).

## **Les broches**

___

```C++
#define RELAY_IN1 8   // l'entrée IN1 du module relais
#define BUTTON1   9   // le bouton
```

## **La fonction setup()**

___

La broche du relais est une sortie. Le bouton est une entrée, et on active la résistance de pull-up interne avec `INPUT_PULLUP` : la broche est à HIGH quand le bouton est relâché, et à LOW quand on appuie.

```C++
void setup() {
  pinMode(RELAY_IN1, OUTPUT);
  digitalWrite(RELAY_IN1, HIGH);    // relais au repos au démarrage
  pinMode(BUTTON1, INPUT_PULLUP);
}
```

## **La fonction loop()**

___

On lit le bouton et on commande le relais. Sur la plupart des modules 2 relais, le relais s'active quand son entrée est à **LOW** :

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

## **Le code complet**

___

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

## **Pour aller plus loin**

___

- Utilise le deuxième relais pour commander un deuxième appareil avec un deuxième bouton.
- Fais un bouton « interrupteur » : un appui allume, un autre appui éteint.
- Commande le relais depuis le téléphone (Bluetooth ou Wi-Fi). C'est la base du projet de maison connectée King House.

___

Tous les cours et les vidéos sont sur **[Zakpy Academy](https://academy.zakpy.com)**.

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zakariarhiba.tech)
