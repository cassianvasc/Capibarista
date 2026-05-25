#include "raylib.h"
#include "jogo.h"
#include "lista_encadeada.h"

int main(){

    const int LARGURA_TELA = 1280;
    const int ALTURA_TELA = 720;
    
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Capibarista");

    SetTargetFPS(60);

    Jogo jogo;
    inicializarJogo(&jogo);
    
    jogo.texturaMenu = LoadTexture("assets/Menu.png");

    jogo.texturaTelaNome = LoadTexture("assets/TelaNome.png");
    jogo.texturaTelaCreditos = LoadTexture("assets/TelaCreditos.png");
    jogo.texturaRanking = LoadTexture("assets/TelaRanking.png");

    jogo.texturaFundoJogo = LoadTexture("assets/TelaJogo.png");
    jogo.iconCafe = LoadTexture("assets/copocheio.png");
    jogo.iconTapioca = LoadTexture("assets/pratotapioca.png");
    jogo.iconBoloGoiabada = LoadTexture("assets/pratogoiabada.png");
    jogo.iconBoloChocolate = LoadTexture("assets/pratochocolate.png");
    jogo.clienteAlceu = LoadTexture("assets/alceu.png");
    jogo.clienteCaboclo = LoadTexture("assets/caboclo.png");
    jogo.clienteChico = LoadTexture("assets/chico.png");
    jogo.clienteNatacha = LoadTexture("assets/natacha.png");
    jogo.frigideiraVazia = LoadTexture("assets/frigideiravazia.png");
    jogo.frigideiraCrua = LoadTexture("assets/frigideiracrua.png");
    jogo.frigideiraBoa = LoadTexture("assets/frigideiraboa.png");
    jogo.frigideiraQueimada = LoadTexture("assets/frigideiraqueimada.png");
    jogo.fornoDesligado = LoadTexture("assets/fornodesligado.png");
    jogo.fornoCru = LoadTexture("assets/fornocru.png");
    jogo.fornoPronto = LoadTexture("assets/fornoligado.png");
    jogo.fornoQueimado = LoadTexture("assets/fornoqueimado.png");


// ==========================================================================================================================
// Menu - Carregamento das texturas dos botões
    jogo.btnNormalJogar = LoadTexture("UI/btnJogar.png"); 
    jogo.btnHoverJogar = LoadTexture("UI/btnJogarHover.png");
    jogo.btnNormalRanking = LoadTexture("UI/btnRanking.png");
    jogo.btnHoverRanking = LoadTexture("UI/btnRankingHover.png");
    jogo.btnNormalCreditos = LoadTexture("UI/btnCreditos.png");
    jogo.btnHoverCreditos = LoadTexture("UI/btnCreditosHover.png");

    while(WindowShouldClose() == false){
        atualizarJogo(&jogo);

        BeginDrawing();
            ClearBackground(BEIGE);
            

            
            desenharJogo(&jogo);
        EndDrawing();
    }

    liberarLista(&jogo.listaClientes);
    
    UnloadTexture(jogo.texturaTelaNome);
    UnloadTexture(jogo.btnNormalJogar);
    UnloadTexture(jogo.btnHoverJogar);
    UnloadTexture(jogo.btnNormalRanking);
    UnloadTexture(jogo.btnHoverRanking);
    UnloadTexture(jogo.btnNormalCreditos);
    UnloadTexture(jogo.btnHoverCreditos);
    UnloadTexture(jogo.texturaFundoJogo);
    UnloadTexture(jogo.iconCafe);
    UnloadTexture(jogo.iconTapioca);
    UnloadTexture(jogo.iconBoloGoiabada);
    UnloadTexture(jogo.iconBoloChocolate);
    UnloadTexture(jogo.clienteAlceu);
    UnloadTexture(jogo.clienteCaboclo);
    UnloadTexture(jogo.clienteChico);
    UnloadTexture(jogo.clienteNatacha);
    UnloadTexture(jogo.frigideiraVazia);
    UnloadTexture(jogo.frigideiraCrua);
    UnloadTexture(jogo.frigideiraBoa);
    UnloadTexture(jogo.frigideiraQueimada);
    UnloadTexture(jogo.fornoDesligado);
    UnloadTexture(jogo.fornoCru);
    UnloadTexture(jogo.fornoPronto);
    UnloadTexture(jogo.fornoQueimado);
    UnloadTexture(jogo.texturaTelaCreditos);
    UnloadTexture(jogo.texturaRanking);


    CloseWindow();
    return 0;
}