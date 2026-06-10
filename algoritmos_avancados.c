// Nível Novato - Tema: Árvore Binária
#include <stdio.h>  // Obrigatória
#include <stdlib.h> // malloc, free, exit
#include <string.h> // strcpy, strcmp

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
    int esquerdaExplorada;
    int direitaExplorada;
} Sala;

Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova == NULL) {
        printf("Erro: Falha na alocacao de memoria!\n");
        exit(1);
    }
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    nova->esquerdaExplorada = 0;
    nova->direitaExplorada = 0;
    return nova;
}

Sala* construirMansao() {
    Sala* hall = criarSala("Hall de Entrada");
    
    hall->esquerda = criarSala("Biblioteca");
    hall->direita  = criarSala("Cozinha");

    hall->esquerda->esquerda = criarSala("Sotao");
    hall->esquerda->direita  = criarSala("Sala de Jantar");

    hall->direita->esquerda = criarSala("Porao");
    hall->direita->direita  = criarSala("Caminho Bloqueado");
    
    return hall;
}

// Função auxiliar para sair do jogo de forma limpa
void sairDoJogo(Sala* mansao) {
    printf("\nSaindo da exploracao...\n");
    printf("========================================\n");
    printf("Finalizando o programa...\n");
    printf("Liberando memoria da arvore (percurso em POS-ORDEM)...\n");
    liberarMansao(mansao);
    printf("Memoria liberada com sucesso!\n");
    printf("========================================\n");
    printf("\nObrigado por jogar Detective Quest!\n");
    exit(0);
}

void explorarSalas(Sala* atual, Sala* raiz) {
    if (atual == NULL) return;

    while (1) {
        printf("\n======================================\n");
        printf("   Voce esta em: %s\n", atual->nome);
        printf("======================================\n");

        if (strcmp(atual->nome, "Caminho Bloqueado") == 0) {
            printf("ERRO: Este caminho esta bloqueado!\n");
            printf("Pressione ENTER para voltar...\n");
            getchar(); 
            getchar();
            return;
        }

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Este e um beco sem saida! Nao ha mais caminhos.\n");
        }

        printf("\nPara onde deseja ir?\n");
        printf("(E) Esquerda\n");
        printf("(D) Direita\n");

        if ((atual->esquerda == NULL && atual->direita == NULL) ||
            (atual->esquerdaExplorada && atual->direitaExplorada)) {
            printf("(S) Sair do Jogo\n");
        } else {
            printf("(S) Sair do Jogo (bloqueado - explore os dois lados primeiro)\n");
        }

        printf("Digite sua escolha: ");

        char linha[10];
        fgets(linha, sizeof(linha), stdin);
        char opcao = linha[0];

        if (opcao == 'e' || opcao == 'E') {
            if (atual->esquerda != NULL) {
                explorarSalas(atual->esquerda, raiz);
                atual->esquerdaExplorada = 1;
            } else {
                printf("Nao ha caminho para a esquerda!\n");
            }
        }
        else if (opcao == 'd' || opcao == 'D') {
            if (atual->direita != NULL) {
                explorarSalas(atual->direita, raiz);
                atual->direitaExplorada = 1;
            } else {
                printf("Nao ha caminho para a direita!\n");
            }
        }
        else if (opcao == 's' || opcao == 'S') {
            if ((atual->esquerda == NULL && atual->direita == NULL) ||
                (atual->esquerdaExplorada && atual->direitaExplorada)) {
                sairDoJogo(raiz);        // Sai do programa completamente
            } else {
                printf("Voce ainda nao explorou todos os caminhos deste comodo!\n");
                printf("Explore tanto a Esquerda quanto a Direita antes de sair.\n");
            }
        }
        else {
            printf("Opcao invalida! Digite E, D ou S.\n");
        }
    }
}

void liberarMansao(Sala* sala) {
    if (sala == NULL) return;
    liberarMansao(sala->esquerda);
    liberarMansao(sala->direita);
    free(sala);
}

int main() {
    printf("========================================\n");
    printf("     DETECTIVE QUEST - NIVEL NOVATO\n");
    printf("========================================\n\n");
    
    printf("Bem-vindo a Mansao Misteriosa!\n");
    printf("Explore todos os caminhos antes de poder sair do jogo!\n\n");

    Sala* mansao = construirMansao();
    explorarSalas(mansao, mansao);   // Passa a raiz para conseguir liberar depois

    return 0;  // Nunca deve chegar aqui
}
