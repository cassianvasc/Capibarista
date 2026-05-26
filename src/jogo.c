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

            int x = 190;
            int y = 55;

            while (cliente != NULL)
            {
                Rectangle areaCliente = {
                    x,
                    y,
                    190,
                    300
                };

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
                            else
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

                x += 230;
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


        Vector2 posJogar = {880, 290};
        Vector2 posRanking = {880, 445};
        Vector2 posCreditos = {880, 590};

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
        else if (jogo->telaAtual == TELA_NOME){

            DrawTexture(jogo->texturaTelaNome,0,0,WHITE);
            Rectangle caixaNome = {
                570,
                345,
                540,
                60
            };
            DrawText(jogo->nomeJogador,caixaNome.x + 20,caixaNome.y + 15,30,WHITE);
        }
    

        //======================================================================================
        else if (jogo->telaAtual == TELA_JOGO)
        {
            char textoInventario[80];
            DrawTexture(jogo->texturaFundoJogo, 0, 0, WHITE);

            //========================
            // HUD SUPERIOR
            //========================

            char textoHud[100];

            DrawRectangleRounded(
                (Rectangle){360, 10, 560, 55},
                0.25f,
                10,
                Fade(RAYWHITE, 0.88f)
            );

            DrawRectangleRoundedLines(
                (Rectangle){360, 10, 560, 55},
                0.25f,
                10,
                DARKBROWN
            );

            sprintf(textoHud, "Jogador: %s", jogo->nomeJogador);
            DrawText(textoHud, 380, 27, 22, DARKBROWN);

            sprintf(textoHud, "R$ %d / %d", jogo->dinheiro, META_DINHEIRO);
            DrawText(textoHud, 610, 27, 22, DARKBROWN);

            sprintf(textoHud, "Tempo: %.0f", jogo->tempoTurno);
            DrawText(textoHud, 760, 27, 22, DARKBROWN);

            //========================
            // ITENS PRONTOS
            //========================

            int cafeX = 230;
            int cafeY = 315;

            int tapiocaX = 210;
            int tapiocaY = 365;

            int goiabadaX = 195;
            int goiabadaY = 410;

            int chocolateX = 175;
            int chocolateY = 460;

            //========================
            // CAFE
            //========================

            DrawTextureEx(
                jogo->iconCafe,
                (Vector2){cafeX, cafeY},
                0,
                0.055f,
                WHITE
            );

            sprintf(textoInventario, "x%d", jogo->qtdCafe);

            DrawText(
                textoInventario,
                cafeX + 60,
                cafeY + 18,
                22,
                WHITE
            );

            //========================
            // TAPIOCA
            //========================

            DrawTextureEx(
                jogo->iconTapioca,
                (Vector2){tapiocaX, tapiocaY},
                0,
                0.075f,
                WHITE
            );

            sprintf(textoInventario, "x%d", jogo->qtdTapioca);

            DrawText(
                textoInventario,
                tapiocaX + 60,
                tapiocaY + 18,
                22,
                WHITE
            );

            //========================
            // BOLO GOIABADA
            //========================

            DrawTextureEx(
                jogo->iconBoloGoiabada,
                (Vector2){goiabadaX, goiabadaY},
                0,
                0.075f,
                WHITE
            );

            sprintf(textoInventario, "x%d", jogo->qtdBoloGoiabada);

            DrawText(
                textoInventario,
                goiabadaX + 60,
                goiabadaY + 18,
                22,
                WHITE
            );

            //========================
            // BOLO CHOCOLATE
            //========================

            DrawTextureEx(
                jogo->iconBoloChocolate,
                (Vector2){chocolateX, chocolateY},
                0,
                0.075f,
                WHITE
            );

            sprintf(textoInventario, "x%d", jogo->qtdBoloChocolate);

            DrawText(
                textoInventario,
                chocolateX + 60,
                chocolateY + 18,
                22,
                WHITE
            );

            desenharClientes(jogo, jogo->listaClientes);

            if (jogo->tempoAviso > 0){
                int larguraTexto = MeasureText(jogo->aviso, 42);

                int caixaLargura = larguraTexto + 80;
                int caixaAltura = 90;

                int caixaX = GetScreenWidth()/2 - caixaLargura/2;
                int caixaY = GetScreenHeight()/2 - caixaAltura/2;

                DrawRectangleRounded(
                    (Rectangle){caixaX, caixaY, caixaLargura, caixaAltura},
                    0.2f,
                    10,
                    Fade(BLACK, 0.80f)
                );
                DrawRectangleRoundedLines(
                    (Rectangle){caixaX, caixaY, caixaLargura, caixaAltura},
                    0.2f,
                    10,
                    RED
                );
                DrawText(
                    jogo->aviso,
                    GetScreenWidth()/2 - larguraTexto/2,
                    caixaY + 26,
                    42,
                    RED
                );
            }
            //==============================================
            //             desenho frigideira 
            // =============================================
            Texture2D texturaFrigideira;
            if(jogo->cozinha.fogao.estado == TAPIOCA_VAZIA){
                texturaFrigideira = jogo->frigideiraVazia;
            }
            else if(jogo->cozinha.fogao.estado == TAPIOCA_CRUA){
                texturaFrigideira = jogo->frigideiraCrua;
            }
            else if(jogo->cozinha.fogao.estado == TAPIOCA_NO_PONTO){
                texturaFrigideira = jogo->frigideiraBoa;
            }
            else{
                texturaFrigideira = jogo->frigideiraQueimada;
            }
            DrawTextureEx(
                texturaFrigideira,
                (Vector2){707, 380},
                0,
                0.24f,
                WHITE
            );
        
        //==============================================
        //               desenho forno
        // =============================================

            Texture2D texturaForno;
            if(jogo->cozinha.forno.estado == FORNO_VAZIO)
            {
                texturaForno = jogo->fornoDesligado;
            }
            else if(jogo->cozinha.forno.estado == BOLO_ASSANDO)
            {
                texturaForno = jogo->fornoCru;
            }
            else if(jogo->cozinha.forno.estado == BOLO_PRONTO)
            {
                texturaForno = jogo->fornoPronto;
            }
            else
            {
                texturaForno = jogo->fornoQueimado;
            }

            DrawTexturePro(
                texturaForno,
                (Rectangle){0, 0, texturaForno.width, texturaForno.height},
                (Rectangle){810, 538, 230, 100},
                (Vector2){0, 0},
                0,
                WHITE
            );
            //==============================================
            //               desenho cafeteira
            // =============================================

            Texture2D texturaCafe;
            if(jogo->cozinha.cafe.estado == CAFE_MAQUINA_VAZIA)
            {
                texturaCafe = jogo->cafeteiraVazia;
            }
            else if(jogo->cozinha.cafe.estado == CAFE_PREPARANDO)
            {
                texturaCafe = jogo->cafeteiraLigada;
            }
            else
            {
                texturaCafe = jogo->cafeteiraPronta;
            }

            DrawTexturePro(
                texturaCafe,
                (Rectangle){0, 0, texturaCafe.width, texturaCafe.height},
                (Rectangle){937, 315, 135, 185},
                (Vector2){0, 0},
                0,
                WHITE
            );

        }

        //======================================================================================

        else if (jogo->telaAtual == TELA_FIM)
        {
            DrawTexture(jogo->texturaTelaFim, 0, 0, WHITE);

            const char *resultado;

            if(jogo->dinheiro >= META_DINHEIRO){
                resultado = "VOCE VENCEU!";
            }
            else{
                resultado = "VOCE PERDEU!";
            }

            int larguraResultado = MeasureText(resultado, 50);

            DrawText(
                resultado,
                GetScreenWidth()/2 - larguraResultado/2,
                185,
                50,
                DARKBROWN
            );

            char textoDinheiro[80];
            sprintf(textoDinheiro, "Dinheiro final: R$ %d", jogo->dinheiro);

            int larguraDinheiro = MeasureText(textoDinheiro, 32);

            DrawText(
                textoDinheiro,
                GetScreenWidth()/2 - larguraDinheiro/2,
                285,
                32,
                DARKBROWN
            );

            DrawText(
                "Pressione ENTER para voltar ao menu",
                420,
                455,
                26,
                DARKBROWN
            );
        }

        //======================================================================================
        else if (jogo->telaAtual == TELA_RANKING)
        {
            DrawTexture(jogo->texturaRanking, 0, 0, WHITE);

            JogadorRanking ranking[MAX_RANKING];
            int quantidade = carregarRanking(ranking);

            ordenarRanking(ranking, quantidade);

            int y = 215;

            for(int i = 0; i < quantidade && i < 10; i++)
            {
                char texto[100];

                sprintf(
                    texto,
                    "%d. %s - R$ %d",
                    i + 1,
                    ranking[i].nome,
                    ranking[i].pontuacao
                );

                DrawText(
                    texto,
                    455,
                    y,
                    30,
                    WHITE
                );

                y += 42;
            }

            DrawText(
                "Pressione ENTER para voltar",
                470,
                670,
                24,
                WHITE
            );
        }
        else if (jogo->telaAtual == TELA_CREDITOS)
        {
            DrawTexture(jogo->texturaTelaCreditos, 0, 0, WHITE);

            DrawText(
                "Pressione ENTER para voltar",
                470,
                670,
                24,
                WHITE
            );
        }
    }