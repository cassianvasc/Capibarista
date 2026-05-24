#ifndef JOGO_H
#define JOGO_H
#include "global.h"
#include "cliente.h"
#include "cozinha.h"

typedef struct Jogo{
    TelaJogo telaAtual;
    Cliente *listaClientes;
    Cozinha cozinha;
    int proximoIdCliente;
    int dinheiro;
    float tempoTurno;
    char nomeJogador[TAM_NOME];
    int tamanhoNome;
    float tempoSpawn;
    float intervaloSpawn;
    int qtdTapioca;
    int qtdBoloGoiabada;
    int qtdBoloChocolate;
    int qtdCafe;
    char aviso[100];
    float tempoAviso;
    Texture2D texturaMenu;
    Texture2D texturaFundoJogo;
    Texture2D btnNormalJogar;
    Texture2D btnHoverJogar;
    Texture2D btnNormalRanking;
    Texture2D btnHoverRanking;
    Texture2D btnNormalCreditos;
    Texture2D btnHoverCreditos;
}Jogo;

void inicializarJogo(Jogo *jogo);

void atualizarJogo(Jogo *jogo);

void desenharJogo(Jogo *jogo);

void atualizarPacienciaClientes(Cliente *lista, float dt);

void desenharClientes(Cliente *lista);



#endif