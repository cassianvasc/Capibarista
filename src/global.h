#ifndef COMUM_H
#define COMUM_H

#include "raylib.h"
#include <stdbool.h>

#define LARGURA_TELA 1000
#define ALTURA_TELA 600

#define TAM_NOME 32
#define DURACAO_TURNO 90.0f
#define META_DINHEIRO 150

typedef enum TelaJogo{
    TELA_MENU,
    TELA_NOME,
    TELA_JOGO,
    TELA_RANKING,
    TELA_FIM
} TelaJogo;

typedef enum SaborBolo{
    BOLO_NENHUM,
    BOLO_GOIABADA,
    BOLO_CHOCOLATE
} SaborBolo;

typedef struct Pedido{ 
    bool cafe;
    bool tapioca;
    bool bolo;
    SaborBolo saborBolo;
} Pedido;

#endif