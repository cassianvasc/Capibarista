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

void removerClientesSemPaciencia(Cliente **lista){
    if(*lista == NULL){
        return;
    }
    //caso a remoçao seja no head
    while(*lista != NULL && (*lista)->pacienciaAtual <= 0){
        Cliente *remover = *lista;
        *lista = (*lista)->prox;
        free(remover);
    }
    //caso a remoçao seja no meio ou tail
    Cliente *atual = *lista;
    while(atual->prox != NULL){
        if(atual->prox->pacienciaAtual <= 0){
            Cliente *remover = atual->prox;
            atual->prox = remover->prox;
            free(remover);
        }
        else{
            atual = atual->prox;
        }
    }
}

void liberarLista(Cliente **lista){
    while(*lista != NULL){
        removerClientePrimeiro(lista);
    }
}
