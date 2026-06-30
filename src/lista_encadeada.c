#include "cliente.h"
#include <stdlib.h>
#include <stdio.h>

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
    //caso a remoçao seja na head
    if(*lista == clienteRemover){
        Cliente *aux = *lista;
        *lista = (*lista)->prox;
        free(aux);
        return;
    }
    //senao procuro o anterior ao que sera removido, ligo ele o anterior ao proximo dele e removo ele
    Cliente *anterior = *lista;
    while(anterior->prox != NULL && anterior->prox != clienteRemover){
        anterior = anterior->prox;
    }
    if(anterior->prox == clienteRemover){
        anterior->prox = clienteRemover->prox;
        free(clienteRemover);
    }
}

void removerClientesSemPaciencia(Cliente **lista, int *dinheiro, char aviso[], float *tempoAviso){
    if(*lista == NULL){
        return;
    }
    //caso a remoçao seja no head
    while(*lista != NULL && (*lista)->pacienciaAtual <= 0){
        Cliente *remover = *lista;

        *dinheiro -= 15;

        sprintf(aviso, "Cliente foi embora! -R$ 15");
        *tempoAviso = 2.0f;

        *lista = (*lista)->prox;
        free(remover);
    }
    //caso a remoçao seja no meio ou tail
    Cliente *atual = *lista;
    while(atual->prox != NULL){
        if(atual->prox->pacienciaAtual <= 0){
            Cliente *remover = atual->prox;

            *dinheiro -= 15;

            sprintf(aviso, "Cliente foi embora! -R$ 15");
            *tempoAviso = 2.0f;

            atual->prox = remover->prox;
            free(remover);
        }
        else{
            atual = atual->prox;
        }
    }
}

int contarClientes(Cliente *lista){
    int total = 0;

    Cliente *aux = lista;

    while(aux != NULL){
        total++;
        aux = aux->prox;
    }

    return total;
}

void liberarLista(Cliente **lista){
    while(*lista != NULL){
        removerClientePrimeiro(lista);
    }
}
