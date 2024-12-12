#include "Station.h"

int max(int a, int b){
  if(a < b){
    return b;
  } else{
    return a;
  }
}

int min(int a, int b){
  if(a < b){
    return a;
  } else{
    return b;
  }
} 

pTree createTree(long capacity_, long consumption_, int id_){
  pTree treeNode = malloc(sizeof(AVLtree));
  if (treeNode == NULL) {
    exit(1);
  }
  
  treeNode->id = id_;
  treeNode->capacity = capacity_;
  treeNode->consumption = consumption_;
    
  treeNode->left = NULL; 
  treeNode->right = NULL;

  treeNode->balance = 0;
  
  return treeNode;
}

pTree rotationLeft(pTree node) {
  pTree pivot = node->right;
  node->right = pivot->left;
  pivot->left = node;

  int eq_node = node->balance;
  int eq_pivot = pivot->balance;
  
  node->balance = eq_node - max(eq_pivot, 0) - 1;
  pivot->balance = min(eq_node - 2, min(eq_pivot + eq_node - 2, eq_pivot - 1));
    
  return pivot;
}

pTree rotationRight(pTree node) {
    pTree pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;

    int eq_node = node->balance;
    int eq_pivot = pivot->balance;

    node->balance = eq_node - min(eq_pivot, 0) + 1;
    pivot->balance = max(eq_node + 2, max(eq_pivot + eq_node + 2, eq_pivot + 1));

    return pivot;
  }

pTree doubleRotationLeft(pTree node) {
  node->right = rotationRight(node->right);
  return rotationLeft(node);
}

pTree doubleRotationRight(pTree node) {
  node->left = rotationLeft(node->left);
  return rotationRight(node);
}

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

pTree insert(pTree node, pTree new, int* height) {
  if(new == NULL){
    exit(2);
  }
  if (node == NULL) {
    *height = 1;
    return new;
  }
  else if(node->id == new->id){
    node->capacity += new->capacity;
    node->consumption = new->consumption;
    
    *height = 0;
    return node;
  }
  else if(new->id < node->id){
    node->left = insert(node->left, new, height);
    *height = -(*height);
  }
  else if(new->id > node->id){
    node->right = insert(node->right, new, height);
  } 
  else{
    *height = 0;
    return node;
  }

  if(*height != 0){
    node->balance += *height; 
    node = balanceAVL(node);

    if(node->balance == 0){
      *height = 0;
    } else{
      *height = 1;
    }
  }

  return node;
}

void infix(pTree node){
  if(node == NULL){
    return;
  }

  infix(node->left);
  printf("%d; %ld; %ld\n", node->id, node->consumption, node->consumption);
  infix(node->right);
}

void freeTree(pTree node){
  if(node == NULL){
    return;
  }

  freeTree(node->left);
  freeTree(node->right);
  free(node);
  
}
