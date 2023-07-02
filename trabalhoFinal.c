#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
    int codigo;
    char descricao[100];
    int quantidade;
    float valor;
    struct produto* prox;
} Produto;

//função para inicializar a lista vazia

Produto* inicializar(void) {
    return NULL;
}

//função para cadastrar os produtos

Produto* cadastrar(Produto* lista) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &novoProduto->codigo);

    printf("Digite a descricao do produto: ");
    scanf(" %[^\n]s", novoProduto->descricao);

    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Digite o valor do produto: R$ ");
    scanf("%f", &novoProduto->valor);

    novoProduto->prox = lista;
    return novoProduto;
}

//função para imprimir a lista do estoque

void imprimirEstoque(Produto* lista) {
    printf("\n-----RELATORIO DE ESTOQUE-----\n\n");

    Produto* atual = lista;
    int i = 1;

    while (atual != NULL) {
        printf("PRODUTO %d\n\n", i);
        printf("* Codigo --> %d\n", atual->codigo);
        printf("* Descricao --> %s\n", atual->descricao);
        printf("* Quantidade --> %d\n", atual->quantidade);
        printf("* Valor --> R$ %.2f\n\n", atual->valor);

        atual = atual->prox;
        i++;
    }
}

//função para pesquisar um produto pelo código

Produto* pesquisarProduto(Produto* lista, int codigo) {
    Produto* atual = lista;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->prox;
    }

    return NULL; //caso o produto não seja encontrado
}

//função para remover um produto pelo código

Produto* removerProduto(Produto* lista, int codigo) {
    Produto* atual = lista;
    Produto* anterior = NULL;

    while (atual != NULL) {
        if (atual->codigo == codigo) {
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("\nProduto removido com sucesso!\n");
            return lista;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("\nProduto nao encontrado.\n");
    return lista;
}

//função adicional para a liberação da lista 

void liberarLista(Produto* lista) {
    Produto* atual = lista;

    while (atual != NULL) {
        Produto* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main() {
    Produto* lista = inicializar();

    int opcao;
    int codigo;

    do {
        printf("\n\n*******CONTROLE DE ESTOQUE********\n\n");
        printf("[1] Adicionar um novo produto ao estoque\n");
        printf("[2] Mostrar todos os produtos na lista de estoque\n");
        printf("[3] Buscar produto pelo codigo\n");
        printf("[4] Remover produto pelo codigo\n");
        printf("[5] Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
            lista = cadastrar(lista);
            break;

            case 2:
            imprimirEstoque(lista);
            break;

            case 3:
            printf("\nDigite o codigo do produto: ");
            scanf("%d", &codigo);
            {
                Produto* produtoEncontrado = pesquisarProduto(lista, codigo);
                if (produtoEncontrado != NULL) {
                    printf("\n\n***Produto encontrado***\n\n");
                    printf("Codigo: %d\n", produtoEncontrado->codigo);
                    printf("Descricao: %s\n", produtoEncontrado->descricao);
                    printf("Quantidade: %d\n", produtoEncontrado->quantidade);
                    printf("Valor: R$ %.2f\n", produtoEncontrado->valor);
                } else {
                    printf("\nProduto nao encontrado.\n");
                }
            }
            break;

            case 4:
            printf("\nDigite o codigo do produto: ");
            scanf("%d", &codigo);
            lista = removerProduto(lista, codigo);
            break;
        }
    } while (opcao != 5);

    liberarLista(lista);

    return 0;
}
