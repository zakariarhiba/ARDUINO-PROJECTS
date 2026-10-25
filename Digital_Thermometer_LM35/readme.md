---
title: "Thermomètre numérique avec alarme réglable"
slug: "thermometre-lm35-7-segments"
order: 5
level: "Intermédiaire"
duration: "3 h"
board: "Arduino Mega 2560"
description: "Un thermomètre au dixième de degré avec un LM35 et un afficheur 7 segments, et une alarme réglable qui fait clignoter une LED. On utilise l'ADC, le multiplexage, les registres et deux timers."
notions: ["ADC et référence 1,1 V", "afficheur 7 segments", "multiplexage", "registres PORTA", "Timer 1 et Timer 3", "interruptions"]
components: ["Arduino Mega 2560", "capteur LM35", "afficheur 7 segments 4 chiffres", "potentiomètre 1 kΩ", "1 LED", "8 résistances 1 kΩ", "résistance 3,3 kΩ", "résistance 220 Ω"]
tags: ["capteur", "température", "7 segments", "timers", "interruptions"]
youtube: "https://youtu.be/OAM6kZShvFw"
videos:
  - url: "https://youtu.be/OAM6kZShvFw"
    duration: "1 h"
  - url: "https://youtu.be/QV_i8QGy2lg"
    duration: "2 h"
code: "https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/Digital_Thermometer_LM35/Digital_Thermometer_LM35.ino"
wokwi: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35/wokwi"
resources:
  - label: "Fiche projet (PDF)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Fiche_projet.pdf"
  - label: "Support de cours complet (PDF)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Support_de_cours.pdf"
  - label: "Datasheet du LM35 (PDF)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/datasheet_capteur_LM35.pdf"
  - label: "Simulation Wokwi (circuit et code)"
    url: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35/wokwi"
github: "https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35"
author: "RHIBA Zakaria"
updated: "2026-10-25"
---

# **Thermomètre numérique avec alarme réglable**

```
Projet Arduino n°5 : LM35 et afficheur 7 segments
Écrit par RHIBA Zakaria, Zakpy Academy
```

*Dans ce projet on mesure la température avec un capteur LM35, et on l'affiche sur un afficheur 7 segments avec une précision de 0,1 °C (par exemple 24.8). Un potentiomètre permet de régler une température d'alarme entre 0 et 40 °C. Quand la température dépasse cette alarme, une LED se met à clignoter.*

*Le projet a l'air simple, mais il permet de voir des notions importantes : l'ADC, le multiplexage d'un afficheur, les registres du microcontrôleur, les timers et les interruptions.*

## **Les documents du projet**

___

| Document | Contenu |
|---|---|
| [Fiche projet](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Fiche_projet.pdf) | la description, le schéma Proteus, les étapes et les annexes |
| [Support de cours](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/Support_de_cours.pdf) | toutes les explications, les erreurs fréquentes et des exercices corrigés |
| [Datasheet du LM35](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/Digital_Thermometer_LM35/docs/datasheet_capteur_LM35.pdf) | la documentation du capteur |

## **Ce qu'on va apprendre**

___

- Lire une tension avec l'ADC et choisir la bonne référence (1,1 V).
- Coder les chiffres d'un afficheur 7 segments sur un octet.
- Écrire 8 broches d'un coup avec le registre `PORTA`.
- Afficher plusieurs chiffres avec le multiplexage.
- Configurer un timer et utiliser une interruption.

## **Le matériel**

___

- Une carte Arduino Mega 2560
- Un capteur de température LM35
- Un afficheur 7 segments 4 chiffres (12 broches, par exemple 5641AS à cathode commune)
- Un potentiomètre de 1 kΩ et une résistance de 3,3 kΩ
- Une LED et une résistance de 220 Ω
- 8 résistances de 1 kΩ (une par segment)

## **Le câblage**

___

![Le schéma du projet sur Proteus : Arduino Mega 2560, LM35, afficheur 7 segments, potentiomètre et LED (ici un afficheur à anode commune avec des inverseurs 4049)](images/schema-proteus.png)

| Élément | Broche Arduino |
|---|---|
| LM35 (sortie Vout) | A0 |
| Potentiomètre (curseur) | A1 |
| Segments A, B, C, D, E, F, G, DP | 22 à 29 (PORTA) |
| Chiffres dizaines, unités, dixièmes | 52, 51, 50 |
| LED d'alarme | 32 |

> Les broches 22 à 29 forment le PORTA de l'ATmega2560. On peut donc écrire les 8 segments d'un chiffre en une ligne : `PORTA = 0x5B;` affiche un 2.

## **Mesurer la température**

___

Le LM35 donne 10 mV par degré. On utilise la référence interne de 1,1 V de l'ADC : un pas fait alors 1,1 V / 1024 = 1,07 mV, soit environ 0,1 °C.

```C++
analogReference(INTERNAL1V1);
```

Le calcul `N × 1100 / 1024` donne des mV, et comme 1 mV = 0,1 °C, c'est directement la température en dixièmes de degré (248 = 24,8 °C). On utilise un `long` parce que 1023 × 1100 dépasse la taille d'un `int` :

```C++
int mesureTemp() {
  long N = analogRead(LM35_pin);
  return (int)((N * 1100L) / 1024L);
}
```

## **Afficher sur le 7 segments**

___

Chaque segment correspond à un bit (bit 0 = A … bit 7 = DP), et on ajoute le point avec `| 0x80` :

```C++
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
```

Les segments sont partagés entre les chiffres, donc on allume un seul chiffre à la fois, 5 ms chacun : c'est le multiplexage. Le Timer 1 s'en occupe dans une interruption toutes les 5 ms (prescaler 64, `OCR1A = 1249`) :

```C++
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);              // on éteint tout
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);
  PORTA = affichage[digitCourant];         // les segments du chiffre
  digitalWrite(pinDigits[digitCourant], LOW);   // on allume ce chiffre
  digitCourant++;
  if (digitCourant >= 3) digitCourant = 0;
}
```

## **L'alarme**

___

Le potentiomètre est transformé en une température entre 0 et 40,0 °C :

```C++
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}
```

Le Timer 3 fait clignoter la LED toutes les 0,5 s (prescaler 256, `OCR3A = 31249`) quand la température dépasse l'alarme. La boucle `loop()` se contente de mesurer et de décider :

```C++
alarme = (temp > temp_trigger);
```

## **Les étapes du projet**

___

Le code de chaque étape est dans le dossier [steps](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35/steps), avec les mêmes numéros que la fiche projet :

- `Etape1_Lire_Temperature` : lire le LM35 et tester l'afficheur avec 88.8
- `Etape2_Affichage_Timer1` : afficher la température avec le Timer 1
- L'étape 3 est le câblage sur la vraie carte, avec le même code que l'étape 2
- `Etape4_Alarme_Potentiometre` : régler l'alarme avec le potentiomètre, la LED s'allume
- `Etape5_Alarme_Clignotante_Timer3` : la LED clignote avec le Timer 3

## **Tester sans matériel sur Wokwi**

___

Crée un nouveau projet Arduino Mega sur [wokwi.com](https://wokwi.com), colle `wokwi/sketch.ino` dans l'onglet du code et `wokwi/diagram.json` dans l'onglet du schéma, puis lance la simulation. Wokwi n'a pas de LM35, donc un potentiomètre sur A0 joue le rôle de la température.

> Sur la vraie carte, si ton afficheur est à anode commune (par exemple 5641BS), il faut inverser les segments (`PORTA = ~affichage[...]`) et les chiffres (`HIGH` pour sélectionner, `LOW` pour éteindre).

## **Le code complet**

___

```C++
/*********************************************************************
 *  Thermomètre numérique avec alarme - Arduino Mega 2560 (16 MHz)
 *  LM35 + afficheur 7 segments (Timer 1) + alarme réglable (Timer 3)
 *  Written by RHIBA Zakaria - Zakpy Academy
 *********************************************************************/
#define LM35_pin A0      // capteur LM35
#define POT      A1      // potentiomètre du seuil
#define LED      32      // LED d'alarme
#define DIG_D2   52      // afficheur des dizaines
#define DIG_D3   51      // afficheur des unités (+ point)
#define DIG_D4   50      // afficheur des dixièmes

// Codes 0..9, 1 = segment allumé (cathode commune, ou anode commune + 4049)
byte tabDigit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
const byte pinDigits[3] = {DIG_D2, DIG_D3, DIG_D4};

volatile byte affichage[3];          // les 3 codes à afficher
volatile byte digitCourant = 0;      // afficheur allumé en ce moment
volatile bool alarme = false;        // décidée par loop(), lue par Timer 3

int temp;                            // température en dixièmes (248 = 24,8 °C)
int temp_trigger;                    // seuil en dixièmes (0..400)

void prepareAffichage(int number);
int  mesureTemp();
int  mesureTrigger();
void initTimer1();
void initTimer3();

void setup() {
  Serial.begin(9600);

  pinMode(DIG_D2, OUTPUT);  digitalWrite(DIG_D2, HIGH);   // HIGH = éteint
  pinMode(DIG_D3, OUTPUT);  digitalWrite(DIG_D3, HIGH);
  pinMode(DIG_D4, OUTPUT);  digitalWrite(DIG_D4, HIGH);
  pinMode(LED, OUTPUT);     digitalWrite(LED, LOW);

  analogReference(INTERNAL1V1);      // 1 pas = 1,07 mV ≈ 0,1 °C
  analogRead(LM35_pin);              // 1re lecture ignorée

  DDRA  = 0xFF;                      // broches 22..29 en sortie
  PORTA = 0x00;

  initTimer1();                      // multiplexage toutes les 5 ms
  initTimer3();                      // clignotement toutes les 0,5 s

  prepareAffichage(888);             // test des segments : 88.8
  delay(3000);
}

void loop() {
  temp         = mesureTemp();
  temp_trigger = mesureTrigger();
  alarme       = (temp > temp_trigger);   // loop() décide, les timers agissent

  prepareAffichage(temp);

  Serial.print("Temp = ");
  Serial.print(temp / 10);  Serial.print(".");  Serial.print(temp % 10);
  Serial.print(" C  |  Seuil = ");
  Serial.print(temp_trigger / 10);  Serial.print(".");  Serial.print(temp_trigger % 10);
  Serial.println(alarme ? " C  -> ALARME" : " C");

  delay(500);
}

// Température en dixièmes : N x 1100 / 1024 = mV = dixièmes de °C
int mesureTemp() {
  long N = analogRead(LM35_pin);           // long : 1023 x 1100 dépasse un int
  return (int)((N * 1100L) / 1024L);
}

// Seuil en dixièmes : 0..1023 -> 0..400 (0,0 à 40,0 °C)
int mesureTrigger() {
  return map(analogRead(POT), 0, 1023, 0, 400);
}

// Découpe la valeur en 3 chiffres et prépare les codes
void prepareAffichage(int number) {
  if (number > 999) number = 999;          // 3 digits : 99,9 max
  if (number < 0)   number = 0;

  int dizaine = number / 100;
  int unite   = (number / 10) % 10;
  int dixieme = number % 10;

  if (dizaine == 0) affichage[0] = 0x00;   // pas de zéro inutile
  else              affichage[0] = tabDigit[dizaine];
  affichage[1] = tabDigit[unite] | 0x80;   // point décimal (bit 7)
  affichage[2] = tabDigit[dixieme];
}

// Timer 1 : CTC, prescaler 64, 1250 ticks de 4 us = 5 ms
void initTimer1() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 1249;
  TCCR1B |= (1 << WGM12);                  // mode CTC
  TCCR1B |= (1 << CS11) | (1 << CS10);     // prescaler 64
  TIMSK1 |= (1 << OCIE1A);                 // autorise l'interruption
  interrupts();
}

// Timer 3 : CTC, prescaler 256, 31250 ticks de 16 us = 0,5 s
void initTimer3() {
  noInterrupts();
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3  = 0;
  OCR3A  = 31249;
  TCCR3B |= (1 << WGM32);                  // mode CTC
  TCCR3B |= (1 << CS32);                   // prescaler 256
  TIMSK3 |= (1 << OCIE3A);
  interrupts();
}

// Multiplexage : un afficheur à chaque appel (toutes les 5 ms)
ISR(TIMER1_COMPA_vect) {
  digitalWrite(DIG_D2, HIGH);              // 1) tout éteindre
  digitalWrite(DIG_D3, HIGH);
  digitalWrite(DIG_D4, HIGH);

  PORTA = affichage[digitCourant];         // 2) segments du chiffre
  digitalWrite(pinDigits[digitCourant], LOW);   // 3) allumer cet afficheur

  digitCourant++;                          // 4) le suivant au prochain appel
  if (digitCourant >= 3) digitCourant = 0;
}

// Clignotement : bascule la LED toutes les 0,5 s si alarme
ISR(TIMER3_COMPA_vect) {
  if (alarme) digitalWrite(LED, !digitalRead(LED));
  else        digitalWrite(LED, LOW);
}
```

## **Pour aller plus loin**

___

- Remplace la LED par un buzzer pour avoir une vraie alarme sonore.
- Ajoute une hystérésis pour que l'alarme ne s'allume et ne s'éteigne pas sans arrêt autour de la limite.
- Garde la limite en mémoire (EEPROM) même après une coupure de courant.
- Envoie la température sur le téléphone, une première brique pour le projet de maison connectée King House.

___

Tous les cours et les vidéos sont sur **[Zakpy Academy](https://academy.zakpy.com)**.

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zakariarhiba.tech)
