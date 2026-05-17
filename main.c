#include "raylib.h"
#include "jogo.h"
#include "lista_encadeada.h"

int main(){
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Capibarista");

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