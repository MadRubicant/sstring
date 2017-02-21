// Method of using the preprocessor for generics taken from https://stackoverflow.com/questions/16522341/pseudo-generics-in-c

#include "generic_macros.h"
// BST_COMPARE returns negative if x < y, 0 if equal, positive if x > y
#define bst_node(T) _TOKENPASTE(_bst_node_, T)
#define bst_insert(T) _TOKENPASTE(_bst_insert_, T)
#define bst_contains(T) _TOKENPASTE(_bst_contains_, T)
#define bst_delete(T) _TOKENPASTE(_bst_remove_, T)
#define bst_free(T) _TOKENPASTE(_bst_free_, T)
#define bst_predecessor(T) _TOKENPASTE(_bst_predecessor, T)
#define bst_successor(T) _TOKENPASTE(_bst_successor, T)

#ifndef BST_COMPARE
#define BST_COMPARE(x, y) (x - y)
#endif

#ifdef BST_TYPE
#include <stdlib.h>
#include "stdint.h"

typedef struct bst_node(BST_TYPE) bst_node(BST_TYPE);
bst_node(BST_TYPE)* bst_insert(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data);
int bst_contains(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data);
bst_node(BST_TYPE)* bst_delete(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data);
void bst_free(BST_TYPE)(bst_node(BST_TYPE)* root);

#ifdef BST_IMPLEMENTATION
typedef struct bst_node(BST_TYPE) {
  struct bst_node(BST_TYPE)* left;
  struct bst_node(BST_TYPE)* right;
  BST_TYPE data;
} bst_node(BST_TYPE);

static bst_node(BST_TYPE)* bst_predecessor(BST_TYPE)(bst_node(BST_TYPE)* root, int* depth) {
  if (root == NULL) {
    return root;
  }
  else if (root->right != NULL) {
    *depth++;
    return bst_predecessor(BST_TYPE)(root->right, depth);
  }
  else {
    *depth++;
    return root;
  }
};

static bst_node(BST_TYPE)* bst_successor(BST_TYPE)(bst_node(BST_TYPE)* root, int* depth) {
  if (root == NULL) {
    return root;
  }
  else if (root->left != NULL) {
    *depth++;
    return bst_successor(BST_TYPE)(root->left, depth);
  }
  else {
    *depth++;
    return root;
  }
};

// bst_node* bst_insert(bst_node* root, data)
bst_node(BST_TYPE)* bst_insert(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data) {
  if (root == NULL) {
    root = malloc(sizeof root);
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
  }
  // Data < root
  else if (BST_COMPARE(data, root->data) < 0) {
    return bst_insert(BST_TYPE)(root->left, data);
  }
  else {
    return bst_insert(BST_TYPE)(root->right, data);
  }
};


int bst_contains(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data) {
  if (root == NULL)
    return 0;
  else if (BST_COMPARE(data, root->data) < 0)
    return bst_contains(BST_TYPE)(root->left, data);
  else
    return bst_contains(BST_TYPE)(root->right, data);
};


bst_node(BST_TYPE)* bst_delete(BST_TYPE)(bst_node(BST_TYPE)* root, BST_TYPE data) {
  if (root == NULL)
    return root
      ;
  else if (BST_COMPARE(data, root->data) < 0) {
    bst_node(BST_TYPE)* tmp = bst_delete(BST_TYPE)(root->left, data);
    if (!tmp)
      root->left = tmp;
    return tmp;
  }
  
  else if (BST_COMPARE(data, root->data) > 0) {
    bst_node(BST_TYPE)* tmp = bst_delete(BST_TYPE)(root->right, data);
    if (!tmp)
      root->right = tmp;
    return tmp;
  }
  
  else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }
    
    else if (root->left == NULL) {
      bst_node(BST_TYPE)* tmp = root->right;
      free(root);
      return tmp;
    }
    
    else if (root->right == NULL) {
      bst_node(BST_TYPE)* tmp = root->left;
      free(root);
      return tmp;
    }
    
    else {
      int preddepth = 0;
      int succdepth = 0;
      bst_node(BST_TYPE)* pred = bst_predecessor(BST_TYPE)(root->left, &preddepth);
      bst_node(BST_TYPE)* succ = bst_successor(BST_TYPE)(root->right, &succdepth);
      if (leftdepth < rightdepth) {
	root->data = pred->data;
	bst_delete(BST_TYPE)(pred, pred->data);
      }
      else {
	root->data = succ->data;
	bst_delete(BST_TYPE)(succ, succ->data);
      }
    }
  }
}


void bst_free(BST_TYPE)(bst_node(BST_TYPE)* root) {
  if (root == NULL)
    return;
  if (root->left != NULL)
    bst_free(root->left);
  if (root->right != NULL)
    bst_free(root->right);
  free(root);
}
#endif
#endif
