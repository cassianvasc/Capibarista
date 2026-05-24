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
    
    jogo.texturaMenu = LoadTexture("assests/Menu.png");
    jogo.texturaFundoJogo = LoadTexture("assests/background.jpg");

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
    

    UnloadTexture(jogo.btnNormalJogar);
    UnloadTexture(jogo.btnHoverJogar);
    UnloadTexture(jogo.btnNormalRanking);
    UnloadTexture(jogo.btnHoverRanking);
    UnloadTexture(jogo.btnNormalCreditos);
    UnloadTexture(jogo.btnHoverCreditos);
    CloseWindow();
    return 0;
}