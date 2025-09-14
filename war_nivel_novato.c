#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Cada território terá: nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {
    // Vetor para armazenar até 5 territórios
    Territorio territorios[5];

    printf("==========================================\n\n");
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo!\n\n");

    // Loop para entrada de dados
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        // Leitura do nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remove o '\n' deixado pelo fgets
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Leitura da cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Leitura da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        // Limpa o buffer do teclado para evitar problemas no próximo fgets
        getchar();
        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n===== Territorios cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------------\n");
    }

    return 0;
}
    
