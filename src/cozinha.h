#ifndef COZINHA_H
#define COZINHA_H

#include "raylib.h"


// --- ESTAÇÃO DA TAPIOCA ---
typedef enum EstadoTapioca {
    TAPIOCA_VAZIA,
    TAPIOCA_CRUA,
    TAPIOCA_NO_PONTO,
    TAPIOCA_QUEIMADA
} EstadoTapioca;

typedef struct EstacaoTapioca {
    Rectangle areaInteracao;
    EstadoTapioca estado;
    float tempoNoFogo;
} EstacaoTapioca;

// --- ESTAÇÃO DO BOLO (FORNO) ---
typedef enum EstadoForno {
    FORNO_VAZIO,
    BOLO_ASSANDO,      
    BOLO_PRONTO,     
    BOLO_QUEIMADO     
} EstadoForno;

typedef enum SaborBolo{
    BOLO_NENHUM,
    BOLO_GOIABADA,
    BOLO_CHOCOLATE
} SaborBolo;

typedef struct EstacaoBolo {
    Rectangle areaInteracao;
    EstadoForno estado;
    SaborBolo sabor;   
    float tempoNoForno;
} EstacaoBolo;

// --- ESTRUTURA GERAL DA COZINHA ---
typedef struct Cozinha {
    EstacaoTapioca fogao;
    EstacaoBolo forno;
    
} Cozinha;


void inicializarCozinha(Cozinha *cozinha);
void atualizarCozinha(Cozinha *cozinha, float dt);
void desenharCozinha(Cozinha *cozinha);

#endif