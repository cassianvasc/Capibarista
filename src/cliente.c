#include "cliente.h"
#include <stdlib.h>

const char *nomeSaborBolo(SaborBolo sabor){
    if(sabor == BOLO_GOIABADA) return "goiabada";
    else if(sabor == BOLO_CHOCOLATE) return "chocolate";
    else return "nenhum";
}

Cliente *criarCliente(int id){
    //alocar o espaço pro cliente novo
    Cliente *novo = malloc(sizeof(Cliente));
    if (novo == NULL) return NULL;

    //preencher os campos do nó
    novo->id = id;

    novo->pedido.cafe = GetRandomValue(0,1); //como os itens sao booleanos, 0 significa que nao esta no pedido e 1 significa que esta
    novo->pedido.tapioca = GetRandomValue(0,1);
    novo->pedido.bolo = GetRandomValue(0,1);

    //se o cliente for gerado sem nenhum pedido ele é obrigado a pedir um item:
    if(novo->pedido.cafe == false && novo->pedido.tapioca == false && novo->pedido.bolo == false){
        int item = GetRandomValue(0,2);
        if(item ==0){
            novo->pedido.cafe = true;
        }
        else if(item == 1){
            novo->pedido.tapioca = true;
        }
        else{
            novo->pedido.bolo = true;
        }
    }
    
    //definindo o sabor do bolo
    if(novo->pedido.bolo == true){
        int sabor = GetRandomValue(0,1);
        if(sabor == 0){
            novo->pedido.saborBolo = BOLO_GOIABADA;
        }
        else{
            novo->pedido.saborBolo = BOLO_CHOCOLATE;
        }
    }
    else {
        novo->pedido.saborBolo = BOLO_NENHUM;
    }

    novo->pacienciaAtual = 25.0f;
    novo->pacienciaMaxima = 25.0f;

    novo->valorBase = 0;

    //definindo os valores dos itens
    if(novo->pedido.cafe){
        novo->valorBase += 5;
    }
    if(novo->pedido.tapioca){
        novo->valorBase += 15;
    }
    if(novo->pedido.bolo){
        novo->valorBase += 10;
    }

    novo->prox = NULL;
    return novo;
}