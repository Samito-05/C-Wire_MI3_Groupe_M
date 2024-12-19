# C-Wire_MI3_Groupe_M

Projet CY Tech 3ème Semestre : **PROCOPPE, TRAN-PHAT, PELISSIER**

---

## Table des matières
1. [Résumé du projet](#résumé-du-projet)
2. [Avancement hebdomadaire](#avancement-hebdomadaire)
    - [Semaine du 25/11](#semaine-du-2511)
    - [Semaine du 02/12](#semaine-du-0212)
    - [Semaine du 09/12](#semaine-du-0912)
    - [Semaine du 16/12](#semaine-du-1612)
3. [Exécuter le projet](#comment-exécuter-le-projet)
4. [Organisation du projet](#organisation-du-projet)

---

## Résumé du projet

Ce projet analyse un fichier de données comportant différentes stations électriques (HV-B, HV-A ou LV) ainsi que leurs consommations. Il permet de filtrer les données selon un type de station et un type de consommateur (entreprises ou individus), puis de trier les stations par ID à l'aide d'un AVL. Enfin, le programme calcule la somme des charges (Load) des entreprises ou individus pour chaque station et génère un fichier de sortie structuré avec les capacités totales et les consommations.

---

## Avancement hebdomadaire

### Semaine du 25/11 :
    - Création du dossier
    - Ajout des fichiers dans GitHub

### Semaine du 02/12 :
    - Début shell :
        - Ajout de la fonction d'aide
        - Vérification des paramètres
        - Compilation + vérification
        - Création des dossiers 'tmp' & 'graphs'
    - Début C :
        - Implémentation des fonctions de base
        - Création des structures
        - Gestion des documents via Shell
    
### Semaine du 09/12 :
    - Gestion du fichier trié en C
    - Création des fichiers pour la gestion d'un AVL (structures et fonctions)

### Semaine du 16/12 :
    - Création du fichier `main.c` :
        - Traitement des données triées par le Shell.
        - Création d’un fichier dans le dossier `tests`.
    - Génération de graphiques.
    
---

## Exécuter le projet

Pour exécuter ce projet, suivez les étapes ci-dessous :
1. Dans le termnial Bash, utiliser la commande :
```bash
./c-wire.sh nom_du_fichier option
```

---

## Organisation du projet

Voici l'organisation des dossiers et fichiers du projet :

- **codeC/** : Contient les fichiers source en langage C
  - `main.c` : Programme principal
  - `station.c` : Fichier source pour la gestion des stations
  - `station.h` : Fichier d'en-tête associé à `station.c`
  - `Makefile` : Fichier pour automatiser la compilation du projet

- **graphs/** (**créé après exécution**): Dossier destiné aux graphiques générés par le programme

- **Input/** : Dossier contenant les fichiers d'entrée ou données nécessaires à l'exécution

- **tests/** : Dossier contenant les fichiers de sorties 

- **tmp/** (**créé après exécution**): Dossier contenant les fichiers temporaires et triés par le Shell

- **Fichiers principaux :**
  - `c-wire.sh` : Script Shell principal permettant d'automatiser les étapes (compilation, exécution, etc.)
  - `README.md` : Documentation du projet
  - `Projet_C-Wire_preIng2_2024_2025-v1.2.pdf` : Fichier pdf contenant des informations liées au projet

