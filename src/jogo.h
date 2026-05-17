#ifndef JOGO_H
#define JOGO_H
#include "global.h"
#include "cliente.h"

typedef struct Jogo{
    TelaJogo telaAtual;
    Cliente *listaClientes;
    int proximoIdCliente;
    int dinheiro;
    float tempoTurno;
    char nomeJogador[TAM_NOME];
    int tamanhoNome;
    float tempoSpawn;
    float intervaloSpawn;
}Jogo;

void inicializarJogo(Jogo *jogo);

void atualizarJogo(Jogo *jogo);

void desenharJogo(Jogo *jogo);

void atualizarPacienciaClientes(Cliente *lista, float dt);

void desenharClientes(Cliente *lista);

#endif