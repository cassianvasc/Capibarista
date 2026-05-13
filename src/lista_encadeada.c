#include "cliente.h"
#include <stdlib.h>

void InserirClienteFinal(Cliente **lista, Cliente *novo){
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

void RemoverClientePrimeiro(Cliente **lista){
    if(*lista == NULL){
        return;
    }
    Cliente *aux = *lista;
    *lista = (*lista)->prox;
    free(aux);
}

void LiberarLista(Cliente **lista){
    while(*lista != NULL){
        RemoverClientePrimeiro(lista);
    }
}
