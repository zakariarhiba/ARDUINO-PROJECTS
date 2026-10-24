# Utiliser ce dépôt sur academy.zakpy.com

Ce fichier explique comment le site peut lire les projets de ce dépôt pour en faire des leçons (article + vidéo YouTube + documents).

## 1. La liste des projets

Tous les projets sont regroupés dans un seul fichier JSON :

```
https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/projects.json
```

Il contient un tableau `projects`, trié par `order`. Chaque projet a les mêmes champs que l'en-tête de son readme (voir plus bas), plus :

- `folder` : le nom du dossier dans le dépôt
- `readme` : le lien brut vers le readme du projet

## 2. Le contenu d'une leçon

Le texte de la leçon, c'est le readme du projet, en Markdown :

```
https://raw.githubusercontent.com/zakariarhiba/ARDUINO-PROJECTS/main/<folder>/readme.md
```

Le fichier commence par un en-tête entre deux lignes `---` (front matter). Le site doit le lire pour les informations, et afficher seulement ce qui vient après comme article. Tous les liens du readme sont des liens complets (https://…), donc ils marchent aussi sur le site.

## 3. Les champs de l'en-tête

| Champ | Exemple | À quoi il sert |
|---|---|---|
| `title` | "Faire clignoter une LED" | le titre de la leçon |
| `slug` | "led-clignotante" | l'adresse de la page sur le site |
| `order` | 1 | l'ordre dans la liste |
| `level` | "Débutant" | Débutant ou Intermédiaire |
| `duration` | "15 min" | la durée estimée |
| `board` | "Arduino Uno ou Mega" | la carte utilisée |
| `description` | une phrase | le résumé affiché sur la carte de la leçon |
| `notions` | liste | ce qu'on apprend |
| `components` | liste | le matériel |
| `tags` | liste | pour filtrer les leçons |
| `youtube` | "" | **le lien de la vidéo, à remplir quand elle est en ligne** |
| `code` | lien | le fichier .ino brut |
| `wokwi` | lien | (optionnel) le circuit de simulation |
| `resources` | liste de `label` + `url` | les documents à télécharger (PDF, datasheets, liens) |
| `github` | lien | le dossier du projet sur GitHub |
| `author`, `updated` | | l'auteur et la date de mise à jour |

## 4. Ajouter un projet ou une vidéo

1. Crée le dossier du projet avec son readme (copie l'en-tête d'un autre projet et change les valeurs).
2. Quand la vidéo est publiée, colle son lien dans le champ `youtube` du readme.
3. Lance `python3 tools/build_index.py` pour mettre à jour `projects.json`.
4. Commit et push : le site prend la nouvelle version.
