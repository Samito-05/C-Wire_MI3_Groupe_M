#include <stdio.h>
#include <stdlib.h>
#define couleur(param) printf("\033[%sm",param)

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