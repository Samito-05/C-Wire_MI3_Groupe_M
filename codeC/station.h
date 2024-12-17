#ifndef STATION_H
#define STATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLtree {
  int id;
  long long int capacity;
  long long int consumption;
  struct AVLtree* left;  
  struct AVLtree* right; 
  int balance;
} AVLtree;

typedef AVLtree* pTree;


int max(int, int);
int min(int, int);
pTree createTree(long long int capacity, long long int load, int);
pTree rotationLeft(pTree);
pTree rotationRight(pTree);
pTree doubleRotationLeft(pTree);
pTree doubleRotationRight(pTree);
pTree balanceAVL(pTree);
pTree insert(pTree, pTree, int*);
void infix(pTree);
void freeTree(pTree);

#endif
