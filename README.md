# C-Wire_MI3_Groupe_M

---

## Sommaire
1. [Résumé du Projet](#résumé-du-projet)
2. [Prérequis](#Prérequis)
3. [Exécuter le Projet](#exécuter-le-projet)
4. [Récupérer les Résultats](#récupérer-les-résultats)
5. [Organisation du Projet](#organisation-du-projet)
6. [Rapport du Projet (pdf)](#Rapport-du-projet)

---

## Résumé du Projet

Ce projet analyse un fichier de données comportant différentes centrales électriques et stations électriques (HV-B, HV-A ou LV) ainsi que leurs consommations. Il permet de filtrer les données selon un type de station et un type de consommateur (entreprises ou individus), puis de trier les stations par ID à l'aide d'un AVL. Enfin, le programme calcule la somme des charges (Load) des entreprises ou individus pour chaque station et génère un fichier de sortie trié par ordre croissant des capacités totales et les consommations.

---

## Prérequis

Avant d'exécuter le programme, assurez-vous que votre machine possède les outils suivants :  
- **GCC Compiler :** compilateur pour le C afin de convertir le code source en un exécutable
- **Makefile :** automatiser la compilation et la gestion des dépendances
- **Gnuplot :** traçage graphique utilisé pour générer des visualisations basées sur les données de sortie du programme
- *Git (sous Windows) :* interface permettant d'exécuter des commandes Git et des scripts Bash sous Windows

---

## Exécuter le Projet

Pour exécuter ce projet, suivez les étapes ci-dessous :
1. Télécharger le dossier du code
2. Dézipper le dossier
3. Dans le termnial Bash, utiliser la commande :
```bash
./c-wire.sh nom_fichier type_station type_consommateur ID_power_plant(optionnel)
```
- **Nom du fichier : Input/nom_fichier**  
- **Type de stations possibles : hvb, hva, lv**  
- **Type de consommateurs possibles : comp, indiv, all**  
- (Optionnel) ID possibles pour les centrales électriques : 1, 2, 3, 4, 5  
### ❗Attention❗ Combinaisons interdites : hvb all, hvb indiv, hva all, hva indiv

*Si besoin d'aide, exécuter la commande :* 
```bash
./c-wire.sh --h
```

---

## Récupérer les Résultats

A la fin de l'exécution du code : 
  - Dossier `tests/` pour récupérer nos anciennes compilations
  - Dossier `tmp/` pour récupérer les graphiques
  - Dossier `output/` pour récupérer les résultats (Il faut les télécharger puisqu'ils s'effaçent à chaque compilation)

A la fin du programme, la durée totale d'exécution du code sera affiché par un compteur en secondes.

---

## Organisation du Projet

Voici l'organisation des dossiers et fichiers du projet :

- **codeC/** : Contient les fichiers source en langage C
  - `main.c` : Programme principal
  - `station.c` : Fichier source pour la gestion des stations
  - `station.h` : Fichier d'en-tête associé à `station.c`
  - `Makefile` : Fichier pour automatiser la compilation du projet

- **Input/** : Dossier contenant les fichiers d'entrée ou données nécessaires à l'exécution

- **tests/** : Dossier contenant les résultats d'exécutions précédentes (fichiers créés par le C)

- **tmp/** (créé après exécution) : Dossier contenant les fichiers temporaires et triés par le Shell

- **graphs/** (créé après exécution) : Dossier destiné aux graphiques générés par le programme

- **output/** (créé après exécution) : Dossier avec le dernier résultat de compilation

- **Fichiers principaux :**
  - `c-wire.sh` : Script Shell principal permettant d'automatiser les étapes (compilation, exécution, etc)
  - `README.md` : Documentation du projet
  - `Projet_C-Wire_preIng2_2024_2025-v1.2.pdf` : Fichier pdf contenant des informations liées au projet
  - `Rapport.pdf` : Rapport du projet (pdf)

---

## Rapport du Projet

[Télécharger le rapport (pdf)](Rapport.pdf)

---

## Auteurs 

**PROCOPPE Sam**  
**TRAN-PHAT Hugo**  
**PELISSIER JULES**
