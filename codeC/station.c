#include "Station.h"

// Function to return the maximum of two integers.
int max(int a, int b){
  if(a < b){
    return b;
  } else{
    return a;
  }
}

// Function to return the minimum of two integers.
int min(int a, int b){
  if(a < b){
    return a;
  } else{
    return b;
  }
} 

// Function to create a new node in the AVL tree.
pTree createTree(long long int capacity_, long long int consumption_, int id_){
  pTree treeNode = malloc(sizeof(AVLtree));
  if (treeNode == NULL) {
    exit(1);
  }

    // Initialize the node's data fields.
  treeNode->id = id_;
  treeNode->capacity = capacity_;
  treeNode->consumption = consumption_;
    
  treeNode->left = NULL; 
  treeNode->right = NULL;

  treeNode->balance = 0;
  
  return treeNode;
}

// Function for a single left rotation to balance the AVL tree.
pTree rotationLeft(pTree node) {
  pTree pivot = node->right;
  node->right = pivot->left;
  pivot->left = node;

    // Update balance factors.
  int eq_node = node->balance;
  int eq_pivot = pivot->balance;
  
  node->balance = eq_node - max(eq_pivot, 0) - 1;
  pivot->balance = min(eq_node - 2, min(eq_pivot + eq_node - 2, eq_pivot - 1));
    
  return pivot;
}
// Function for a single right rotation to balance the AVL tree.
pTree rotationRight(pTree node) {
    pTree pivot = node->left;
    node->left = pivot->right;
    pivot->right = node;

    // Update balance factors.
    int eq_node = node->balance;
    int eq_pivot = pivot->balance;

    node->balance = eq_node - min(eq_pivot, 0) + 1;
    pivot->balance = max(eq_node + 2, max(eq_pivot + eq_node + 2, eq_pivot + 1));

    return pivot;
  }

// Function for a double left rotation (right rotation followed by left rotation).
pTree doubleRotationLeft(pTree node) {
  node->right = rotationRight(node->right);
  return rotationLeft(node);
}

// Function for a double right rotation (left rotation followed by right rotation).
pTree doubleRotationRight(pTree node) {
  node->left = rotationLeft(node->left);
  return rotationRight(node);
}

// Function to balance an AVL tree node.
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

// Function to insert a new node into the AVL tree.
pTree insert(pTree node, pTree new, int* height) {
  
  if (node == NULL) {
    *height = 1;
    return new;
  }

    // If the node already exists, update its data.
  if (node->id == new->id) {
    node->capacity += new->capacity;
    node->consumption += new->consumption;
    *height = 0;  
    return node;
  }

    // Insert into the left subtree if the new node's ID is smaller.
  if (new->id < node->id) {
    node->left = insert(node->left, new, height);
    *height = -(*height);  
  }

    // Insert into the right subtree if the new node's ID is larger.
  else if (new->id > node->id) {
    node->right = insert(node->right, new, height);
  }

    // Update balance factor and rebalance if necessary.
  if (*height != 0) {
    node->balance += *height; 
    node = balanceAVL(node);  

        // Update height based on balance factor.
    if (node->balance == 0) {
      *height = 0;
    } else {
      *height = 1;
    }
  }

  return node;
}

// Function to traverse the AVL tree in order and write the data to a file.
void traversal(pTree node, FILE *file) {
    if (node == NULL) {
        return;
    }

    traversal(node->left, file);
    fprintf(file, "%d:%lld:%lld\n", node->id, node->capacity, node->consumption);
    traversal(node->right, file);
}

// Function to free all dynamically allocated memory in the AVL tree.
void freeTree(pTree node){
  if(node == NULL){
    return;
  }

  freeTree(node->left);
  freeTree(node->right);
  free(node);
  
}
