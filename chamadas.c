


// chamadas.c
//AUTOR: HENRIQUE MENESES DOS SANTOS CORREA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chamadas.h"

void InicializarFila(Fila* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

Chamada* CriarChamada(DadosChamada dados) {
    Chamada* nova = (Chamada*)malloc(sizeof(Chamada));
    if (!nova) return NULL;

    strcpy(nova->nome, dados.nome);
    strcpy(nova->motivo, dados.motivo);
    nova->prioridade = dados.prioridade;
    nova->prox = NULL;
    return nova;
}

void InserirChamada(Fila* alta, Fila* media, Fila* baixa, DadosChamada dados) {
    Chamada* nova = CriarChamada(dados);
    if (!nova) return;

    Fila* fila_destino;
    switch (dados.prioridade) {
        case PRIORIDADE_ALTA:
            fila_destino = alta;
            break;
        case PRIORIDADE_MEDIA:
            fila_destino = media;
            break;
        case PRIORIDADE_BAIXA:
        default:
            fila_destino = baixa;
            break;
    }

    if (fila_destino->tras) {
        fila_destino->tras->prox = nova;
    } else {
        fila_destino->frente = nova;
    }
    fila_destino->tras = nova;
}

void ExibirFila(Fila* fila, int prioridade) {
    const char* desc;
    switch (prioridade) {
        case PRIORIDADE_ALTA: desc = "Alta"; break;
        case PRIORIDADE_MEDIA: desc = "Média"; break;
        case PRIORIDADE_BAIXA: desc = "Baixa"; break;
        default: desc = "Desconhecida";
    }
    printf("\nFila de prioridade %s:\n", desc);
    Chamada* atual = fila->frente;
    while (atual) {
        printf("Cliente: %s | Motivo: %s\n", atual->nome, atual->motivo);
        atual = atual->prox;
    }
    if (!fila->frente) {
        printf("[Vazia]\n");
    }
}

int FilaVazia(Fila* fila) {
    return fila->frente == NULL;
}


