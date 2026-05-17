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
    
    if(jogo->telaAtual == TELA_NOME){
        int tecla = GetCharPressed();
        while(tecla > 0){
            if(tecla >= 32 && tecla <= 125 && jogo->tamanhoNome < TAM_NOME - 1){
                jogo->nomeJogador[jogo->tamanhoNome] = (char)tecla;
                jogo->tamanhoNome++;
                jogo->nomeJogador[jogo->tamanhoNome] = '\0';
            }
            tecla = GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE) && jogo->tamanhoNome > 0){

            jogo->tamanhoNome--;
            jogo->nomeJogador[jogo->tamanhoNome] = '\0';
        }
        if(IsKeyPressed(KEY_ENTER) && jogo->tamanhoNome > 0){
            jogo->telaAtual = TELA_JOGO;
        }
    }
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
    else if(jogo->telaAtual == TELA_NOME){
    int largura = GetScreenWidth();
    int altura = GetScreenHeight();
    const char *titulo = "Digite seu nome";
    int tamanhoTitulo = 40;
    int larguraTitulo = MeasureText(titulo, tamanhoTitulo);

    DrawText(
        titulo,
        largura / 2 - larguraTitulo / 2,
        altura / 2 - 130,
        tamanhoTitulo,
        DARKBROWN
    );
    Rectangle caixaNome = {
        largura / 2 - 200,
        altura / 2 - 40,
        400,
        60
    };
    DrawRectangleRec(caixaNome, RAYWHITE);
    DrawRectangleLinesEx(caixaNome, 3, DARKBROWN);
    DrawText(
        jogo->nomeJogador,
        caixaNome.x + 15,
        caixaNome.y + 17,
        28,
        DARKBROWN
    );
    const char *instrucao = "Pressione ENTER para comecar";
    int larguraInstrucao = MeasureText(instrucao, 22);
    DrawText(
        instrucao,
        largura / 2 - larguraInstrucao / 2,
        altura / 2 + 50,
        22,
        DARKBROWN
    );
}
}