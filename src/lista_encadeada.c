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

void liberarLista(Cliente **lista){
    while(*lista != NULL){
        removerClientePrimeiro(lista);
    }
}
