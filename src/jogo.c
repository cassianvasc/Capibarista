#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "jogo.h"
#include "lista_encadeada.h"
#include "menu.h"
#include "cozinha.h"
#include "ranking.h"

void inicializarJogo(Jogo *jogo)
{
    jogo->telaAtual = TELA_MENU;
    jogo->listaClientes = NULL;
    inicializarCozinha(&jogo->cozinha);
    jogo->proximoIdCliente = 1;
    jogo->dinheiro = 0;
    jogo->tempoTurno = DURACAO_TURNO;
    jogo->nomeJogador[0] = '\0';
    jogo->tamanhoNome = 0;
    jogo->tempoSpawn = 0;
    jogo->intervaloSpawn = 5.0f;
    jogo->qtdTapioca = 0;
    jogo->qtdBoloGoiabada = 0;
    jogo->qtdBoloChocolate = 0;
    jogo->qtdCafe = 0;
    jogo->aviso[0] = '\0';
    jogo->tempoAviso = 0.0f;
}
//-------------------------------------------------------------------------------------------------------------------------------------
bool pedidoCompletoNaMao(Jogo *jogo, Cliente *cliente)
{

    if (cliente->pedido.cafe && jogo->qtdCafe <= 0)
    {
        return false;
    }
    if (cliente->pedido.tapioca && jogo->qtdTapioca <= 0)
    {
        return false;
    }
    if (cliente->pedido.bolo)
    {
        if (cliente->pedido.saborBolo == BOLO_GOIABADA && jogo->qtdBoloGoiabada <= 0)
        {
            return false;
        }
        if (cliente->pedido.saborBolo == BOLO_CHOCOLATE && jogo->qtdBoloChocolate <= 0)
        {
            return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------------
void atualizarJogo(Jogo *jogo)
{

    if (jogo->telaAtual == TELA_NOME)
    {
        int tecla = GetCharPressed();
        while (tecla > 0)
        {
            if (tecla >= 32 && tecla <= 125 && jogo->tamanhoNome < TAM_NOME - 1)
            {
                jogo->nomeJogador[jogo->tamanhoNome] = (char)tecla;
                jogo->tamanhoNome++;
                jogo->nomeJogador[jogo->tamanhoNome] = '\0';
            }
            tecla = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && jogo->tamanhoNome > 0)
        {
            jogo->tamanhoNome--;
            jogo->nomeJogador[jogo->tamanhoNome] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER) && jogo->tamanhoNome > 0)
        {
            jogo->telaAtual = TELA_JOGO;
        }
    }
    //=============================================================================
    else if (jogo->telaAtual == TELA_JOGO)
    {
        float dt = GetFrameTime();
        if (jogo->tempoAviso > 0)
        {
            jogo->tempoAviso -= dt;
        }

        jogo->tempoTurno -= dt;

        if (jogo->tempoTurno <= 0)
        {
            jogo->tempoTurno = 0;
            salvarPontuacao(jogo->nomeJogador, jogo->dinheiro);
            jogo->telaAtual = TELA_FIM;
        }
        jogo->tempoSpawn += dt;
        atualizarPacienciaClientes(jogo->listaClientes, dt);

        atualizarCozinha(&jogo->cozinha, dt);

        // Penalidade por tapioca queimada
        if (jogo->cozinha.fogao.estado == TAPIOCA_QUEIMADA && !jogo->cozinha.fogao.penalidadeAplicada)
        {
            jogo->dinheiro -= 5;
            sprintf(jogo->aviso, "Tapioca queimou! -R$ 5");
            jogo->tempoAviso = 2.0f;
            jogo->cozinha.fogao.penalidadeAplicada = true;
        }

        // Penalidade por bolo queimado
        if (jogo->cozinha.forno.estado == BOLO_QUEIMADO && !jogo->cozinha.forno.penalidadeAplicada)
        {
            jogo->dinheiro -= 10;
            sprintf(jogo->aviso, "Bolo queimou! -R$ 10");
            jogo->tempoAviso = 2.0f;
            jogo->cozinha.forno.penalidadeAplicada = true;
        }

        // pegar cafe pronto
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), jogo->cozinha.cafe.areaInteracao))
        {
            if (jogo->cozinha.cafe.estado == CAFE_PRONTO)
            {
                jogo->qtdCafe++;
                jogo->cozinha.cafe.estado = CAFE_MAQUINA_VAZIA;
                jogo->cozinha.cafe.tempoPreparo = 0.0f;
                return;
            }
        }

        // Pegar a tapioca pronta
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), jogo->cozinha.fogao.areaInteracao))
        {

            if (jogo->cozinha.fogao.estado == TAPIOCA_NO_PONTO)
            {
                jogo->qtdTapioca++;
                jogo->cozinha.fogao.estado = TAPIOCA_VAZIA;
                jogo->cozinha.fogao.tempoNoFogo = 0.0f;
                return;
            }
        }
        // Pegar bolo pronto
        if (
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), jogo->cozinha.forno.areaInteracao))
        {
            if (jogo->cozinha.forno.estado == BOLO_PRONTO)
            {

                if (jogo->cozinha.forno.sabor == BOLO_GOIABADA)
                {
                    jogo->qtdBoloGoiabada++;
                }
                else if (jogo->cozinha.forno.sabor == BOLO_CHOCOLATE)
                {
                    jogo->qtdBoloChocolate++;
                }

                jogo->cozinha.forno.estado = FORNO_VAZIO;
                jogo->cozinha.forno.tempoNoForno = 0.0f;
                return;
            }
        }

        // Entregar item clicando no cliente
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {

            Vector2 mouse = GetMousePosition();
            Cliente *cliente = jogo->listaClientes;

            int x = 30;
            int y = 260;

            while (cliente != NULL)
            {
                Rectangle areaCliente = {x, y, 160, 130};

                if (CheckCollisionPointRec(mouse, areaCliente))
                {
                    if (pedidoCompletoNaMao(jogo, cliente))
                    {
                        jogo->dinheiro += calcularGorjeta(cliente);

                        if (cliente->pedido.tapioca)
                        {
                            jogo->qtdTapioca--;
                        }
                        if (cliente->pedido.bolo)
                        {
                            if (cliente->pedido.saborBolo == BOLO_GOIABADA)
                            {
                                jogo->qtdBoloGoiabada--;
                            }
                            else if (cliente->pedido.saborBolo == BOLO_CHOCOLATE)
                            {
                                jogo->qtdBoloChocolate--;
                            }
                        }
                        if (cliente->pedido.cafe)
                        {
                            jogo->qtdCafe--;
                        }
                        removerClienteEspecifico(&jogo->listaClientes, cliente);
                    }
                    break;
                }
                x += 180;
                cliente = cliente->prox;
            }
        }
        if (jogo->tempoSpawn >= jogo->intervaloSpawn)
        {

            Cliente *novo = criarCliente(jogo->proximoIdCliente);

            inserirClienteFinal(&jogo->listaClientes, novo);

            jogo->proximoIdCliente++;
            jogo->tempoSpawn = 0;
        }
        removerClientesSemPaciencia(&jogo->listaClientes, &jogo->dinheiro, jogo->aviso, &jogo->tempoAviso);
    }
    //=============================================================================
    else if (jogo->telaAtual == TELA_FIM)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            inicializarJogo(jogo);
        }
    }
    //=============================================================================
    else if (jogo->telaAtual == TELA_RANKING)
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            jogo->telaAtual = TELA_MENU;
        }
    }

    //=============================================================================
    else if (jogo->telaAtual == TELA_CREDITOS)
    {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
        {
            jogo->telaAtual = TELA_MENU;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------
void desenharClientes(Jogo *jogo, Cliente *lista)
{
    Cliente *aux = lista;

    int x = 190;
    int y = 55;

    while (aux != NULL)
    {
        //========================
        // CLIENTE
        //========================

        Texture2D texturaCliente;
        float escalaCliente = 0.22f;
        Vector2 ajuste = {0, 0};

        float linhaBalcao = y + 300;

        int tipoCliente = aux->id % 4;

        if(tipoCliente == 0){
            texturaCliente = jogo->clienteAlceu;
            escalaCliente = 0.50f;
            ajuste = (Vector2){70, -25};
        }
        else if(tipoCliente == 1){
            texturaCliente = jogo->clienteCaboclo;
            escalaCliente = 0.20f;
            ajuste = (Vector2){30, -45};
        }
        else if(tipoCliente == 2){
            texturaCliente = jogo->clienteChico;
            escalaCliente = 0.50f;
            ajuste = (Vector2){40, -45};
        }
        else{
            texturaCliente = jogo->clienteNatacha;
            escalaCliente = 0.20f;
            ajuste = (Vector2){35, -45};
        }

        float alturaSprite = texturaCliente.height * escalaCliente;

        DrawTextureEx(
            texturaCliente,
            (Vector2){
                x + ajuste.x,
                linhaBalcao - alturaSprite + ajuste.y
            },
            0,
            escalaCliente,
            WHITE
        );

        //========================
        // BALAO
        //========================

        int larguraBalao = 150;
        int alturaBalao = 90;

        DrawRectangleRounded(
            (Rectangle){x, y, larguraBalao, alturaBalao},
            0.25f,
            10,
            Fade(RAYWHITE, 0.94f)
        );

        DrawRectangleRoundedLines(
            (Rectangle){x, y, larguraBalao, alturaBalao},
            0.25f,
            10,
            DARKBROWN
        );

        DrawTriangle(
            (Vector2){x + 68, y + alturaBalao},
            (Vector2){x + 88, y + alturaBalao},
            (Vector2){x + 78, y + alturaBalao + 18},
            Fade(RAYWHITE, 0.94f)
        );

        //========================
        // PACIENCIA
        //========================

        float porcentagem = aux->pacienciaAtual / aux->pacienciaMaxima;

        DrawRectangleRounded(
            (Rectangle){x + 20, y + 12, 115, 9},
            0.5f,
            10,
            LIGHTGRAY
        );

        DrawRectangleRounded(
            (Rectangle){x + 20, y + 12, 115 * porcentagem, 9},
            0.5f,
            10,
            GREEN
        );

        //========================
        // PEDIDOS
        //========================

        int qtdItens = 0;

        if(aux->pedido.cafe) qtdItens++;
        if(aux->pedido.tapioca) qtdItens++;
        if(aux->pedido.bolo) qtdItens++;

        int larguraTotalItens = 0;

        if(aux->pedido.cafe) larguraTotalItens += 38;
        if(aux->pedido.tapioca) larguraTotalItens += 52;
        if(aux->pedido.bolo) larguraTotalItens += 52;

        int iconX = x + (larguraBalao - larguraTotalItens) / 2;
        int iconY = y + 35;

        if(aux->pedido.cafe){

            DrawTextureEx(
                jogo->iconCafe,
                (Vector2){iconX, iconY - 3},
                0,
                0.060f,
                WHITE
            );

            iconX += 38;
        }

        if(aux->pedido.tapioca){

            DrawTextureEx(
                jogo->iconTapioca,
                (Vector2){iconX - 5, iconY + 4},
                0,
                0.085f,
                WHITE
            );

            iconX += 52;
        }

        if(aux->pedido.bolo){

            Texture2D texturaBolo;

            if(aux->pedido.saborBolo == BOLO_GOIABADA){
                texturaBolo = jogo->iconBoloGoiabada;
            }
            else{
                texturaBolo = jogo->iconBoloChocolate;
            }

            DrawTextureEx(
                texturaBolo,
                (Vector2){iconX - 5, iconY + 2},
                0,
                0.085f,
                WHITE
            );

            iconX += 52;
        }

        x += 230;
        aux = aux->prox;
    }
}
//-------------------------------------------------------------------------------------------------------------------------
void atualizarPacienciaClientes(Cliente *lista, float dt)
{
    Cliente *aux = lista;
    while (aux != NULL)
    {
        aux->pacienciaAtual -= dt;
        if (aux->pacienciaAtual < 0)
        {
            aux->pacienciaAtual = 0;
        }
        aux = aux->prox;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
void desenharJogo(Jogo *jogo)
{

    if (jogo->telaAtual == TELA_MENU)
    {

        DrawTexture(jogo->texturaMenu, 0, 0, WHITE);


        Vector2 posJogar = {760, 310};
        Vector2 posRanking = {760, 435};
        Vector2 posCreditos = {760, 560};

        if (botaoImagemClicado(posJogar, jogo->btnNormalJogar, jogo->btnHoverJogar))
        {
            jogo->telaAtual = TELA_NOME;
        }

        if (botaoImagemClicado(posRanking, jogo->btnNormalRanking, jogo->btnHoverRanking))
        {
            jogo->telaAtual = TELA_RANKING;
        }

        if (botaoImagemClicado(posCreditos, jogo->btnNormalCreditos, jogo->btnHoverCreditos))
        {
            jogo->telaAtual = TELA_CREDITOS;
        }
    }
        //======================================================================================
        else if (jogo->telaAtual == TELA_NOME)
        {

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
                60};
            DrawRectangleRec(caixaNome, RAYWHITE);
            DrawRectangleLinesEx(caixaNome, 3, DARKBROWN);

            DrawText(jogo->nomeJogador, caixaNome.x + 15, caixaNome.y + 17, 28, DARKBROWN);

            const char *instrucao = "Pressione ENTER para comecar";
            int larguraInstrucao = MeasureText(instrucao, 22);
            DrawText(instrucao, largura / 2 - larguraInstrucao / 2, altura / 2 + 50, 22, DARKBROWN);
        }

        //======================================================================================
        else if (jogo->telaAtual == TELA_JOGO)
        {

            int largura = GetScreenWidth();

            DrawTexture(jogo->texturaFundoJogo, 0, 0, WHITE);

            // DrawText("Capibarista", 30, 25, 32, DARKBROWN);

            // char textoNome[80];
            // sprintf(textoNome, "Jogador: %s", jogo->nomeJogador);
            // DrawText(textoNome, 30, 75, 24, DARKBROWN);

            // char textoDinheiro[80];
            // sprintf(textoDinheiro, "Dinheiro: R$ %d", jogo->dinheiro);
            // DrawText(textoDinheiro, 30, 110, 24, DARKBROWN);

            // char textoMeta[80];
            // sprintf(textoMeta, "Meta: R$ %d", META_DINHEIRO);
            // DrawText(textoMeta, 30, 145, 24, DARKBROWN);

            // char textoTempo[80];
            // sprintf(textoTempo, "Tempo: %.0f", jogo->tempoTurno);
            // DrawText(textoTempo, largura - 180, 30, 24, DARKBROWN);

            desenharClientes(jogo, jogo->listaClientes);

            char textoInventario[80];

            // sprintf(textoInventario, "Tapiocas: %d", jogo->qtdTapioca);
            // DrawText(textoInventario, largura - 220, 90, 22, DARKBROWN);

            // sprintf(textoInventario, "Bolo goiabada: %d", jogo->qtdBoloGoiabada);
            // DrawText(textoInventario, largura - 220, 120, 22, DARKBROWN);

            // sprintf(textoInventario, "Bolo chocolate: %d", jogo->qtdBoloChocolate);
            // DrawText(textoInventario, largura - 220, 150, 22, DARKBROWN);

            // sprintf(textoInventario, "Cafe: %d", jogo->qtdCafe);
            // DrawText(textoInventario, largura - 220, 60, 22, DARKBROWN);

            if (jogo->tempoAviso > 0)
            {
                int larguraTexto = MeasureText(jogo->aviso, 28);

                DrawRectangle(
                    GetScreenWidth() / 2 - larguraTexto / 2 - 20,
                    20,
                    larguraTexto + 40,
                    50,
                    Fade(BLACK, 0.7f));
                DrawText(
                    jogo->aviso,
                    GetScreenWidth() / 2 - larguraTexto / 2,
                    32,
                    28,
                    RED);
            }
            DrawRectangleLinesEx(jogo->cozinha.fogao.areaInteracao, 3, RED);

            DrawRectangleLinesEx(jogo->cozinha.forno.areaInteracao, 3, BLUE);

            DrawRectangleLinesEx(jogo->cozinha.cafe.areaInteracao, 3, GREEN);
        }

        //======================================================================================
        else if (jogo->telaAtual == TELA_FIM)
        {

            int largura = GetScreenWidth();
            int altura = GetScreenHeight();

            const char *resultado;

            if (jogo->dinheiro >= META_DINHEIRO)
            {
                resultado = "VOCE VENCEU!";
            }
            else
            {
                resultado = "VOCE PERDEU!";
            }

            int larguraResultado = MeasureText(resultado, 50);

            DrawText(
                resultado,
                largura / 2 - larguraResultado / 2,
                altura / 2 - 100,
                50,
                DARKBROWN);

            char textoDinheiro[80];

            sprintf(textoDinheiro, "Dinheiro final: R$ %d", jogo->dinheiro);

            int larguraDinheiro = MeasureText(textoDinheiro, 30);

            DrawText(
                textoDinheiro,
                largura / 2 - larguraDinheiro / 2,
                altura / 2 - 30,
                30,
                MAROON);

            const char *instrucao = "Pressione ENTER para voltar ao menu";
            int larguraInstrucao = MeasureText(instrucao, 24);

            DrawText(
                instrucao,
                largura / 2 - larguraInstrucao / 2,
                altura / 2 + 40,
                24,
                DARKBROWN);
        }

        //======================================================================================
        else if (jogo->telaAtual == TELA_RANKING)
        {
            int largura = GetScreenWidth();
            DrawText(
                "RANKING",
                largura / 2 - 100,
                50,
                50,
                DARKBROWN);
            JogadorRanking ranking[MAX_RANKING];
            int quantidade = carregarRanking(ranking);

            ordenarRanking(ranking, quantidade);

            int y = 140;

            for (int i = 0; i < quantidade && i < 10; i++)
            {
                char texto[100];
                sprintf(
                    texto,
                    "%d. %s - R$ %d",
                    i + 1,
                    ranking[i].nome,
                    ranking[i].pontuacao);
                DrawText(
                    texto,
                    largura / 2 - 180,
                    y,
                    28,
                    MAROON);
                y += 40;
            }
            DrawText(
                "Pressione ENTER para voltar ao menu",
                largura / 2 - 170,
                y + 40,
                24,
                DARKBROWN);
        }
    }