#ifndef COMUM_H
#define COMUM_H

#include "raylib.h"
#include "cozinha.h"
#include <stdbool.h>

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



typedef struct Pedido{ 
    bool cafe;
    bool tapioca;
    bool bolo;
    SaborBolo saborBolo;
} Pedido;


#endif