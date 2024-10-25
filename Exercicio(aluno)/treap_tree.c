#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
    int data;
    int heap;
    struct  Node* right;
    struct Node* left;
} Node;

// Function to create a new node with a random heap priority
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failure.\n");
        exit(-1);
    }
    new_node->data = data;
    new_node->heap = rand() % 100;  // Generate a random priority between 0 and 99
    new_node->right = NULL;
    new_node->left = NULL;
    return new_node;
}

// Rotations
Node* rotate_right(Node* node) {
    Node* left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;
    return left_child;
}
Node* rotate_left(Node* node) {
    Node* right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;
    return right_child;
}

// Insertion function
Node* insert_node(Node* node, int data) {
    if (node == NULL) {
        return create_node(data);
    }

    if (data == node->data) {
        printf("Value already inserted, cannot duplicate.\n");
        return node;
    }

    if (data < node->data) {
        node->left = insert_node(node->left, data);
        if (node->left && node->left->heap > node->heap) {
            node = rotate_right(node);
        }
    } else {
        node->right = insert_node(node->right, data);
        if (node->right && node->right->heap > node->heap) {
            node = rotate_left(node);
        }
    }
    return node;
}

Node* delete_node(Node* node, int data) {
    if (node == NULL) {
        printf("Node not found!\n");
        return node;
    }

    // Find the node
    if (data < node->data) {
        node->left = delete_node(node->left, data);
    } else if (data > node->data) {
        node->right = delete_node(node->right, data);
    } else {
        // Node with two children
        if (node->left && node->right) {
            // Heap integrity verification
            if (node->left->heap > node->right->heap) {
                node = rotate_right(node);
                node->right = delete_node(node->right, data);
            } else {
                node = rotate_left(node);
                node->left = delete_node(node->left, data);
            }
        }
        // Node with one or no children
        else {
            Node* temp = (node->left) ? node->left : node->right;
            free(node);
            return temp;
        }
    }
    return node;
}

int search_tree(Node* node, int data) {
    if (node == NULL) return 0;
    if (node->data == data) return 1;
    if (data < node->data) return search_tree(node->left, data);
    return search_tree(node->right, data);
}

void print_tree(Node* root, int level) {
    if (root == NULL) return;
    print_tree(root->right, level + 1);
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d (h=%d)\n", root->data, root->heap);
    print_tree(root->left, level + 1);
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    srand(time(NULL));
    Node* root = NULL;
    int data;
    int input = -1;

    while (input != 0) {
        printf("------------------------------Treap Tree------------------------------\n");
        printf("Select your option:\n1-Insert Value\n2-Find Value\n3-Delete Value\n4-Display Tree\n5-Insert Random Values\n0-Exit\n ");
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
                root = delete_node(root, data);
                break;
            case 4:
                printf("--------------------------------------------------------------------------------------------------\n");
                print_tree(root, 0);
                printf("--------------------------------------------------------------------------------------------------\n");
                break;
            case 5:
                printf("Inserting random values...\n");
                for (int i = 0; i < 10; i++){
                    data = rand() % (100 + 1);
                    root = insert_node(root, data);
                }
                printf("Done!\n");
                break;
            default:
                if (input != 0) {
                    printf("Invalid option!\n");
                }
                break;
        }
    }

    
    free_tree(root);

    printf("Closing application!\n");
    return 0;
}
