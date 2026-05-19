#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H
#include "cliente.h"

void inserirClienteFinal(Cliente **lista, Cliente *novo);

void removerClientePrimeiro(Cliente **lista);

void liberarLista(Cliente **lista);

#endif