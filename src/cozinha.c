#include "cozinha.h"

void inicializarCozinha(Cozinha *cozinha)
{
    // Inicializa a Tapioca no Fogão
    cozinha->fogao.estado = TAPIOCA_VAZIA;
    cozinha->fogao.tempoNoFogo = 0.0f;
    cozinha->fogao.areaInteracao = (Rectangle){718, 395, 120, 90};

    // Inicializa o Bolo no Forno
    cozinha->forno.estado = FORNO_VAZIO;
    cozinha->forno.tempoNoForno = 0.0f;
    cozinha->forno.areaInteracao = (Rectangle){810, 540, 230, 100};

    //Inicializa café na maquina
    cozinha->cafe.estado = CAFE_MAQUINA_VAZIA;
    cozinha->cafe.tempoPreparo = 0.0f;
    cozinha->cafe.areaInteracao = (Rectangle){980, 350, 125, 145};

    cozinha->fogao.penalidadeAplicada = false;
    cozinha->forno.penalidadeAplicada = false;
}

void atualizarCozinha(Cozinha *cozinha, float dt)
{
    Vector2 mouse = GetMousePosition();
    bool clicou = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    // LÓGICA DO CAFÉ
    if(cozinha->cafe.estado == CAFE_PREPARANDO){

        cozinha->cafe.tempoPreparo += dt;

        if(cozinha->cafe.tempoPreparo >= 4.0f){
            cozinha->cafe.estado = CAFE_PRONTO;
        }
    }
    if(clicou && CheckCollisionPointRec(mouse, cozinha->cafe.areaInteracao)){

        if(cozinha->cafe.estado == CAFE_MAQUINA_VAZIA){
            cozinha->cafe.estado = CAFE_PREPARANDO;
            cozinha->cafe.tempoPreparo = 0.0f;
        }
    }

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
            cozinha->forno.penalidadeAplicada = false;

            // goiabada sera o sabor padrao
            cozinha->forno.sabor = BOLO_GOIABADA;

            // segurando C muda para chocolate
            if(IsKeyDown(KEY_C)){
                cozinha->forno.sabor = BOLO_CHOCOLATE;
            }
        }
        else if (cozinha->forno.estado == BOLO_QUEIMADO)
        {
            // Jogador limpa o forno (joga no lixo)
            cozinha->forno.estado = FORNO_VAZIO;
            cozinha->forno.tempoNoForno = 0.0f;
            cozinha->forno.penalidadeAplicada = false;

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
            cozinha->fogao.penalidadeAplicada = false;
            
        }
        else if (cozinha->fogao.estado == TAPIOCA_QUEIMADA)
        {
            cozinha->fogao.estado = TAPIOCA_VAZIA;
            cozinha->fogao.tempoNoFogo = 0.0f;
            cozinha->fogao.penalidadeAplicada = false;
        }
    }
}