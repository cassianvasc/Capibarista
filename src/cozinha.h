#ifndef COZINHA_H
#define COZINHA_H

#include "raylib.h"
#include "global.h"

typedef struct EstacaoTapioca {
    Rectangle areaInteracao;
    EstadoTapioca estado;
    float tempoNoFogo;
    bool penalidadeAplicada;
} EstacaoTapioca;


typedef struct EstacaoBolo {
    Rectangle areaInteracao;
    EstadoForno estado;
    SaborBolo sabor;   
    float tempoNoForno;
    bool penalidadeAplicada;
} EstacaoBolo;

typedef struct EstacaoCafe{
    Rectangle areaInteracao;
    EstadoCafe estado;
    float tempoPreparo;
} EstacaoCafe;

// --- ESTRUTURA GERAL DA COZINHA ---
typedef struct Cozinha {
    EstacaoTapioca fogao;
    EstacaoBolo forno;
    EstacaoCafe cafe;
} Cozinha;


void inicializarCozinha(Cozinha *cozinha);
void atualizarCozinha(Cozinha *cozinha, float dt);

#endif