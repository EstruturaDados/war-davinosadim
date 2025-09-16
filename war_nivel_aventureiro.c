#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa cada território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios dinamicamente
void cadastrarTerritorios(Territorio *mapa, int quantidade) {
    printf("\n==========================================\n");
    printf("Cadastro de %d territorios\n", quantidade);
    printf("==========================================\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("--- Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar buffer do teclado
        printf("\n");
    }
}

// Exibe todos os territórios cadastrados
void exibirTerritorios(Territorio *mapa, int quantidade) {
        printf("\n===== Situacao Atual dos Territorios =====\n");
        for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do exercito: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("------------------------------------------\n");
    }
}

// Função que simula uma batalha até que um dos lados perca todas as tropas
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n O ataque nao pode ser contra um territorio da mesma cor!\n");
        return;
    }

    printf("\n==========================================\n");
    printf("Batalha entre %s (atacante) e %s (defensor)\n", atacante->nome, defensor->nome);
    printf("==========================================\n");

    while (atacante->tropas > 0 && defensor->tropas > 0) {
        int dadoAtacante = rand() % 6 + 1;
        int dadoDefensor = rand() % 6 + 1;

        printf("\nRodada!\n");
        printf("  Dado do atacante: %d\n", dadoAtacante);
        printf("  Dado do defensor: %d\n", dadoDefensor);

        if (dadoAtacante > dadoDefensor) {
            defensor->tropas -= 1;
            printf("  %s venceu a rodada! Tropas do defensor: %d\n",
                   atacante->nome, defensor->tropas);
        } else {
            atacante->tropas -= 1;
            printf("  %s defendeu a rodada! Tropas do atacante: %d\n",
                   defensor->nome, atacante->tropas);
        }
    }

    // Resultado final da batalha
    if (defensor->tropas <= 0) {
        printf("\n>>> %s conquistou o territorio %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // ocupa com metade das tropas do atacante
    } else {
        printf("\n>>> %s resistiu ao ataque de %s!\n", defensor->nome, atacante->nome);
    }
}

// Libera a memória alocada dinamicamente
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // inicializa a semente da aleatoriedade

    int qtd;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar(); // limpar buffer

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));

    cadastrarTerritorios(mapa, qtd);
    exibirTerritorios(mapa, qtd);

    int atacanteIdx, defensorIdx;

    printf("\nEscolha o territorio atacante (1 a %d): ", qtd);
    scanf("%d", &atacanteIdx);
    printf("Escolha o territorio defensor (1 a %d): ", qtd);
    scanf("%d", &defensorIdx);

    // Executa o ataque
    atacar(&mapa[atacanteIdx - 1], &mapa[defensorIdx - 1]);

    // Exibe situação final após a batalha
    exibirTerritorios(mapa, qtd);

    liberarMemoria(mapa);
    return 0;
}
