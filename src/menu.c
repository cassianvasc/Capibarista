#include "menu.h"

int botaoClicado(Rectangle botao, const char *texto){
    Vector2 mouse = GetMousePosition();

    int mouseEmCima = CheckCollisionPointRec(mouse, botao);

    if(mouseEmCima){
        DrawRectangleRec(botao, ORANGE);
    }
    else{
        DrawRectangleRec(botao, GOLD);
    }

    DrawRectangleLinesEx(botao, 3, BROWN);

    int tamanhoFonte = 28;
    int larguraTexto = MeasureText(texto, tamanhoFonte);

    DrawText(
        texto,
        botao.x + botao.width / 2 - larguraTexto / 2,
        botao.y + botao.height / 2 - tamanhoFonte / 2,
        tamanhoFonte,
        DARKBROWN
    );

    if(mouseEmCima && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return 1;
    }

    return 0;
}