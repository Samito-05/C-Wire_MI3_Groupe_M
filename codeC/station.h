#IFNDEF STATION_H
#DEFINE STATION_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLtree {
  int id;
  long capacity;
  long consumption;
  struct AVLtree* left;  
  struct AVLtree* right; 
  int balance;
} AVLtree;

typedef AVLtree* pTree;


int max(int, int);
int min(int, int);
pTree createTree(long, long, int);
pTree rotationLeft(pTree);
pTree rotationRight(pTree);
pTree doubleRotationLeft(pTree);
pTree doubleRotationRight(pTree);
pTree balanceAVL(pTree);
pTree insert(pTree, pTree, int*);
void infix(pTree);
void freeTree(pTree);

#ENDIF
