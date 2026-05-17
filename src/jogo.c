#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "jogo.h"
#include "lista_encadeada.h"
#include "menu.h"
#include <stdio.h>

void inicializarJogo(Jogo *jogo){
    jogo->telaAtual = TELA_MENU;
    jogo->listaClientes = NULL;
    jogo->proximoIdCliente = 1;
    jogo->dinheiro = 0;
    jogo->tempoTurno = DURACAO_TURNO;
    jogo->nomeJogador[0] = '\0';
    jogo->tamanhoNome = 0;
    jogo->tempoSpawn = 0;
    jogo->intervaloSpawn = 5.0f;
}
//-------------------------------------------------------------------------------------------------------------------------------------
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

    else if(jogo->telaAtual == TELA_JOGO){
        float dt = GetFrameTime();

        jogo->tempoTurno -= dt;
        if(jogo->tempoTurno <= 0){
            jogo->tempoTurno = 0;
            jogo->telaAtual = TELA_FIM;
        }
        jogo->tempoSpawn += dt;
        atualizarPacienciaClientes(jogo->listaClientes, dt);
    if(jogo->tempoSpawn >= jogo->intervaloSpawn){

        Cliente *novo = criarCliente(jogo->proximoIdCliente);

        inserirClienteFinal(&jogo->listaClientes, novo);

        jogo->proximoIdCliente++;
        jogo->tempoSpawn = 0;
    }
    if(jogo->listaClientes != NULL && jogo->listaClientes->pacienciaAtual <= 0){
        removerClientePrimeiro(&jogo->listaClientes);
    }
    }
}
//----------------------------------------------------------------------------------------------------------------------------
void desenharClientes(Cliente *lista){

    Cliente *aux = lista;
    int x = 30;
    int y = 260;

    while(aux != NULL){

        DrawRectangle(x, y, 160, 130, BEIGE);
        DrawRectangleLines(x, y, 160, 130, DARKBROWN);

        char textoId[30];
        sprintf(textoId, "Cliente %d", aux->id);
        DrawText(textoId, x + 10, y + 10, 20, DARKBROWN);

        float porcentagem = aux->pacienciaAtual / aux->pacienciaMaxima;
        DrawRectangle(x + 10, y + 35, 120, 10, LIGHTGRAY);
        DrawRectangle(x + 10, y + 35, 120 * porcentagem, 10, GREEN);

        int deslocamento = 55;

        if(aux->pedido.cafe){
            DrawText("Cafe", x + 10, y + deslocamento, 18, MAROON);
            deslocamento += 22;
        }
        if(aux->pedido.tapioca){
            DrawText("Tapioca", x + 10, y + deslocamento, 18, MAROON);
            deslocamento += 22;
        }
        if(aux->pedido.bolo){
            char textoBolo[50];
            sprintf(textoBolo, "Bolo %s", nomeSaborBolo(aux->pedido.saborBolo));
            DrawText(textoBolo, x + 10, y + deslocamento, 18, MAROON);
        }
        x += 180;
        aux = aux->prox;
    }
}
//-------------------------------------------------------------------------------------------------------------------------
void atualizarPacienciaClientes(Cliente *lista, float dt){
    Cliente *aux = lista;
    while(aux != NULL){
        aux->pacienciaAtual -= dt;
        if(aux->pacienciaAtual < 0){
            aux->pacienciaAtual = 0;
        }
        aux = aux->prox;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
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

    DrawText(titulo, largura / 2 - larguraTitulo / 2, altura / 2 - 130, tamanhoTitulo, DARKBROWN);
    Rectangle caixaNome = {
        largura / 2 - 200,
        altura / 2 - 40,
        400,
        60
    };
    DrawRectangleRec(caixaNome, RAYWHITE);
    DrawRectangleLinesEx(caixaNome, 3, DARKBROWN);

    DrawText(jogo->nomeJogador, caixaNome.x + 15, caixaNome.y + 17, 28, DARKBROWN);

    const char *instrucao = "Pressione ENTER para comecar";
    int larguraInstrucao = MeasureText(instrucao, 22);
    DrawText(instrucao, largura / 2 - larguraInstrucao / 2, altura / 2 + 50, 22, DARKBROWN);
    }

    else if(jogo->telaAtual == TELA_JOGO){

    int largura = GetScreenWidth();

    DrawText("Capibarista", 30, 25, 32, DARKBROWN);

    char textoNome[80];
    sprintf(textoNome, "Jogador: %s", jogo->nomeJogador);
    DrawText(textoNome, 30, 75, 24, DARKBROWN);

    char textoDinheiro[80];
    sprintf(textoDinheiro, "Dinheiro: R$ %d", jogo->dinheiro);
    DrawText(textoDinheiro, 30, 110, 24, DARKBROWN);

    char textoMeta[80];
    sprintf(textoMeta, "Meta: R$ %d", META_DINHEIRO);
    DrawText(textoMeta, 30, 145, 24, DARKBROWN);

    char textoTempo[80];
    sprintf(textoTempo, "Tempo: %.0f", jogo->tempoTurno);
    DrawText(textoTempo, largura - 180, 30, 24, DARKBROWN);

    DrawText("Fila de clientes", 30, 220, 28, MAROON);
    desenharClientes(jogo->listaClientes);
    DrawText("Cozinha", 30, 420, 28, MAROON);
 }
}