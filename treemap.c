#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    //new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (tree == NULL || tree->root == NULL) return;
  if (searchTreeMap(tree, key) != NULL) return; 
  TreeNode * parent = NULL;
  TreeNode * current = tree->root;
  while (current != NULL) {
    parent = current;
    if (tree->lower_than(key, current->pair->key)) {
      current = current->left;
    } else if (tree->lower_than(current->pair->key, key)) {
      current = current->right;
    } else {
      
      return; 
    }
  }
  TreeNode * nodo = createTreeNode(key, value);
  nodo->parent = parent;
  if (parent == NULL) tree->root = nodo; 
  else {
    if (tree->lower_than(key, parent->pair->key)) parent->left = nodo;
    else parent->right = nodo;
    
  }
  tree->current = nodo;
}

TreeNode * minimum(TreeNode * x){

    TreeNode * current = x;
    while (current->left != NULL) {
      current = current->left;
    }

    return current;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if (tree == NULL || tree->root == NULL) return;
  if (node == NULL || node->pair == NULL) return;
  if (searchTreeMap(tree, node->pair->key) == NULL) return;
  TreeNode * parent = node->parent;
  TreeNode * left = node->left;
  TreeNode * right = node->right;
  if (left == NULL && right == NULL) { // SIN HIJOS
    if (parent == NULL) tree->root = NULL;
    else {
      if (parent->left == node) parent->left = NULL;
      else parent->right = NULL;
    }
    
  }
  else if (left == NULL) { //1 HIJO DERECHO
    if (parent == NULL) tree->root = right;
    else {
      if (parent->left == node) parent->left = right; 
      else parent->right = right;
      right->parent = parent;
    }
    
  }
  else if (right == NULL) { //1 HIJO IZQUIERDO
     if (parent == NULL) tree->root = left;
      else {
        if (parent->right == node) parent->right = left; 
        else parent->left = left;
        left->parent = parent;
      }
  }
  else { //2 HIJOS
    TreeNode * min = minimum(node->right);
    node->pair->key = min->pair->key;
    node->pair->value = min->pair->value;
    removeNode(tree, min);
    
  }
  
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = tree->root;
    while (current != NULL) {
      if (tree->lower_than(key, current->pair->key)) {
        current = current->left;
      } else if (tree->lower_than(current->pair->key, key)) {
        current = current->right;
      } else {

        tree->current = current;
        return current->pair;
      }
    }
  return NULL; 
}



Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if (tree == NULL || tree->root == NULL) return NULL; 
  
  TreeNode * current = tree->root;
  while (current->left != NULL) {
    current = current->left;
  }
  
  return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    
  return NULL;
}
