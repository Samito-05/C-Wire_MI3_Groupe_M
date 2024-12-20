#include "Station.h"

// Fonction pour retourner le maximum entre deux entiers
int max(int a, int b){
  if(a < b){
    return b;
  } else{
    return a;
  }
}

// Fonction pour retourner le minimum entre deux entiers
int min(int a, int b){
  if(a < b){
    return a;
  } else{
    return b;
  }
} 

// Fonction pour créer un nouveau noeud d'arbre AVL
pTree createTree(long long int capacity_, long long int consumption_, int id_){
  pTree treeNode = malloc(sizeof(AVLtree));
  if (treeNode == NULL) {
    exit(1);
  }

  // Initialisation des champs du noeud
  treeNode->id = id_;
  treeNode->capacity = capacity_;
  treeNode->consumption = consumption_;
    
  treeNode->left = NULL; 
  treeNode->right = NULL;

  treeNode->balance = 0;
  
  return treeNode;
}

// Rotation simple à gauche pour équilibrer l'arbre AVL.
pTree rotationLeft(pTree node) {
  pTree pivot = node->right;
  node->right = pivot->left;
  pivot->left = node;

   // Mise à jour des facteurs d'équilibre.
  int eq_node = node->balance;
  int eq_pivot = pivot->balance;
  
  node->balance = eq_node - max(eq_pivot, 0) - 1;
  pivot->balance = min(eq_node - 2, min(eq_pivot + eq_node - 2, eq_pivot - 1));
    
  return pivot;
}
// Rotation simple à droite pour équilibrer l'arbre AVL.
pTree rotationRight(pTree node) {
    pTree pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;

    // Mise à jour des facteurs d'équilibre.
    int eq_node = node->balance;
    int eq_pivot = pivot->balance;

    node->balance = eq_node - min(eq_pivot, 0) + 1;
    pivot->balance = max(eq_node + 2, max(eq_pivot + eq_node + 2, eq_pivot + 1));

    return pivot;
  }

// Rotation double à gauche (rotation droite suivie d'une rotation gauche).
pTree doubleRotationLeft(pTree node) {
  node->right = rotationRight(node->right);
  return rotationLeft(node);
}

// Rotation double à droite (rotation gauche suivie d'une rotation droite).
pTree doubleRotationRight(pTree node) {
  node->left = rotationLeft(node->left);
  return rotationRight(node);
}

// Fonction pour équilibrer un noeud de l'arbre AVL.
pTree balanceAVL(pTree node) {
  if (node->balance >= 2) {
    if (node->right->balance >= 0) {
      return rotationLeft(node);
    } else {
      return doubleRotationLeft(node);
    }
  }

  if (node->balance <= -2) {
    if (node->left->balance <= 0) {
      return rotationRight(node);
    } else {
      return doubleRotationRight(node);
    }
  }
  
  return node;
}

// Fonction pour insérer un noeud dans l'arbre AVL.
pTree insert(pTree node, pTree new, int* height) {
  
  if (node == NULL) {
    *height = 1;
    return new;
  }

  // Si l'identifiant du noeud existe déjà, met à jour les données.
  if (node->id == new->id) {
    node->capacity += new->capacity;
    node->consumption += new->consumption;
    *height = 0;  
    return node;
  }

  // Insertion à gauche si l'identifiant est plus petit.
  if (new->id < node->id) {
    node->left = insert(node->left, new, height);
    *height = -(*height);  
  }

  // Insertion à droite si l'identifiant est plus grand.
  else if (new->id > node->id) {
    node->right = insert(node->right, new, height);
  }

  // Mise à jour du facteur d'équilibre après insertion
  if (*height != 0) {
    node->balance += *height; 
    node = balanceAVL(node);  

    // Mise à jour de la hauteur après équilibrage.
    if (node->balance == 0) {
      *height = 0;
    } else {
      *height = 1;
    }
  }

  return node;
}

// Fonction pour parcourir l'arbre AVL en ordre croissant et écrire dans un fichier.
void traversal(pTree node, FILE *file) {
    if (node == NULL) {
        return;
    }

    traversal(node->left, file);
    fprintf(file, "%d:%lld:%lld\n", node->id, node->capacity, node->consumption);
    traversal(node->right, file);
}

// Fonction pour libérer toute la mémoire allouée pour l'arbre AVL.
void freeTree(pTree node){
  if(node == NULL){
    return;
  }

  freeTree(node->left);
  freeTree(node->right);
  free(node);
  
}
