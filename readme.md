# **Projets Arduino : Zakpy Academy**

*Chaque dossier de ce dépôt est un projet Arduino complet, avec son code, ses explications et parfois une fiche projet en PDF. On commence par les bases (LED, boutons, capteurs) et on avance vers des projets plus complets. Toutes ces briques serviront plus tard pour un grand projet : King House, une maison connectée qu'on commande depuis Internet.*

Les cours en vidéo et les supports sont sur **[academy.zakpy.com](https://academy.zakpy.com)**.

## **Les projets**

___

| # | Projet | Niveau | Ce qu'on apprend |
|---|---|---|---|
| 1 | [Faire clignoter une LED](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/LED-Flashing) | Débutant | `pinMode`, `digitalWrite`, `delay` |
| 2 | [Changer la couleur de deux LED RGB avec une struct](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/RGB_LEDs) | Débutant | LED RGB, `struct`, fonctions |
| 3 | [Commander une lampe 220 V avec un module relais](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Two_Relay_Module) | Débutant | relais, bouton avec pull-up |
| 4 | [Mesurer la température et l'humidité avec un DHT11](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/TEMPERATURE_Sensor_dht) | Débutant | bibliothèques, capteur numérique |
| 5 | [Thermomètre numérique avec alarme réglable](https://github.com/zakariarhiba/ARDUINO-PROJECTS/tree/main/Digital_Thermometer_LM35) | Intermédiaire | ADC, 7 segments, multiplexage, timers, interruptions |

## **Comment est organisé un projet**

___

```
Nom_Du_Projet/
├── readme.md            le cours du projet (explications + code complet)
├── Nom_Du_Projet.ino    le code à ouvrir dans l'IDE Arduino
├── steps/               (si besoin) le code de chaque étape
├── wokwi/               (si besoin) le circuit pour tester sans matériel sur wokwi.com
└── docs/                (si besoin) la fiche projet, le support de cours, les datasheets
```

## **Utiliser un projet**

___

1. Installe l'[IDE Arduino](https://www.arduino.cc/en/software).
2. Ouvre le fichier `.ino` du projet (il doit rester dans un dossier qui a le même nom).
3. Choisis ta carte dans *Outils > Type de carte*, puis téléverse.
4. Si le projet utilise une bibliothèque, son readme explique laquelle installer.

## **Pour le site**

___

Chaque `readme.md` commence par un petit bloc d'informations (titre, niveau, durée, lien YouTube, documents…) que le site [academy.zakpy.com](https://academy.zakpy.com) lit pour afficher la leçon. Le fichier [projects.json](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/projects.json) regroupe tous les projets en un seul fichier. Les détails sont dans [SITE.md](https://github.com/zakariarhiba/ARDUINO-PROJECTS/blob/main/SITE.md).

___

Une question ou une collaboration ? Tu peux me contacter depuis mon portfolio : [Rhiba Zakaria](https://zak-rhiba.codes)
