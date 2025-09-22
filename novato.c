#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 50
#define MAX_TERRITORIOS 5  // Limite máximo de territórios

// ------- Definicao da Estrutura (Struct) -------
typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int tropas;
} Territorio;

// ------- Funcoes -------

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorio(Territorio *territorios, int *total) {
    if (*total >= MAX_TERRITORIOS) {
        printf("Maximo de territorios (%d) atingido!\n", MAX_TERRITORIOS);
        return;
    }

    printf("------- Cadastro do Novo Territorio -------\n\n");
    printf("Digite o nome do Territorio: ");
    fgets(territorios[*total].nome, TAM_STRING, stdin);
    territorios[*total].nome[strcspn(territorios[*total].nome, "\n")] = '\0';

    printf("Digite a cor do Dominio: ");
    fgets(territorios[*total].cor, TAM_STRING, stdin);
    territorios[*total].cor[strcspn(territorios[*total].cor, "\n")] = '\0';

    printf("Digite a quantidade de Tropas: ");
    scanf("%d", &territorios[*total].tropas);
    limparBufferEntrada();

    (*total)++;
    printf("\nTerritorio cadastrado com sucesso!\n");
}

void listarTerritorios(Territorio *territorios, int total) {
    printf("------- Lista de Territorios -------\n");
    if (total == 0) {
        printf("Nenhum territorio cadastrado.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("%d) Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("============================\n");
}

void atacar(Territorio *territorios, int total) {
    if (total < 2) {
        printf("É necessário pelo menos 2 territorios para atacar.\n");
        return;
    }

    int atk, def;
    listarTerritorios(territorios, total);

    printf("Escolha o territorio atacante (numero): ");
    scanf("%d", &atk);
    printf("Escolha o territorio defensor (numero): ");
    scanf("%d", &def);
    limparBufferEntrada();

    atk--; def--; // ajustar índice

    if (atk < 0 || atk >= total || def < 0 || def >= total) {
        printf("Territorio invalido.\n");
        return;
    }

    if (strcmp(territorios[atk].cor, territorios[def].cor) == 0) {
        printf("Não é possivel atacar um territorio da mesma cor!\n");
        return;
    }

    int dadoAtk = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("%s ataca %s!\n", territorios[atk].nome, territorios[def].nome);
    printf("Dado Atacante: %d | Dado Defensor: %d\n", dadoAtk, dadoDef);

    if (dadoAtk > dadoDef) {
        territorios[def].tropas -= dadoAtk;
        if (territorios[def].tropas <= 0) {
            territorios[def].tropas = territorios[atk].tropas / 2;
            strcpy(territorios[def].cor, territorios[atk].cor);
            printf("Territorio %s conquistado!\n", territorios[def].nome);
        } else {
            printf("Defensor perdeu %d tropas, agora tem %d.\n", dadoAtk, territorios[def].tropas);
        }
    } else {
        territorios[atk].tropas -= 1;
        printf("Ataque falhou! Atacante perdeu 1 tropa, agora tem %d.\n", territorios[atk].tropas);
    }
}

void liberarMemoria(Territorio *territorios) {
    free(territorios);
}

void mostrarMenu() {
    printf("============================\n");
    printf("        GAME - WAR \n");
    printf("============================\n");
    printf("1 - Cadastrar novo territorio\n");
    printf("2 - Listar todos os territorios\n");
    printf("3 - Atacar territorio\n");
    printf("0 - Sair\n");
    printf("============================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int totalterritorios = 0;
    int opcao;

    Territorio *territorios = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (!territorios) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    srand(time(NULL)); // inicializa gerador de números aleatórios

    do {
        mostrarMenu();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch(opcao) {
            case 1:
                cadastrarTerritorio(territorios, &totalterritorios);
                break;
            case 2:
                listarTerritorios(territorios, totalterritorios);
                break;
            case 3:
                atacar(territorios, totalterritorios);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }

        printf("Pressione Enter para continuar...");
        getchar();

    } while(opcao != 0);

    liberarMemoria(territorios);
    return 0;
}
