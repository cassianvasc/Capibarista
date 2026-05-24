#include "menu.h"

int botaoImagemClicado(Vector2 posicao, Texture2D texturaNormal, Texture2D texturaHover){
    Vector2 mouse = GetMousePosition();
    
    Rectangle areaColisao = { posicao.x, posicao.y, texturaNormal.width, texturaNormal.height };
    
    int mouseEmCima = CheckCollisionPointRec(mouse, areaColisao);

    Texture2D texturaAtual = mouseEmCima ? texturaHover : texturaNormal;

    DrawTexture(texturaAtual, posicao.x, posicao.y, WHITE);

    if(mouseEmCima && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        return 1;
    }

    return 0;
}