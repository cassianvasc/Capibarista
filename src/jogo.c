#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "jogo.h"
#include "lista_encadeada.h"
#include "menu.h"

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
    if(jogo->telaAtual == TELA_MENU){

        int largura = GetScreenWidth();
        int altura = GetScreenHeight();

        const char *titulo = "Capibarista";
        int tamanhoTitulo = 50;
        int larguraTitulo = MeasureText(titulo, tamanhoTitulo);

        DrawText(
            titulo,
            largura / 2 - larguraTitulo / 2,
            altura / 2 - 180,
            tamanhoTitulo,
            DARKBROWN
        );
        Rectangle botaoIniciar = {
            largura / 2 - 130,
            altura / 2 - 60,
            260,
            70
        };
        Rectangle botaoRanking = {
            largura / 2 - 130,
            altura / 2 + 30,
            260,
            70
        };
        if(botaoClicado(botaoIniciar, "Iniciar")){
            jogo->telaAtual = TELA_NOME;
        }
        if(botaoClicado(botaoRanking, "Ranking")){
            jogo->telaAtual = TELA_RANKING;
        }
    }
}