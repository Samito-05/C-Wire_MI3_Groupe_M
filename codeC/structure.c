#include <stdio.h>
#include <stdlib.h>

typedef struct Station {
  long capacity;
  long consumption;
  int id;
  int balance;
} Station;

typedef struct AVLtree {
  Station* station;
  struct station* left;
  struct station* right;
} AVLtree;

typedef AVLtree* pTree;

// Fonction pour créer une nouvelle station
pTree creerStation(long capacity_, long consumption_, int id_) {
  pTree newStation = (pTree)malloc(sizeof(AVLtree)); // Allocation mémoire pour un nouveau nœud de type AVLtree
  if (newStation == NULL) {
    printf("Erreur d'allocation mémoire pour la station\n");
    exit(1);
  }

pStation createstation(long capacity_, long consumption_, int id_) {
  pStation stat = malloc(sizeof(AVLtree));
  if (stat == NULL) {
    exit(1);
  }

  stat->capacity = capacity_;
  stat->consumption = consumption_;
  stat->id = id_;
  stat->balance = 0;
  stat->left = NULL;
  stat->right = NULL;

  return stat;
}

int hauteur(pStation a) {
  int hmax;
  if (a == NULL) {
    hmax = 0;
    return hmax;
  }

  int hgauche = hauteur(a->left);
  int hdroit = hauteur(a->right);
  
  if (hgauche > hdroit){
    hmax = hgauche;
  } else{
    hmax = hdroit;
  }
  
  return hmax;
}

void miseajourequilibre(pStation station) {
  if (station != NULL) {
    station->balance = hauteur(station->right) - hauteur(station->left);
  }
}

pStation rotationLeft(pStation a) {
  pStation b = a->right;
  pStation c = b->left;
  a->right = c;
  b->left = a;
  miseajourequilibre(a);
  miseajourequilibre(b);
  return b;
}

pStation rotationRight(pStation a) {
  pStation b = a->left;
  pStation c = b->right;

  a->left = c;
  b->right = a;

  miseajourequilibre(a);
  miseajourequilibre(b);

  return b;
}

pStation doubleRotationLeft(pStation station) {
  station->right = rotationRight(station->right);
  return rotationLeft(station);
}

pStation doubleRotationRight(pStation station) {
  station->left = rotationLeft(station->left);
  return rotationRight(station);
}

pStation equilibrage(pStation station){
  if (station->balance >= 2){
    if(station->right >= 0){
      return rotationLeft(station);
    } else{
      return doubleRotationLeft(station);
    }
  }
  
  if(station->balance <= -2){
    if(station->left <= 0){
      return rotationRight(station);
    } else{
      return doubleRotationRight(station);
    }
  }
  
  return station;
}

pStation insert(pStation stat, long capacity, long consumption, int id) {
  if (stat == NULL) {
    return createstation(capacity, consumption, id);
  } else if (consumption < stat->consumption){
    stat->left = insert(stat->left, capacity, consumption, id);
  }
  else if(consumption > stat->consumption){
    stat->right = insert(stat->right, capacity, consumption, id);
  }
  else{
    return stat;
  }
  return equilibrage(stat);
}
