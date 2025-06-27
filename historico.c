// historico.h
// autoria de: Paulo Roberto Gomes Barroso Schiochet
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "historico.h"

//a parte de historico trabalha muito com pilhas, já que a intuitividade é pegar o que está em cima(o mais novo)
void inicializarHistorico(HistNo** topo) {
    *topo = NULL; //define o topo como nulo(vazio), o ponteiro duplo serve para alterar o valor do topo
}

void empilharHistorico(HistNo** topo, Chamada* chamada, int tempoEspera) {
    HistNo* novo = (HistNo*)malloc(sizeof(HistNo)); //cria no p/ pilha, e uma medida de segurança caso nao tenha input
    if (!novo) {
        printf("Erro: Nao foi possível alocar memoria para o historico!\n");
        return;
    }

    Chamada* chamadaCopia = (Chamada*)malloc(sizeof(Chamada));
    if (!chamadaCopia) { //faz uma alocacao p copia da chamada, e entao guarda uma copia no historico
        free(novo);
        printf("Erro: Nao foi possível alocar memoria para a chamada!\n");
        return;
    }

    strcpy(chamadaCopia->nome, chamada->nome);
    strcpy(chamadaCopia->motivo, chamada->motivo); //aqui ele copia todos os dados
    chamadaCopia->prioridade = chamada->prioridade;
    chamadaCopia->prox = NULL;

    novo->chamada = chamadaCopia; //novo no
    novo->tempoEspera = tempoEspera;
    novo->prox = *topo;

    *topo = novo; //configura novo nó, fazendo um last in first out
}

HistNo* desempilharHistorico(HistNo** topo) {
    if (*topo == NULL) {
        return NULL;
    } //remove o topo e retorna, mas só remove a pilha, nao libera a memoria

    HistNo* removido = *topo;
    *topo = (*topo)->prox;
    removido->prox = NULL;

    return removido;
}

void exibirHistorico(HistNo* topo) {
    printf("\n Histórico de Atendimentos: \n");
    
    if (historicoVazio(topo)) {
        printf("[Sem atendimentos realizados]\n\n");
        return;
    } //verificacao se ta vazio

    int contador = 1;
    HistNo* atual = topo;
    
    while (atual != NULL) { //conversor para legibilidade
        const char* prioridadeDesc;
        switch (atual->chamada->prioridade) {
            case PRIORIDADE_ALTA: prioridadeDesc = "Alta"; break;
            case PRIORIDADE_MEDIA: prioridadeDesc = "Média"; break;
            case PRIORIDADE_BAIXA: prioridadeDesc = "Baixa"; break;
            default: prioridadeDesc = "Desconhecida";
        }
        // em baixo, ele esta percorrendo toda a pilha
        printf("%d. Cliente: %s\n", contador, atual->chamada->nome);
        printf("   Motivo: %s\n", atual->chamada->motivo);
        printf("   Prioridade: %s\n", prioridadeDesc);
        printf("   Tempo de Espera: %d minutos\n", atual->tempoEspera);
        printf("   ----------------------------------------\n");
        
        atual = atual->prox;
        contador++; 
    } 
    printf("\n");
}

int historicoVazio(HistNo* topo) {
    return topo == NULL;
} //retorna se o topo for null, ou seja 1(true) ou 0(false)

int contarAtendimentos(HistNo* topo) { //percorre a pilha contando nós
    int contador = 0;
    HistNo* atual = topo;
    
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    
    return contador;
}

void liberarHistorico(HistNo** topo) { //vai liberar toda a memória da pilha
    HistNo* atual = *topo;
    HistNo* proximo;

    while (atual != NULL) {
        proximo = atual->prox;

        if (atual->chamada) {
            free(atual->chamada);
        } //libera
        
        free(atual);
        atual = proximo;
    }

    *topo = NULL; //define o topo como null
}
