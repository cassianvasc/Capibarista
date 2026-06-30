#ifndef COMUM_H
#define COMUM_H

#include "raylib.h"
#include <stdbool.h>

#define TAM_NOME 11
#define DURACAO_TURNO 90.0f
#define META_DINHEIRO 150
#define MAX_CLIENTES_TELA 3

typedef enum TelaJogo{
    TELA_MENU,
    TELA_NOME,
    TELA_JOGO,
    TELA_RANKING,
    TELA_FIM,
    TELA_CREDITOS
} TelaJogo;

typedef enum SaborBolo{
    BOLO_NENHUM,
    BOLO_GOIABADA,
    BOLO_CHOCOLATE
} SaborBolo;

typedef enum EstadoTapioca {
    TAPIOCA_VAZIA,
    TAPIOCA_CRUA,
    TAPIOCA_NO_PONTO,
    TAPIOCA_QUEIMADA
} EstadoTapioca;

typedef enum EstadoForno {
    FORNO_VAZIO,
    BOLO_ASSANDO,      
    BOLO_PRONTO,     
    BOLO_QUEIMADO     
} EstadoForno;

typedef enum EstadoCafe{
    CAFE_MAQUINA_VAZIA,
    CAFE_PREPARANDO,
    CAFE_PRONTO
} EstadoCafe;

typedef struct Pedido{ 
    bool cafe;
    bool tapioca;
    bool bolo;
    SaborBolo saborBolo;
} Pedido;

#endif