#ifndef AVL_TREE_H
#define AVL_TREE_H

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
  struct AVLtree* left;
  struct AVLtree* right;
} AVLtree;


typedef Station* pStation;
typedef AVLtree* pTree;


pStation createstation(long capacity_, long consumption_, int id_);
pTree createTree(pStation station);
int height(pTree node);
void change_balance(pTree node);
pTree rotationLeft(pTree node);
pTree rotationRight(pTree node);
pTree doubleRotationLeft(pTree node);
pTree doubleRotationRight(pTree node);
pTree balancing(pTree node);
pTree insert(pTree root, long capacity, long consumption, int id);

#endif