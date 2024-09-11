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
  node->height = 1 + getMax(height(node->left), height(node->right));                   // Atualiza a altura do nó original
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
  node->height = 1 + getMax(height(node->left), height(node->right));                      // Atualiza a altura do nó original
  right_child->height = 1 + getMax(height(right_child->left), height(right_child->right)); // Atualiza a altura do novo nó raiz (filho à direita)

  return right_child;
}

// Imprimir a arvore na horizontal
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

Node *balance(Node *node)
{
  // Verificar o fator de balanceamento e aplicar rotações
  int balance = getBalance(node);
  printf("\nFator de balanceamento do %d igual a %d\n", node->data, balance);
  // Caso 1 - Rotação simples à direita
  if (balance > 1 && getBalance(node->left) >= 0)
  {
    printf("Feita rotacao simples a direita\n");
    return rightRotate(node);
  }

  // Caso 2 - Rotação simples a esquerda
  if (balance < -1 && getBalance(node->right) <= 0)
  {
    printf("Feita rotacao simples a esquerda\n");
    return leftRotate(node);
  }

  // Caso 3 - Rotação dupla a direita (Left-Right case)
  if (balance > 1 && getBalance(node->left) < 0)
  {
    printf("Feita rotacao dupla a direita\n");
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Caso 4 - Rotação dupla a esquerda (Right-Left case)
  if (balance < -1 && getBalance(node->right) > 0)
  {
    printf("Feita rotacao dupla a esquerda\n");
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

// Funcao para inserir na arvore avl
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
    printf("Esse valor ja foi inserido e nao pode ser inserido novamente!\n");
    return node;
  }

  // Atualizar altura do nó atual
  node->height = 1 + getMax(height(node->left), height(node->right));
  printf("Valor inserido, fazendo balanceamento...");
  return balance(node);
}

// Função para encontrar o maior nó
Node *findMax(Node *node)
{
  while (node && node->right != NULL)
  {
    node = node->right;
  }
  return node;
}

// Funcao para deletar um dado da arvore avl
Node *deleteNode(Node *node, int data)
{
  if (node == NULL)
  {
    printf("Valor para exclusao nao foi encontrado");
    return node;
  }
  // Primeiro, buscar a localização do nó
  if (node->data < data)
  {
    node->right = deleteNode(node->right, data);
  }
  else if (node->data > data)
  {
    node->left = deleteNode(node->left, data);
  }
  else
  {
    // Node com 0 ou 1 filho
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

    // Node com 2+ filhos
    Node *min = findMax(node->left); // Encontrar o maio node a esquerda e o alocar como novo filho
    node->data = min->data;
    node->left = deleteNode(node->left, min->data);
  }

  if (node == NULL)
    return node;

  // Atualizar a altura
  node->height = 1 + getMax(height(node->left), height(node->right));
  // printTree(node,0);

  // Balancear após remoção
  return balance(node);
}

// Encontrar um valor na arvore
void findData(Node *node, int data){
  if (node == NULL)
  {
    printf("Valor não foi encontrado\n");
    return;
  }
  if (node->data < data)
  {
    findData(node->right, data);
  }
  else if (node->data > data)
  {
    findData(node->left, data);
  }
  else{
    printf("Valor encontrado!! Seu valor: %d foi encontrado com sucesso!!\n", node->data);
  }
}

// Para limpar a memoria
void freeTree(Node *node){
  if (node != NULL)
    {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

//----------------------------------------------------------------------------------------------------
//---------------------------------------------MAIN---------------------------------------------------
//----------------------------------------------------------------------------------------------------

int main()
{
  int input = -1;
  int data = 0;
  Node *root = NULL;
  printf("Deseja inserir uma lista predefinida na arvore? (1 Para sim, qualquer outro valor para não)\n");
  scanf("%d",&input);
  if (input == 1){
    printf("\nInserindo a raiz: 50");
    root = insertNode(root, 50);
    printTree(root, 0);

    int lista[20] = {1, 64, 12, 18, 66, 38, 95, 58, 59, 70, 68, 39, 62, 7, 60, 43, 16, 67, 34, 35};
    int i = 0;
    for (i = 0; i < 20; i++)
    {
      printf("------------------------------------------------------------------------------");
      printf("\nInserindo valor na AVL: %d", lista[i]);
      root = insertNode(root, lista[i]);
    }
  }
  input = -1;
  while (input != 0){
    printf("---------------------------Arvore AVL--------------------------------------\n");
    printf("Selecione sua opcao:\n1-Inserir Valor\n2-Encontrar Valor\n3-Deletar Valor\n4-Visualizar Arvore\n0-Fechar\n ");
    scanf("%d",&input);
    switch (input)
    {
    case 1:
      printf("Valor a ser Inserido: ");
      scanf("%d",&data);
      root = insertNode(root, data);
      break;
    case 2:
      printf("Valor a ser Buscado: ");
      scanf("%d",&data);
      findData(root,data);
      break;
    case 3:
      printf("Valor a ser Deletado: ");
      scanf("%d",&data);
      root = deleteNode(root, data);
      break;
    case 4:
      printf("--------------------------------------------------------------------------------------------------\n");
      printTree(root, 0);
      printf("--------------------------------------------------------------------------------------------------\n");
      break;
    default:
      if (input != 0)
        {
          printf("Opcao invalida!\n");
        }
      break;
    }
  }
  printf("Fechando aplicativo!\n");
  // Liberar memoria
  freeTree(root);
  return 0;
}