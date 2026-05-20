#ifndef RANKING_H
#define RANKING_H

#define MAX_RANKING 100

typedef struct JogadorRanking{
    char nome[32];
    int pontuacao;
} JogadorRanking;

void salvarPontuacao(char nome[], int pontuacao);

int carregarRanking(JogadorRanking ranking[]);

void ordenarRanking(JogadorRanking ranking[], int quantidade);

#endif