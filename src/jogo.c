#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "jogo.h"
#include "lista_encadeada.h"

void inicializarJogo(Jogo *jogo){

    jogo->telaAtual = TELA_MENU;

    jogo->listaClientes = NULL;

    jogo->proximoIdCliente = 1;

    jogo->dinheiro = 0;

    jogo->tempoTurno = DURACAO_TURNO;

    jogo->nomeJogador[0] = '\0';

    jogo->tamanhoNome = 0;
}
void atualizarJogo(Jogo *jogo){

}

void desenharJogo(Jogo *jogo){

}