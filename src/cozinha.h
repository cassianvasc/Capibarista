#ifndef COZINHA_H
#define COZINHA_H

#include "raylib.h"
#include "global.h"

typedef struct EstacaoTapioca {
    Rectangle areaInteracao;
    EstadoTapioca estado;
    float tempoNoFogo;
} EstacaoTapioca;


typedef struct EstacaoBolo {
    Rectangle areaInteracao;
    EstadoForno estado;
    SaborBolo sabor;   
    float tempoNoForno;
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
void desenharCozinha(Cozinha *cozinha);

#endif