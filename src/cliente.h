#ifndef CLIENTE_H
#define CLIENTE_H

#include "global.h"

typedef struct Cliente{
    Pedido pedido;
    int id;

    float pacienciaMaxima;
    float pacienciaAtual;

    struct Cliente *prox;
}Cliente;

Cliente *criarCliente(int id);

const char *nomeSaborBolo(SaborBolo sabor); //função para transformar o enum em texto para escrever na dela

int calcularGorjeta(Cliente *cliente);

#endif