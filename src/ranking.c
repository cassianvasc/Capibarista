#include "ranking.h"
#include <stdio.h>
#include <string.h>

void salvarPontuacao(char nome[], int pontuacao){
    FILE *arquivo = fopen("ranking.txt", "a");
    if(arquivo == NULL){
        return;
    }
    fprintf(arquivo, "%s %d\n", nome, pontuacao);
    fclose(arquivo);
}

int carregarRanking(JogadorRanking ranking[]){
    FILE *arquivo = fopen("ranking.txt", "r");
    if(arquivo == NULL){
        return 0;
    }
    int quantidade = 0;
    while(quantidade < MAX_RANKING && fscanf(arquivo, "%31s %d", ranking[quantidade].nome, &ranking[quantidade].pontuacao) == 2){
        quantidade++;
    }
    fclose(arquivo);
    return quantidade;
}

//bubble sort para ordenaçao do ranking
void ordenarRanking(JogadorRanking ranking[], int quantidade){
    int n = 1; // marcador para percorrer o vetor ate o fim
    int troca = 1; //flag de troca

    while(n <= quantidade && troca == 1){
        troca = 0;

        for(int i = 0; i < quantidade - 1; i++){
            if(ranking[i].pontuacao < ranking[i + 1].pontuacao){
                JogadorRanking aux = ranking[i];
                ranking[i] = ranking[i + 1];
                ranking[i + 1] = aux;
                troca = 1;
            }
        }
        n++;
    }
}