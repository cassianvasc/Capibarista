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
    


    while(WindowShouldClose() == false){
        atualizarJogo(&jogo);

        BeginDrawing();
            ClearBackground(BEIGE);
            

            
            desenharJogo(&jogo);
        EndDrawing();
    }

    liberarLista(&jogo.listaClientes);
    

    
    CloseWindow();
    return 0;
}