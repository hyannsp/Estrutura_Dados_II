// Hyann Silva Piffer - Binary Tree
// gcc -o "compiled name" binary_tree.c
#include <stdio.h>
#include <stdlib.h>

// Node struct
typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// Print Tree inOrder
void printInOrder(Node *node)
{
    if (node != NULL)
    {
        printInOrder(node->left);
        printf("%d ", node->value);
        printInOrder(node->right);
    }
}

void printPosOrder(Node *node)
{
    if (node != NULL)
    {
        printPosOrder(node->left);
        printPosOrder(node->right);
        printf("%d ", node->value);
    }
}

void printPreOrder(Node *node)
{
    if (node != NULL)
    {
        printPreOrder(node->left);
        printf("%d ", node->value);
        printPreOrder(node->right);
    }
}

// Find element in tree
void findNode(Node *node, int value)
{
    if (node == NULL)
    {
        printf("Value %i not found\n", value);
        return;
    }
    if (node->value == value)
    {
        printf("Value %i found\n", value);
        return;
    }
    else if (node->value < value)
    {
        findNode(node->right, value);
    }
    else
    {
        findNode(node->left, value);
    }
}

Node *createNode(int value)
{
    // Create Node
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("Error: Memory allocation failure.\n");
        exit(-1);
    }
    new_node->right = NULL;
    new_node->left = NULL;
    new_node->value = value;
    return new_node;
}

void insertNode(Node **node, int value)
{
    // If root is NULL, the new node is now a root
    if (*node == NULL)
    {
        *node = createNode(value);
    }
    // If the value inserted is the same of the any node
    else if ((*node)->value == value)
    {
        printf("Value inserted already, can't create duplicate data.\n");
    }
    // Now, using recursivity to create nodes in NULL childrens (or leafs)
    else if ((*node)->value < value)
    {
        insertNode(&(*node)->right, value);
    }
    else
    {
        insertNode(&(*node)->left, value);
    }
}

// Function to find min node
Node *findMin(Node *node)
{
    while (node && node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

Node *deleteNode(Node *node, int value)
{
    if (node == NULL)
    {
        return node;
    }
    // Recursion to find the value
    if (node->value > value)
    {
        node->left = deleteNode(node->left, value);
    }
    else if (node->value < value)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        // Node with 1 or no childrens
        if (node->left == NULL)
        {
            Node *right = node->right;
            free(node);
            return right;
        }
        else if (node->right == NULL)
        {
            Node *left = node->left;
            free(node);
            return left;
        }

        // 2 childrens node
        Node *min = findMin(node->right); // Find the min node at right and make-it the new children
        node->value = min->value;
        node->right = deleteNode(node->right, min->value);
    }
    return node;
}

// void inOrderNoRecursive(Node *node) {
//   Node *node_stack[100];
//   int top = -1;
//   Node *current = node;
//   while (node != NULL || top != -1) {
//     while (node != NULL) {
//       node_stack[++top] = node;
//       node = node->left;
//     }
//     node = node_stack[top--];
//    printf(" %d", node->value);
//     node = node->right;
//   }
// }

// Liberate space
void freeTree(Node *node)
{
    if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------Main---------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
    // Creating a Tree with some numbers
    int input = -1, value;
    int values[] = {50, 30, 70, 20, 40};
    int size = sizeof(values) / sizeof(values[0]);
    Node *root = NULL;
    for (int i = 0; i < size; i++)
    {
        insertNode(&root, values[i]);
    }
    while (input != 0)
    {
        printf("Select an option:\n");
        printf("1-Insert Value\n2-Find Value\n3-Delete Value\n4-Print in Order\n5-Print Pos Order\n6-Print Pre Order\n0-Close\n");
        scanf("%d", &input);
        // Case switch to input
        switch (input)
        {
        case 1:
            printf("Insert a value: ");
            scanf("%d", &value);
            insertNode(&root, value);
            break;
        case 2:
            printf("Insert a value: ");
            scanf("%d", &value);
            findNode(root, value);
            break;
        case 3:
            printf("Insert a value: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;
        case 4:
            printInOrder(root);
            printf("\n");
            break;
        case 5:
            printPosOrder(root);
            printf("\n");
            break;
        case 6:
            printPreOrder(root);
            printf("\n");
            break;
        default:
            if (input != 0)
            {
                printf("Invalid option\n");
            }
            break;
        }
    }
    printf("Closing app!\n");
    // Free memory
    freeTree(root);
}
