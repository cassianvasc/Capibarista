#include "cliente.h"
#include <stdlib.h>

void inserirClienteFinal(Cliente **lista, Cliente *novo){
    if(novo == NULL){
        return;
    }
    if(*lista == NULL){
        *lista = novo;
        return;
    }
    Cliente *aux = *lista;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
}

void removerClientePrimeiro(Cliente **lista){
    if(*lista == NULL){
        return;
    }
    Cliente *aux = *lista;
    *lista = (*lista)->prox;
    free(aux);
}

void removerClienteEspecifico(Cliente **lista, Cliente *clienteRemover){

    if(*lista == NULL || clienteRemover == NULL){
        return;
    }
    if(*lista == clienteRemover){
        Cliente *aux = *lista;
        *lista = (*lista)->prox;
        free(aux);
        return;
    }
    Cliente *anterior = *lista;
    while(
        anterior->prox != NULL &&
        anterior->prox != clienteRemover
    ){
        anterior = anterior->prox;
    }
    if(anterior->prox == clienteRemover){
        anterior->prox = clienteRemover->prox;
        free(clienteRemover);
    }
}

void liberarLista(Cliente **lista){
    while(*lista != NULL){
        removerClientePrimeiro(lista);
    }
}
