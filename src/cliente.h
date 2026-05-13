#ifndef CLIENTE_H
#define CLIENTE_H

#include "global.h"

typedef struct Cliente{
    Pedido pedido;
    int id;

    float pacienciaMaxima;
    float pacienciaAtual;
    float valorBase; //pagamento sem a gorjeta

    struct Cliente *prox;
}Cliente;

Cliente criarCliente(int id);

const char *nomeSaborBolo(SaborBolo sabor); //função para transformar o enum em texto para escrever na dela

#endif