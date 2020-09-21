#include<stdlib.h>
#include<stdio.h>
#include "splay_tree_imp.h"

#define DEBUG 1

struct node{
  int key;
  int value;
  struct node *left;
  struct node *right;
  struct node *parent;
};
typedef struct node node_t;

struct splay_tree{
    node_t* root;
};
typedef struct splay_tree splay_tree_t;
static node_t* makeNewNode(int key, int value);
static void splayTheTree(splay_tree_t* tree, node_t* new_node);
static void rotateLeft(splay_tree_t* tree, node_t* node);
static void rotateRight(splay_tree_t* tree, node_t* node);

void* make_new_dictionary(){
    splay_tree_t* tree = malloc(sizeof(splay_tree_t));
    tree->root = NULL;
    return (void*)tree;
}

static node_t* makeNewNode(int key, int value) {
  node_t *root = malloc(sizeof(node_t));
  root->key = key;
  root->value = value;
  root->parent = NULL;
  root->right = NULL;
  root->left = NULL;
  return root;
}

static void rotateRight(splay_tree_t* tree, node_t* node){
    node_t* leftChild = node->left;
    node->left = leftChild->right;
    if(leftChild->right != NULL){
        leftChild->right->parent = node;
    }
        
    leftChild->parent = node->parent;
    if(node->parent == NULL){
        tree->root = leftChild;
    }else if(node == node->parent->right){
        node->parent->right = leftChild;
    }else{
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;    
}

static void rotateLeft(splay_tree_t* tree, node_t* node){
    node_t* rightChild = node->right;
    node->right = rightChild->left;
    if(rightChild->left != NULL){
        rightChild->left->parent = node;
    }
        
    rightChild->parent = node->parent;
    if(node->parent == NULL){
        tree->root = rightChild;
    }else if(node == node->parent->left){
        node->parent->left = rightChild;
    }else{
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

static void splayTheTree(splay_tree_t* tree, node_t* new_node){
    //splay_tree_t* tree = (splay_tree_t*)dictionary;
    while(new_node->parent != NULL){
        if(new_node->parent == tree->root){
            if(new_node == tree->root->left){
                rotateRight(tree, new_node->parent);
            }else{
                rotateLeft(tree, new_node->parent);
            }
        }else{
            node_t* parent = new_node->parent;
            node_t* g_parent = parent->parent;

            if(new_node->parent->left == new_node && parent->parent->left == parent){
                rotateRight(tree, g_parent);
                rotateRight(tree, parent);
            }else if(new_node->parent->right == new_node && parent->parent->right == parent){
                rotateLeft(tree, g_parent);
                rotateLeft(tree, parent);
            }else if(new_node->parent->right == new_node && parent->parent->left == parent){
                rotateLeft(tree, parent);
                rotateRight(tree, g_parent);
            }else if(new_node->parent->left == new_node && parent->parent->right == parent){
                rotateRight(tree, parent);
                rotateLeft(tree, g_parent);
            } 
        }
    }
}
void insert(void* dictionary, int key, int value){
    splay_tree_t* tree = (splay_tree_t*)dictionary;
    node_t* current = tree->root;
    node_t* previous = NULL;

    while(current != NULL){
        previous = current;
        if(key < current->key){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    node_t* new_node = makeNewNode(key,value);
    new_node->parent = previous;
    if(previous == NULL){
        tree->root = new_node;
    }else if(new_node->key < previous->key){
        previous->left = new_node;
    }else{
        previous->right = new_node;
    }
    splayTheTree(tree, new_node);
}

int find(void* dictionary, int key){
    splay_tree_t* tree = dictionary;
    node_t* current = tree->root;
    node_t* previous = NULL;
    while(current != NULL && current->key != key){
        previous = current;
        if(key < current->key){
            current = current-> left;
        }else{
            current = current->right;
        }

    }
    int val = -1;
    if(current == NULL){
        val = -1;
        //splayTheTree(tree, previous);
    }else if(current->key == key){
        val = current->value;
        splayTheTree(tree, current);
    }else{
        val = -1;
        //splayTheTree(tree, previous);
    }
    return val;
}
/*
struct node{
    int key;
    int value;
    struct node* left;
    struct node* right;
    struct node* parent;
};
typedef struct node node_t;

struct splayTree{
    node_t* root;
};
typedef struct splayTree splayTree_t;

static node_t* makeNewNode(int , int, node_t* );
static node_t* rotateRight(node_t* );
static node_t* rotateLeft(node_t* );
static node_t* splayTheNode(node_t* , int );

void* make_new_dictionary(){
    splayTree_t* tree = malloc(sizeof(splayTree_t));
    tree->root = NULL;
    return tree;
}

static node_t* makeNewNode(int key, int value, node_t* parent){
    node_t* root = (node_t*)malloc(sizeof(node_t));
    root->key = key;
    root->value = value;
    root->left = NULL;
    root->right = NULL;
    root->parent = parent;
    return root;
}

static node_t* rotateRight(node_t* node){
    node_t* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

static node_t* rotateLeft(node_t* node){
    node_t* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    return rightChild;
}

static node_t* splayTheNode(node_t* node, int key){
    if(node == NULL || node->key == key){
        return node;
    }
    if(key < node->key){
        if(DEBUG){
            printf("Splaying left sub tree\n");
        }
        if(node->left == NULL){
            return node;
        }
        if(key < node->left->key){
            node->left->left = splayTheNode(node->left->left, key);
            node = rotateRight(node);
        }else if(key > node->left->key){
            node->left->right = splayTheNode(node->left->right,key);
            if(node->left->right != NULL){
                node->left = rotateLeft(node->left);
            }
        }
        if(node->left == NULL)
            return node;
        return rotateRight(node);
    }else{
        if(DEBUG){
            printf("Splaying right sub tree\n");
        }
        if(node->right == NULL){
            return node;
        }
        if(key < node->right->key){
            node->right->left = splayTheNode(node->right->left, key);
            if(node->right->left != NULL){
                node->right = rotateRight(node->right);
            }
        }else if(key > node->right->key){
            node->right->right = splayTheNode(node->right->right,key);
            node = rotateLeft(node);
        }
        if(node->right == NULL)
            return node;
        return rotateLeft(node);
    }
    return NULL;
}

void insert(void* dictionary, int key, int value){
    if(DEBUG){
        printf("Inserting key = %d, value = %d\n",key,value);
    }
    splayTree_t* splay_tree = NULL;
    splay_tree = (splayTree_t*)dictionary;
    node_t* current = (node_t*)splay_tree->root;
    if(current == NULL){
        current = makeNewNode(key,value);
        return;
    }
    current = splayTheNode(current,key);
    if(DEBUG){
        //printf("temp key,lkey,rkey = %d %d %d\n",temp->key, temp->left->key, temp->right->key);
        printf("current key,lkey,rkey = %d %d %d\n",current->key, current->left->key, current->right->key);
    }
    if(current->key == key){
        current->value = value;
        return;
    }
    node_t* new_node = makeNewNode(key,value);
    if(key < current->key){
        new_node->right = current;
        new_node->left = current->left;
        current->left = NULL;
    }else{
        new_node->left = current;
        new_node->right = current->right;
        current->right = NULL;
    }
    splay_tree->root = new_node;  
    if(DEBUG){
        printf("[INSERT]key of root node %d, value inserted %d\n",splay_tree->root->key,splay_tree->root->value);
    }  
}

int find(void* dictionary, int key){
    splayTree_t* splay_tree = NULL;
    splay_tree = (splayTree_t*)dictionary;
    node_t* current = (node_t*)splay_tree->root;
    if(DEBUG){
        printf("[FIND]Current key,value at tree root = %d,%d\n",current->key, current->value);
    }
    node_t* result = splayTheNode(current, key);
    if(DEBUG){
        printf("[FIND] address of result %p\n",(void*)result);
    }
    if(result != NULL && result->key == key){
        return result->value;
    }
    return -1;
}
/*
void insert(void* dictionary, int key, int value){
    splayTree_t* splay_tree = (splayTree_t*)dictionary;
    node_t* current = splay_tree->root;
    node_t* parent = NULL;
    node_t* gparent = NULL;
    //node_t* new_node = makeNewNode(key,value);
    while(current != NULL && current->key != key){
        gparent = parent;
        parent = current;
        if(key < current->key){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    if(current == NULL){
        current = makeNewNode(key,value);
        if(parent == NULL && gparent == NULL){
            return;
        }
    }else if(current != NULL && current.key == key){
        current->value = value;
    }
}
*/
