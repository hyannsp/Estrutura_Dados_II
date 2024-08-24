#include <stdio.h>
#include <stdlib.h>

// Node struct
typedef struct Node{
    int valor;
    struct no* left;
    struct no* right;
}node;

// Print Tree inOrder
void printInOrder(Node* node){
    if(node != NULL){
        printf("%d", node->valor);
        printInOrder(node->left);
        printInOrder(node->right);
    }
}

// Find element in tree
void findNode(Node* node, int value){
    // Verify tree exist
    if(node!=NULL){
        // Verify tree value's (if greater, go to right, if lesser, go to left)
        if(node->value == value){
            print("value found in memory!/n");
            return;
        }
        else if(node->value > value){
            findNode(node->right, valor);
        }
        else(node->value < value){
            findNode(node->left, value);
        }
    }
    else{
        printf("Value not found! ");
    }
}

void insertNode(Node* node, int value){
    // Create Node
    Node* new_node = (Node*)malloc(sizeOf(Node));
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->value = value;

    if(node == NULL){
        node = new_node;
    }
    else if(node->value < value){
        insertNode(new_node->left, value);
    }
    else if(node->value > value){
        insertNode(new_node->right, value);
    }
}

void main (){
    
}
