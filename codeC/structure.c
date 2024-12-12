#include <stdio.h>
#include <stdlib.h>

/*
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
*/


pStation createstation(long capacity_, long consumption_, int id_) {
  pStation stat = malloc(sizeof(Station)); 
  if (stat == NULL) {
    exit(1);
  }

  stat->capacity = capacity_;
  stat->consumption = consumption_;
  stat->id = id_;
  stat->balance = 0;

  return stat;
}

pTree createTree(pStation station) {
  pTree treeNode = malloc(sizeof(AVLtree));
  if (treeNode == NULL) {
    exit(1);
  }

  treeNode->station = station;
  treeNode->left = NULL; 
  treeNode->right = NULL;

  return treeNode;
}

int height(pTree node) {
  int hmax;
  if (node == NULL) {
    hmax = 0;
    return hmax;
  }

  int hleft = height(node->left);
  int hright = height(node->right);
  
  if (hleft > hright){
    hmax = hleft;
  } else{
    hmax = hright;
  }
  
  return hmax;
}

void change_balance(pTree node) {
  if (node != NULL) {
    node->station->balance = height(node->right) - height(node->left);
  }
}

pTree rotationLeft(pTree node) {
  pTree rightChild = node->right;
  pTree leftSubtree = rightChild->left;

  rightChild->left = node;
  node->right = leftSubtree;

  change_balance(node);
  change_balance(rightChild);

  return rightChild;
}

pTree rotationRight(pTree node) {
  pTree leftChild = node->left;
  pTree rightSubtree = leftChild->right;

  leftChild->right = node;
  node->left = rightSubtree;

  change_balance(node);
  change_balance(leftChild);

  return leftChild;
}

pTree doubleRotationLeft(pTree node) {
  node->right = rotationRight(node->right);
  return rotationLeft(node);
}

pTree doubleRotationRight(pTree node) {
  node->left = rotationLeft(node->left);
  return rotationRight(node);
}

pTree balancing(pTree node) {
  change_balance(node);

  if (node->station->balance >= 2) {
    if (node->right->station->balance >= 0) {
      return rotationLeft(node);
    } else {
      return doubleRotationLeft(node);
    }
  }

  if (node->station->balance <= -2) {
    if (node->left->station->balance <= 0) {
      return rotationRight(node);
    } else {
      return doubleRotationRight(node);
    }
  }

  return node;
}

pTree insert(pTree root, long capacity, long consumption, int id) {
  if (root == NULL) {
    return createTree(createStation(capacity, consumption, id));
  }

  if (consumption < root->station->consumption) {
    root->left = insert(root->left, capacity, consumption, id);
  } else if (consumption > root->station->consumption) {
    root->right = insert(root->right, capacity, consumption, id);
  } else {
    return root; // Duplicate consumption, do nothing
  }

  return balancing(root);
}