#include<stdlib.h>
#include<stdio.h>
#include "splay_tree_imp.h"

#define DEBUG 1
//unsigned long long int rotations;
struct node{
  int key_;
  int value_;
  struct node *left_;
  struct node *right_;
  struct node *parent_;
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
    //rotations = 0;
    splay_tree_t* tree = malloc(sizeof(splay_tree_t));
    tree->root = NULL;
    return (void*)tree;
}

static node_t* makeNewNode(int key, int value) {
  node_t *root = malloc(sizeof(node_t));
  root->key_ = key;
  root->value_ = value;
  root->parent_ = NULL;
  root->right_ = NULL;
  root->left_ = NULL;
  return root;
}

static void rotateRight(splay_tree_t* tree, node_t* node){
    //rotations++;
    node_t* leftChild = node->left_;
    node->left_ = leftChild->right_;
    if(leftChild->right_ != NULL){
        leftChild->right_->parent_ = node;
    }
        
    leftChild->parent_ = node->parent_;
    if(node->parent_ == NULL){
        tree->root = leftChild;
    }else if(node == node->parent_->right_){
        node->parent_->right_ = leftChild;
    }else{
        node->parent_->left_ = leftChild;
    }
    leftChild->right_ = node;
    node->parent_ = leftChild;    
}

static void rotateLeft(splay_tree_t* tree, node_t* node){
    //rotations++;
    node_t* rightChild = node->right_;
    node->right_ = rightChild->left_;
    if(rightChild->left_ != NULL){
        rightChild->left_->parent_ = node;
    }
        
    rightChild->parent_ = node->parent_;
    if(node->parent_ == NULL){
        tree->root = rightChild;
    }else if(node == node->parent_->left_){
        node->parent_->left_ = rightChild;
    }else{
        node->parent_->right_ = rightChild;
    }
    rightChild->left_ = node;
    node->parent_ = rightChild;
}

static void splayTheTree(splay_tree_t* tree, node_t* new_node){
    //splay_tree_t* tree = (splay_tree_t*)dictionary;
    while(new_node->parent_ != NULL){
        if(new_node->parent_ == tree->root){
            if(new_node == tree->root->left_){
                rotateRight(tree, new_node->parent_);
            }else{
                rotateLeft(tree, new_node->parent_);
            }
        }else{
            node_t* parent = new_node->parent_;
            node_t* g_parent = parent->parent_;

            if(new_node->parent_->left_ == new_node && parent->parent_->left_ == parent){
                rotateRight(tree, g_parent);
                rotateRight(tree, parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->right_ == parent){
                rotateLeft(tree, g_parent);
                rotateLeft(tree, parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->left_ == parent){
                rotateLeft(tree, parent);
                rotateRight(tree, g_parent);
            }else if(new_node->parent_->left_ == new_node && parent->parent_->right_ == parent){
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

    while(current != NULL && current->key_ != key){
        previous = current;
        if(key < current->key_){
            current = current->left_;
        }else{
            current = current->right_;
        }
    }
    node_t* new_node = makeNewNode(key,value);
    new_node->parent_ = previous;
    if(previous == NULL){
        tree->root = new_node;
    }else if(current != NULL && current->key_ == key){
        current->value_ = value;
        splayTheTree(tree, current);
        return;    
    }else if(new_node->key_ < previous->key_){
        previous->left_ = new_node;
    }else{
        previous->right_ = new_node;
    }
    splayTheTree(tree, new_node);
}

int find(void* dictionary, int key){
    splay_tree_t* tree = dictionary;
    node_t* current = tree->root;
    node_t* previous = NULL;
    while(current != NULL && current->key_ != key){
        previous = current;
        if(key < current->key_){
            current = current-> left_;
        }else{
            current = current->right_;
        }

    }
    int val = -1;
    if(current == NULL){
        val = -1;
        //splayTheTree(tree, previous);
    }else if(current->key_ == key){
        val = current->value_;
        splayTheTree(tree, current);
    }else{
        val = -1;
        //splayTheTree(tree, previous);
    }
    return val;
}
