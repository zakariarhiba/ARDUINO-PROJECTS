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
| `videos` | liste de `url` + `duration` | (optionnel) quand la vidéo est en plusieurs parties : une ligne par partie, dans l'ordre (Partie 1, Partie 2…). `youtube` garde le lien de la partie 1 |
| `code` | lien | le fichier .ino brut |
| `wokwi` | lien | (optionnel) le circuit de simulation |
| `resources` | liste de `label` + `url` | les documents à télécharger (PDF, datasheets, liens) |
| `github` | lien | le dossier du projet sur GitHub |
| `cover` | "images/montage.jpg" | (optionnel) la photo de la carte du projet |
| `author`, `updated` | | l'auteur et la date de mise à jour |

## 4. Les images (photos et schémas)

Les photos du montage et les schémas d'un projet vont dans son dossier `images/` (PNG, JPG ou WebP, moins de 500 Ko si possible). Dans le readme, on les met avec un chemin relatif, et le texte entre crochets sert de légende :

```
![Le montage sur la breadboard](images/montage.jpg)
```

GitHub les affiche, et le site copie chaque image utilisée sur ses propres pages. Le champ optionnel `cover` de l'en-tête (par exemple `cover: "images/montage.jpg"`) donne la photo de la carte du projet sur le site ; sans `cover`, le site prend la miniature de la vidéo.

## 5. Les traductions (anglais et arabe)

Le readme en français (`readme.md`) est la source. À côté, `readme.en.md` (anglais) et `readme.ar.md` (arabe clair, pas la darija) sont ses traductions. Leur en-tête ne contient que les champs traduits : `title`, `description`, `board`, `notions`, `components`, et `resources` si les noms des documents changent. Tout le reste (slug, vidéo, code…) vient du readme français.

En arabe, on traduit aussi les mots techniques (résistance → مقاومة, broche → منفذ, afficheur 7 segments → شاشة العرض ذات القطع السبع…) ; on ne garde en lettres latines que les noms (Arduino, LM35, LED, DHT11) et le code, sinon les lignes se mélangent.

Le code reste le même que le fichier `.ino`, commentaires compris. Le site affiche la version qui correspond à la langue choisie par le visiteur ; s'il n'y a pas de traduction, il affiche le français avec une petite note. Quand on change le readme français, il faut changer les traductions aussi.

## 6. Ajouter un projet ou une vidéo

1. Crée le dossier du projet avec son readme (copie l'en-tête d'un autre projet et change les valeurs).
2. Quand la vidéo est publiée, colle son lien dans le champ `youtube` du readme.
3. Lance `python3 tools/build_index.py` pour mettre à jour `projects.json`.
4. Commit et push : le site prend la nouvelle version.
