#include <stdio.h>
#include <stdlib.h>
#define red 1
#define black 0

// Root is always black
// A red node cannot have a left/right node the same color
// Every path of one node to leaf have the same count of black nodes

typedef struct Node
{
    int data; 
    int color;
    struct Node *right;
    struct Node *left;
} Node;

// Function to create a new node
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->color = red;  // Every new node starts as red
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to perform insertion in a binary tree
Node* bin_insert(Node *root, Node *new_node) {
    if (root == NULL) {
        return new_node;  // If tree is empty, the new node becomes the root
    }
    if (new_node->data < root->data) {
        root->left = bin_insert(root->left, new_node);
    } else if (new_node->data > root->data) {
        root->right = bin_insert(root->right, new_node);
    }

    return root;
}

// To verify if node color is red
int is_red(Node * node){
    return node == NULL ? black : node->color; // Node Null is black
}


Node *rotate_left(Node *root){
    Node *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    new_root->color = root->color;
    root->color = red;
    return new_root;
}

Node *rotate_right(Node *root){
    Node *new_root = root->left;

    // Swap Position
    root->left = new_root->right;
    new_root->right = root;

    // Swap colors
    new_root->color = root->color;
    root->color = red;
    return new_root;
}

// To fix red-black tree properties
Node *balance_tree(Node *root){
    // Case 1: Left Rotate -- 1 red node in left and no red node in right
    if (is_red(root->right) && !is_red(root->left)) {
        root = rotate_left(root);
    }

    // Case 2: Right Rotate -- 2 red nodes consecutives
    if (is_red(root->left) && is_red(root->left->left)) {
        root = rotate_right(root);
    }

    // Case 3: Recolor -- Both childrens red
    if (is_red(root->left) && is_red(root->right)) {
        root->color = red;
        root->left->color = black;
        root->right->color = black;
    }

    return root;
}

// Function to search for a value in the tree
int search_tree(Node *root, int data) {
    if (root == NULL) {
        return 0; // Not found
    }
    if (data < root->data) {
        return search_tree(root->left, data);
    } else if (data > root->data) {
        return search_tree(root->right, data);
    }
    return 1; // Found
}

Node *insert_node(Node *root, int data){
    // Create the new node
    Node *new_node = create_node(data);

    // Insert the new node into the binary search tree
    root = bin_insert(root, new_node);

    // red-black properties
    root = balance_tree(root);

    root->color = black;

    return root;
}

Node* find_minimum(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node *remove_node(Node *root, int data){
    if (root == NULL) {
        return NULL;
        printf("Node not Found: ", data);
    }
    if (data < root->data) {
        root->left = remove_node(root->left, data);
    } else if (data > root->data) {
        root->right = remove_node(root->right, data);
    } else { // Node Found
        // Case 1: No childrens
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: 1 children
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: 2 Childrens
        // Find the minimun node at right nad make-it the new root
        Node *temp = find_minimum(root->right);
        root->data = temp->data;  
        root->right = remove_node(root->right, temp->data);  
    }

    // Balance tree
    root = balance_tree(root);

    return root;
}

void print_tree(Node *root, int level) {
    if (root == NULL) return;

    print_tree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    printf("%d (%s)\n", root->data, root->color == red ? "Red" : "Black");

    print_tree(root->left, level + 1);
}

void free_tree(Node *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main (){
    Node *root = NULL;
    int input = -1;
    int data;
    while (input != 0) {
        printf("---------------------------Red Black Tree------------------------------\n");
        printf("Select your option:\n1-Insert Value\n2-Find Value\n3-Delete Value\n4-Display Tree\n0-Exit\n ");
        scanf("%d", &input);
        switch (input) {
            case 1:
                printf("Value to be inserted: ");
                scanf("%d", &data);
                root = insert_node(root, data);
                break;
            case 2:
                printf("Value to be searched: ");
                scanf("%d", &data);
                if (search_tree(root, data)) {
                    printf("Value %d found in the tree.\n", data);
                } else {
                    printf("Value %d not found.\n", data);
                }
                break;
            case 3:
                printf("Value to be deleted: ");
                scanf("%d", &data);
                root = remove_node(root, data);
                break;
            case 4:
                printf("--------------------------------------------------------------------------------------------------\n");
                print_tree(root, 0);
                printf("--------------------------------------------------------------------------------------------------\n");
                break;
            default:
                if (input != 0) {
                    printf("Invalid option!\n");
                }
                break;
        }
    }

    // Free the memory of the tree before exiting
    free_tree(root);

    printf("Closing application!\n");
    return 0;
}