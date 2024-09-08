#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  int height;
  struct Node *right;
  struct Node *left;
} Node;

// Cria um novo nó
Node *createNode(int data)
{
  Node *new_node = (Node *)malloc(sizeof(Node));
  if (!new_node)
  {
    printf("Erro ao criar no!");
    exit(EXIT_FAILURE);
  }
  new_node->data = data;
  new_node->height = 1;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// Retornar o valor da arvore
int height(Node *node)
{
  if (node == NULL)
  {
    return 0;
  }
  return node->height;
}

// Retornar o fator de balanceamento dos nos
int getBalance(Node *node)
{
  if (node == NULL)
  {
    return 0;
  }
  return height(node->left) - height(node->right);
}

// Uso para pegar a maior altura entre as subarvores direita e esquerda
int getMax(int a, int b) { return a > b ? a : b; }

Node *rightRotate(Node *node)
{
  Node *left_child = node->left; // Filho a esquerda
  Node *right_grandchild =
      left_child->right; // Filho a direita do filho a esquerda
  left_child->right = node;
  node->left = right_grandchild;

  // Atualizar as alturas
  node->height = 1 + getMax(height(node->left), height(node->right)); // Atualiza a altura do nó original
  left_child->height = 1 + getMax(height(left_child->left), height(left_child->right)); // Atualiza a altura do novo nó raiz (filho à esquerda)


  return left_child;
}

Node *leftRotate(Node *node)
{
  Node *right_child = node->right;
  Node *left_grandchild = right_child->left;

  right_child->left = node;
  node->right = left_grandchild;

  // Atualizar as alturas
  node->height = 1 + getMax(height(node->left), height(node->right)); // Atualiza a altura do nó original
  right_child->height = 1 + getMax(height(right_child->left), height(right_child->right)); // Atualiza a altura do novo nó raiz (filho à direita)

  return right_child;
}

void printTree(Node *root, int space)
{
  if (root == NULL)
  {
    return;
  }
  space += 10;

  printTree(root->right, space);

  printf("\n");
  for (int i = 10; i < space; i++)
  {
    printf(" ");
  }
  printf("%d\n", root->data);

  printTree(root->left, space);
}

Node *insertNode(Node *node, int data)
{
  // Inserir os dados como uma arvore binaria
  if (node == NULL)
  {
    return createNode(data);
  }
  if (data < node->data)
  {
    node->left = insertNode(node->left, data);
  }
  else if (data > node->data)
  {
    node->right = insertNode(node->right, data);
  }
  else
  {
    // Duplicado
    printf("Esse valor já foi inserido e não pode ser inserido novamente!\n");
    return node;
  }

  node->height = 1 + getMax(height(node->left), height(node->right));

  // Verificar o fator de balanceamento e aplicar rotações
  int balance = getBalance(node);
  printf("\nFator de balanceamento do %d igual a %d\n", node->data, balance);

  // Caso 1 - Rotação simples à direita
  if (balance > 1 && data < node->left->data)
  {
    printf("Feita rotação simples à direita\n");
    return rightRotate(node);
  }

  // Caso 2 - Rotação simples à esquerda
  if (balance < -1 && data > node->right->data)
  {
    printf("Feita rotacao simples a esquerda\n");
    return leftRotate(node);
  }

  // Caso 3 - Rotação dupla à esquerda
  if (balance > 1 && data > node->left->data)
  {
    printf("Feita rotacao dupla a esquerda\n");
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Caso 4 - Rotação dupla à direita
  if (balance < -1 && data < node->right->data)
  {
    printf("Feita rotacao dupla a direita\n");
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

//----------------------------------------------------------------------------------------------------
//---------------------------------------------MAIN---------------------------------------------------
//----------------------------------------------------------------------------------------------------

int main()
{
  Node *root = NULL;
  printf("\nInserindo a raiz: 50");
  root = insertNode(root, 50);
  printf("\nArvore");
  printTree(root, 0);

  int lista[20] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 60, 43, 16, 67, 34, 35};
  int i = 0;
  for (i = 0; i < 20; i++)
  {
    printf("------------------------------------------------------------------------------");
    printf("\nInserindo valor na AVL: %d", lista[i]);
    root = insertNode(root, lista[i]);
    printTree(root, 0);
  }

  return 0;
}