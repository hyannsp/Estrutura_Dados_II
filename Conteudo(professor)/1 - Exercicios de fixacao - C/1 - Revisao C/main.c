#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PADRAO 10

// Criando a estrutura do tipo Aluno
typedef struct {
    int matricula;
    char nome[100];
    char endereco[200];
    char data_nasc[10];
} Aluno;

// Protótipos das funções
void pesquisaAluno(Aluno *alunos[], int tamanho);
void imprimirVetor(Aluno *alunos[], int tamanho);
void ordenarTurma(Aluno *alunos[], int tamanho);
void excluirAluno(Aluno *alunos[], int *tamanho);
void insereAluno(Aluno *alunos[], int *tamanho, int *matricula);

int main() {
    int tamanho = TAM_PADRAO;
    Aluno *alunos[tamanho];
    int matricula = 1;
    // Alocando memória para cada aluno e inicializando os valores
    for (int i = 0; i < tamanho; i++) {
        alunos[i] = (Aluno *)malloc(sizeof(Aluno));
        alunos[i]->matricula = matricula;
        matricula++;
        sprintf(alunos[i]->nome, "Exemplo %d", i + 1);
        strcpy(alunos[i]->endereco, "Padrao");
        strcpy(alunos[i]->data_nasc, "Padrao");
    }

    // Chamando as funções
    int opcao = -1;
    while(opcao!=0){
        printf("\nMenu do Sistema\n1 - Buscar por matricula\n2 - Ordenar por nome\n3 - Excluir aluno\n4 - Imprimir lista de alunos\n5  -Inserir novo aluno\n0 - Sair\nDigite a opcao desejada:");
        scanf("%d",&opcao);
        switch(opcao){
        case 1: pesquisaAluno(alunos,tamanho); break;
        case 2: ordenarTurma(alunos,tamanho); break;
        case 3: excluirAluno(alunos,&tamanho); break;
        case 4: imprimirVetor(alunos,tamanho); break;
        case 5: insereAluno(alunos,&tamanho,&matricula); break;
        case 0:  // Liberando a memória alocada
        for (int i = 0; i < tamanho; i++) {
        free(alunos[i]);
        }printf("Sistema finalizado com sucesso!\n"); 
        break;
        default: printf("Opção invalida! Tente novamente.\n"); break;
    }
    }
    return 0;
}

void imprimirVetor(Aluno *alunos[], int tamanho) {
    for (int j = 0; j < tamanho; j++) {
        printf("%i - %s\n", alunos[j]->matricula, alunos[j]->nome);
    }
}

void pesquisaAluno(Aluno *alunos[], int tamanho) {
    int matr, ind = -1;
    printf("Digite a matricula: ");
    scanf("%d", &matr);
    for (int j = 0; j < tamanho; j++) {
        if (alunos[j]->matricula == matr) {
            ind = j;
            break;
        }
    }
    if (ind >= 0) {
        printf("O aluno %s, matricula %d foi encontrado!\n\n", alunos[ind]->nome, alunos[ind]->matricula);
    } else {
        printf("Aluno nao encontrado!\n\n");
    }
}

void ordenarTurma(Aluno *alunos[], int tamanho) {
    Aluno *temp;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (strcmp(alunos[j]->nome, alunos[j + 1]->nome) > 0) {
                // Troca as strings de posição
                temp = alunos[j];
                alunos[j] = alunos[j+1];
                alunos[j+1] = temp;
            }
        }
    }
    printf("\nVetor ordenado:\n");
    imprimirVetor(alunos, tamanho);
}

void excluirAluno(Aluno *alunos[], int *tamanho) {
    int matr, ind = -1;
    printf("Digite a matricula do aluno a ser excluido: ");
    scanf("%d", &matr);
    for (int j = 0; j < *tamanho; j++) {
        if (alunos[j]->matricula == matr) {
            ind = j;
            break;
        }
    }
    if (ind >= 0) {
        for (int j = ind; j < *tamanho - 1; j++) {
            alunos[j] = alunos[j + 1];
        }
        (*tamanho)--;
        printf("Aluno com matricula %d excluido.\n\n", matr);
    } else {
        printf("Aluno nao encontrado!\n\n");
    }
}

void insereAluno(Aluno *alunos[], int *tamanho, int *matricula) {
    
    if (*tamanho >= TAM_PADRAO) {
        printf("Nao e possivel adicionar mais alunos, limite maximo atingido.\n");
        return;
    }  
    if(*tamanho < TAM_PADRAO){ // Ou um else... está if para melhor compreensão
    *alunos = realloc(*alunos, (*tamanho + 1) * sizeof(Aluno *));
    Aluno *novoaluno = (Aluno *)malloc(sizeof(Aluno));
    novoaluno->matricula = *matricula;
    printf("- Inserindo novo aluno -\nDigite o nome do novo aluno: ");
    scanf("%s", novoaluno->nome);
    printf("- Digite o endereco do novo aluno: ");
    scanf("%s", novoaluno->endereco);
    printf("- Digite a data de nascimento do novo aluno: ");
    scanf("%s", novoaluno->data_nasc);
    alunos[*tamanho] = novoaluno;
    (*tamanho)++;
    (*matricula)++;}
}
