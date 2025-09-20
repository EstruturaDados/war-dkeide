#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------- Constante Global -------
#define TAM_STRING 50
#define MAX_TERRITORIOS 50

// ------- Definicao da Estrutura (Struct) -------
struct war {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
};

// Limpando Buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// ------- Funcao Principal -------
int main() {
    struct war territorios[MAX_TERRITORIOS];
    int totalterritorios = 0;
    int opcao;

    // ------- Laco Principal do Menu -------
    do {
        // Exibe o menu de opcoes
        printf("============================\n");
        printf("        GAME - WAR \n");
        printf("============================\n");
        printf("1 - Cadastrar novo territorio\n");
        printf("2 - Listar todos os territorios\n");
        printf("0 - Sair\n");
        printf("============================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        limparBufferEntrada();

        // ------- Processamento da Opcao -------
        switch (opcao) {
            case 1: // Cadastro do Territorio
                printf("------- Cadastro do Novo territorio ------- \n\n");

                if (totalterritorios < MAX_TERRITORIOS) {
                    printf("Digite o nome do Territorio: ");
                    fgets(territorios[totalterritorios].nome, TAM_STRING, stdin);

                    printf("Digite a cor do Dominio: ");
                    fgets(territorios[totalterritorios].cor, TAM_STRING, stdin);

                    territorios[totalterritorios].nome[strcspn(territorios[totalterritorios].nome, "\n")] = '\0';
                    territorios[totalterritorios].cor[strcspn(territorios[totalterritorios].cor, "\n")] = '\0';

                    printf("Digite a quantidade de Tropas: ");
                    scanf("%d", &territorios[totalterritorios].tropas);
                    limparBufferEntrada();

                    totalterritorios++;

                    printf("\nTerritorio cadastrado com sucesso!\n");
                } else {
                    printf("Impossivel cadastrar mais um territorio!");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2:
                printf("------- Lista de Territorios -------\n");

                if (totalterritorios == 0) {
                    printf("Nenhum territorio cadastrado.\n");
                } else {
                    for (int i = 0; i < totalterritorios; i++) {
                        printf("%d) Nome: %s | Cor: %s | Tropas: %d\n",
                               i + 1,
                               territorios[i].nome,
                               territorios[i].cor,
                               territorios[i].tropas);
                    }
                    printf("============================\n");
                }

                printf("Pressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                break;
        }
    } while (opcao != 0);

    return 0;
}