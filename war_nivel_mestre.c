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

// ======= Funções de Missões =======

// Sorteia uma missão e copia para o destino
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão do jogador
void exibirMissao(char* missao, int jogador) {
    printf("\n>>> Jogador %d, sua missao e: %s\n", jogador, missao);
}

// Verifica se a missão foi cumprida (lógica simples de exemplo)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 1 territorio")) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) {
                return 1; // vitória simulada
            }
        }
    }
    if (strstr(missao, "Eliminar cor vermelha")) {
        int encontrou = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                encontrou = 1;
                break;
            }
        }
        return !encontrou; // vitória se não encontrou vermelho
    }
    // Pode adicionar outras lógicas conforme a descrição
    return 0;
}

// ======= Funções de Territórios =======

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
void liberarMemoria(Territorio *mapa, char* missoesJogadores[], int qtdJogadores) {
    free(mapa);
    for (int i = 0; i < qtdJogadores; i++) {
        free(missoesJogadores[i]);
    }
}

int main() {
    srand(time(NULL)); // inicializa a semente da aleatoriedade

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 1 territorio",
        "Eliminar cor vermelha",
        "Conquistar 3 territorios",
        "Manter 2 territorios com mais de 5 tropas",
        "Eliminar todas as tropas de um inimigo"
    };
    int totalMissoes = 5;

    int qtd;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);
    getchar(); // limpar buffer

    // Alocação dinâmica do vetor de territórios
    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    cadastrarTerritorios(mapa, qtd);

    // Dois jogadores
    int qtdJogadores = 2;
    char* missoesJogadores[2];
    for (int i = 0; i < qtdJogadores; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        exibirMissao(missoesJogadores[i], i + 1);
    }

    int atacanteIdx, defensorIdx;
    int jogadorAtual = 0;

    while (1) {
        printf("\n===== Turno do Jogador %d =====\n", jogadorAtual + 1);
        exibirTerritorios(mapa, qtd);

        printf("\nEscolha o territorio atacante (1 a %d): ", qtd);
        scanf("%d", &atacanteIdx);
        printf("Escolha o territorio defensor (1 a %d): ", qtd);
        scanf("%d", &defensorIdx);

        atacar(&mapa[atacanteIdx - 1], &mapa[defensorIdx - 1]);

        // Verifica se missão foi cumprida
        if (verificarMissao(missoesJogadores[jogadorAtual], mapa, qtd)) {
            printf("\n>>> Jogador %d cumpriu sua missão e venceu o jogo!\n", jogadorAtual + 1);
            break;
        }

        // Alterna jogador
        jogadorAtual = (jogadorAtual + 1) % qtdJogadores;
    }

    liberarMemoria(mapa, missoesJogadores, qtdJogadores);
    return 0;
}
