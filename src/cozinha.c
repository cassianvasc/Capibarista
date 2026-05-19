#include "cozinha.h"

void inicializarCozinha(Cozinha *cozinha)
{
    // Inicializa a Tapioca no Fogão
    cozinha->fogao.estado = TAPIOCA_VAZIA;
    cozinha->fogao.tempoNoFogo = 0.0f;
    cozinha->fogao.areaInteracao = (Rectangle){100, 400, 100, 100}; // Exemplo de posição

    // Inicializa o Bolo no Forno
    cozinha->forno.estado = FORNO_VAZIO;
    cozinha->forno.tempoNoForno = 0.0f;
    cozinha->forno.areaInteracao = (Rectangle){250, 400, 100, 100}; // Exemplo de posição
}

void atualizarCozinha(Cozinha *cozinha, float dt)
{
    Vector2 mouse = GetMousePosition();
    bool clicou = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // ==========================================
    // LÓGICA DO FORNO (BOLO)
    // ==========================================
    if (cozinha->forno.estado != FORNO_VAZIO)
    {
        cozinha->forno.tempoNoForno += dt;

        // Se está assando e passou de 5 segundos, fica pronto
        if (cozinha->forno.estado == BOLO_ASSANDO && cozinha->forno.tempoNoForno >= 5.0f)
        {
            cozinha->forno.estado = BOLO_PRONTO;
        }
        // Se ficou pronto e ficou mais 4 segundos (9 no total), queima
        else if (cozinha->forno.estado == BOLO_PRONTO && cozinha->forno.tempoNoForno >= 9.0f)
        {
            cozinha->forno.estado = BOLO_QUEIMADO;
        }
    }

    // Interação de Clique no Forno
    if (clicou && CheckCollisionPointRec(mouse, cozinha->forno.areaInteracao))
    {
        if (cozinha->forno.estado == FORNO_VAZIO)
        {
            cozinha->forno.estado = BOLO_ASSANDO;
            cozinha->forno.tempoNoForno = 0.0f;
            cozinha->forno.sabor = BOLO_CHOCOLATE; // Padrão temporário
        }
        else if (cozinha->forno.estado == BOLO_PRONTO)
        {
            // nao faz nada aqui
            // quem pega o bolo pronto sera o jogo.c
        }
        else if (cozinha->forno.estado == BOLO_QUEIMADO)
        {
            // Jogador limpa o forno (joga no lixo)
            cozinha->forno.estado = FORNO_VAZIO;
        }
    }


    // LÓGICA DO FOGÃO (TAPIOCA)
    
    if (cozinha->fogao.estado != TAPIOCA_VAZIA)
    {
        cozinha->fogao.tempoNoFogo += dt;

        // Se está crua e passou de 3 segundos, fica no ponto
        if (cozinha->fogao.estado == TAPIOCA_CRUA && cozinha->fogao.tempoNoFogo >= 3.0f)
        {
            cozinha->fogao.estado = TAPIOCA_NO_PONTO;
        }
        // Se ficou no ponto e ficou mais 2 segundos (5 no total), queima
        else if (cozinha->fogao.estado == TAPIOCA_NO_PONTO && cozinha->fogao.tempoNoFogo >= 5.0f)
        {
            cozinha->fogao.estado = TAPIOCA_QUEIMADA;
        }
    }

    // Interação de Clique no Fogão 
    if (clicou && CheckCollisionPointRec(mouse, cozinha->fogao.areaInteracao))
    {
        if (cozinha->fogao.estado == TAPIOCA_VAZIA)
        {
            cozinha->fogao.estado = TAPIOCA_CRUA;
            cozinha->fogao.tempoNoFogo = 0.0f;
            
        }
        else if (cozinha->fogao.estado == TAPIOCA_NO_PONTO)
        {
            // nao faz nada aqui
            // quem pega a tapioca pronta sera o jogo.c
        }
        else if (cozinha->fogao.estado == TAPIOCA_QUEIMADA)
        {
            
            cozinha->fogao.estado = TAPIOCA_VAZIA;
        }
    }
}

void desenharCozinha(Cozinha *cozinha) {
    // --- DESENHAR FOGÃO (TAPIOCA) ---
    DrawRectangleRec(cozinha->fogao.areaInteracao, DARKGRAY); // Fundo do fogão
    
    switch(cozinha->fogao.estado) {
        case TAPIOCA_VAZIA:
            DrawText("Vazia", cozinha->fogao.areaInteracao.x + 20, cozinha->fogao.areaInteracao.y + 40, 20, LIGHTGRAY);
            break;
        case TAPIOCA_CRUA:
            DrawRectangleRec(cozinha->fogao.areaInteracao, WHITE);
            DrawText("Crua", cozinha->fogao.areaInteracao.x + 25, cozinha->fogao.areaInteracao.y + 40, 20, BLACK);
            break;
        case TAPIOCA_NO_PONTO:
            DrawRectangleRec(cozinha->fogao.areaInteracao, YELLOW);
            DrawText("Pronta!", cozinha->fogao.areaInteracao.x + 15, cozinha->fogao.areaInteracao.y + 40, 20, BLACK);
            break;
        case TAPIOCA_QUEIMADA:
            DrawRectangleRec(cozinha->fogao.areaInteracao, BLACK);
            DrawText("Queimou", cozinha->fogao.areaInteracao.x + 10, cozinha->fogao.areaInteracao.y + 40, 20, RED);
            break;
    }

    // --- DESENHAR FORNO (BOLO) ---
    DrawRectangleRec(cozinha->forno.areaInteracao, DARKGRAY); // Fundo do forno
    
    switch(cozinha->forno.estado) {
        case FORNO_VAZIO:
            DrawText("Vazio", cozinha->forno.areaInteracao.x + 20, cozinha->forno.areaInteracao.y + 40, 20, LIGHTGRAY);
            break;
        case BOLO_ASSANDO:
            DrawRectangleRec(cozinha->forno.areaInteracao, ORANGE);
            DrawText("Assando", cozinha->forno.areaInteracao.x + 10, cozinha->forno.areaInteracao.y + 40, 20, BLACK);
            break;
        case BOLO_PRONTO:
            DrawRectangleRec(cozinha->forno.areaInteracao, BROWN);
            DrawText("Pronto!", cozinha->forno.areaInteracao.x + 15, cozinha->forno.areaInteracao.y + 40, 20, WHITE);
            break;
        case BOLO_QUEIMADO:
            DrawRectangleRec(cozinha->forno.areaInteracao, BLACK);
            DrawText("Queimou", cozinha->forno.areaInteracao.x + 10, cozinha->forno.areaInteracao.y + 40, 20, RED);
            break;
    }
}