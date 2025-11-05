// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

#include <stdio.h>      // Entrada e saída (printf, scanf)
#include <stdlib.h>     // Alocação de memória (malloc, calloc, free)
#include <string.h>     // Manipulação de strings (strcpy, strcmp)
#include <time.h>       // Geração de números aleatórios com srand/time
#include <locale.h>     // Configuração de idioma (setlocale)

// --- Constantes Globais ---
#define MAX_TERRITORIOS 10
#define MAX_NOME 50
#define MAX_MISSOES 5

// --- Estrutura de Dados ---
typedef struct {
    char nome[MAX_NOME];
    char corExercito[20];
    int tropas;
} Territorio;

// --- Protótipos das Funções ---
// Funções de setup e gerenciamento de memória:
Territorio* alocarMapa(int tamanho);
void inicializarTerritorios(Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa);

// Funções de interface com o usuário:
void exibirMenuPrincipal(void);
void exibirMapa(const Territorio* mapa, int tamanho);
void exibirMissao(int idMissao);

// Funções de lógica principal do jogo:
void faseDeAtaque(Territorio* mapa, int tamanho);
void simularAtaque(Territorio* origem, Territorio* destino);
int sortearMissao(void);
int verificarVitoria(const Territorio* mapa, int tamanho, int idMissao, const char* corJogador);

// Função utilitária:
void limparBufferEntrada(void);

// --- Função Principal (main) ---
int main() {
    setlocale(LC_ALL, "Portuguese");

    srand(time(NULL)); // Inicializa a semente aleatória

    // 1. Configuração Inicial
    int tamanhoMapa = MAX_TERRITORIOS;
    Territorio* mapa = alocarMapa(tamanhoMapa);
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1;
    }

    inicializarTerritorios(mapa, tamanhoMapa);
    char corJogador[] = "Azul";
    int idMissao = sortearMissao();

    int opcao, venceu = 0;

    // 2. Loop Principal do Jogo
    do {
        exibirMapa(mapa, tamanhoMapa);
        exibirMissao(idMissao);
        exibirMenuPrincipal();

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, tamanhoMapa);
                break;
            case 2:
                venceu = verificarVitoria(mapa, tamanhoMapa, idMissao, corJogador);
                if (venceu)
                    printf("\nParabéns! Você completou sua missão!\n");
                else
                    printf("\nVocê ainda não cumpriu sua missão.\n");
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
        }

    } while (opcao != 0 && !venceu);

    // 3. Limpeza
    liberarMemoria(mapa);

    return 0;
}

// --- Implementações básicas das Funções ---
Territorio* alocarMapa(int tamanho) {
    return (Territorio*) calloc(tamanho, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa, int tamanho) {
    const char* nomes[] = {"Brasil", "Argentina", "Chile", "Peru", "México", "Canadá", "EUA", "França", "Alemanha", "Itália"};
    for (int i = 0; i < tamanho; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, (i % 2 == 0) ? "Azul" : "Vermelho");
        mapa[i].tropas = rand() % 10 + 1;
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

void exibirMenuPrincipal(void) {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair\n");
}

void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %-10s | Tropas: %2d | Exército: %-10s\n",
               i + 1, mapa[i].nome, mapa[i].tropas, mapa[i].corExercito);
    }
}

void exibirMissao(int idMissao) {
    printf("\n===== MISSÃO =====\n");
    switch (idMissao) {
        case 0: printf("Conquistar 5 territórios.\n"); break;
        case 1: printf("Destruir o exército vermelho.\n"); break;
        case 2: printf("Conquistar toda a América do Sul.\n"); break;
        case 3: printf("Dominar 3 continentes.\n"); break;
        case 4: printf("Ter mais de 40 tropas distribuídas.\n"); break;
        default: printf("Missão desconhecida.\n"); break;
    }
}

void faseDeAtaque(Territorio* mapa, int tamanho) {
    printf("\nFase de ataque (em desenvolvimento)...\n");
}

void simularAtaque(Territorio* origem, Territorio* destino) {
    printf("\nSimulação de ataque (em desenvolvimento)...\n");
}

int sortearMissao(void) {
    return rand() % MAX_MISSOES;
}

int verificarVitoria(const Territorio* mapa, int tamanho, int idMissao, const char* corJogador) {
    int conquistados = 0, tropas = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mapa[i].corExercito, corJogador) == 0) {
            conquistados++;
            tropas += mapa[i].tropas;
        }
    }

    switch (idMissao) {
        case 0: return conquistados >= 5;
        case 4: return tropas >= 40;
        default: return 0;
    }
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
