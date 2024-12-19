# C-Wire_MI3_Groupe_M

---

## Sommaire
1. [Résumé du Projet](#résumé-du-projet)
2. [Exécuter le Projet](#exécuter-le-projet)
3. [Récupérer les Résultats](#récupérer-les-résultats)
4. [Organisation du Projet](#organisation-du-projet)

---

## Résumé du projet

Ce projet analyse un fichier de données comportant différentes stations électriques (HV-B, HV-A ou LV) ainsi que leurs consommations. Il permet de filtrer les données selon un type de station et un type de consommateur (entreprises ou individus), puis de trier les stations par ID à l'aide d'un AVL. Enfin, le programme calcule la somme des charges (Load) des entreprises ou individus pour chaque station et génère un fichier de sortie structuré avec les capacités totales et les consommations.

---

## Exécuter le projet

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
### Attention ! Combinaisons interdites : hvb all, hvb indiv, hva all, hva indiv

*Si besoin d'aide, exécuter la commande :* 
```bash
./c-wire.sh -h
```

---

## Récupérer les résultats

A la fin de l'exécution du code : 
  - Dossier `tests/` pour récupérer les données
  - Dossier `tmp/` pour récupérer les graphiques

A la fin du programme, la durée totale d'exécution du code sera affiché par un compteur en secondes.

---

## Organisation du projet

Voici l'organisation des dossiers et fichiers du projet :

- **codeC/** : Contient les fichiers source en langage C
  - `main.c` : Programme principal
  - `station.c` : Fichier source pour la gestion des stations
  - `station.h` : Fichier d'en-tête associé à `station.c`
  - `Makefile` : Fichier pour automatiser la compilation du projet

- **Input/** : Dossier contenant les fichiers d'entrée ou données nécessaires à l'exécution

- **tests/** : Dossier contenant les fichiers de sorties créés par le C

- **tmp/** (créé après exécution) : Dossier contenant les fichiers temporaires et triés par le Shell

- **graphs/** (créé après exécution) : Dossier destiné aux graphiques générés par le programme

- **Fichiers principaux :**
  - `c-wire.sh` : Script Shell principal permettant d'automatiser les étapes (compilation, exécution, etc)
  - `README.md` : Documentation du projet
  - `Projet_C-Wire_preIng2_2024_2025-v1.2.pdf` : Fichier pdf contenant des informations liées au projet
  - `Rapport.pdf` : Rapport du projet (pdf)

---

## Auteurs 

**PROCOPPE Sam**  
**TRAN-PHAT Hugo**  
**PELISSIER JULES**
