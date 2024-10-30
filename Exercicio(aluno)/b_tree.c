#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int* keys;                  // Array of keys stored in the node
    int max_keys;               // Maximum number of keys allowed in the node
    struct Node** childrens;    // Array of pointers to the node's children
    int childrens_quantity;     // Current number of children the node has
    int leaf;                   // Flag to indicate if the node is a leaf (1 = yes, 0 = no)
} Node;

// Function to create a new node with the specified maximum keys and leaf status
Node* createNode(int max_keys, int leaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->max_keys = max_keys;
    node->leaf = leaf;

    // Allocate array memory for arrays with max quantity of keys allowed
    node->keys = (int*)malloc((max_keys - 1) * sizeof(int));
    node->childrens = (Node**)malloc(max_keys * sizeof(Node*));

    node->childrens_quantity = 0;
    return node;
}

// Insert Node
void insert(Node** root, int key, int max_keys) {
    Node* r = *root;

    // If the root is full, we need to split it
    if (r->childrens_quantity == max_keys - 1) {
        // Create a new root and define the old root as a child
        Node* newRoot = createNode(max_keys, 0);
        newRoot->childrens[0] = r;

        // need Split childs function here
        int i = 0;

        // Decide which child should receive the new key
        if (newRoot->keys[0] < key)
            i++;
        
        // needs a functio to Insert the key into the appropriate child here
        *root = newRoot;                           // Update root to point to the new root
    } else {
        // If root is not full, insert the key directly (use same function above)
    }
}

int main(void){
    return 0;
}