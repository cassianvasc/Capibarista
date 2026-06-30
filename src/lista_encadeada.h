#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H
#include "cliente.h"

void inserirClienteFinal(Cliente **lista, Cliente *novo);

void removerClientePrimeiro(Cliente **lista);

void removerClienteEspecifico(Cliente **lista, Cliente *clienteRemover);

void removerClientesSemPaciencia(Cliente **lista, int *dinheiro, char aviso[], float *tempoAviso);

int contarClientes(Cliente *lista);

void liberarLista(Cliente **lista);

#endif