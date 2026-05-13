#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H
#include "cliente.h"

void InserirClienteFinal(Cliente **lista, Cliente *novo);

void *RemoverClientePrimeiro(Cliente **lista);

void LiberarLista(Cliente **lista);

#endif