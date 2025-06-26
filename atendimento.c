// atendimento.c
// AUTOR: Thiago Tanaka Peczek
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "atendimento.h"

// Desenfileira a próxima chamada pela ordem de prioridade:
// A função tenta remover da fila de prioridade alta;
// se estiver vazia, tenta da fila de prioridade média;
// se também estiver vazia, tenta da fila de prioridade baixa;
// se todas estiverem vazias, retorna NULL.
static Chamada* desenfileirarPrioridade(Fila* alta, Fila* media, Fila* baixa) {
    if (!FilaVazia(alta)) {
        Chamada* c = alta->frente;
        alta->frente = c->prox;
        if (!alta->frente) alta->tras = NULL;
        return c;
    }
    if (!FilaVazia(media)) {
        Chamada* c = media->frente;
        media->frente = c->prox;
        if (!media->frente) media->tras = NULL;
        return c;
    }
    if (!FilaVazia(baixa)) {
        Chamada* c = baixa->frente;
        baixa->frente = c->prox;
        if (!baixa->frente) baixa->tras = NULL;
        return c;
    }
    return NULL;
}

// Inicializa todas as estatistícas de atendimento zerando os contadores e somas
// prepara a pilha de histórico definindo o topo como NULL
// cria uma seed para o rand()
void inicializarAtendimento(Estatisticas* est, HistNo** topo) {
    est->countAlta = est->sumEsperaAlta = 0;
    est->countMedia = est->sumEsperaMedia = 0;
    est->countBaixa = est->sumEsperaBaixa = 0;
    *topo = NULL;

    srand((unsigned)time(NULL));
}

// Chama a função de desenfileirarPrioridade, retirando algum valor da fila
// se não houver valores, retorna
// gera um numero aleatório para o tempo de atendimento
// empilha a chamada e o tempo de espera no histórico
// incrementa o contador de atendimentos da fila de prioridade
void atenderProximaChamada(Fila* alta, Fila* media, Fila* baixa, HistNo** topo, Estatisticas* est) {
    Chamada* c = desenfileirarPrioridade(alta, media, baixa);
    if (!c) {
        printf("\nNenhuma chamada na fila para atendimento.\n\n");
        return;
    }

    // simular tempo de espera entre 1 e 10
    int espera = rand() % 10 + 1;
    printf("\nAtendendo %s (prioridade %d). Tempo de espera simulado: %d minutos.\n\n", c->nome, c->prioridade, espera);

    // empilhar no histórico
    HistNo* no = malloc(sizeof(HistNo));
    no->chamada    = c;
    no->tempoEspera= espera;
    no->prox       = *topo;
    *topo          = no;

    // atualizar estatísticas
    switch (c->prioridade) {
      case PRIORIDADE_ALTA:
        est->countAlta++;
        est->sumEsperaAlta += espera;
        break;
      case PRIORIDADE_MEDIA:
        est->countMedia++;
        est->sumEsperaMedia += espera;
        break;
      case PRIORIDADE_BAIXA:
      default:
        est->countBaixa++;
        est->sumEsperaBaixa += espera;
        break;
    }
}

// Mostra a soma de todos os atendimentos e tempos de espera
void gerarRelatorio(Estatisticas* est, HistNo* topo) {
    printf("\n========= Relatorio Final =========\n");
    int total = est->countAlta + est->countMedia + est->countBaixa;
    printf("Total de atendimentos: %d\n", total);
    if (est->countAlta)
        printf("  Alta   : %d chamadas (media espera: %.1f min)\n",
               est->countAlta,
               (double)est->sumEsperaAlta / est->countAlta);
    if (est->countMedia)
        printf("  Media  : %d chamadas (media espera: %.1f min)\n",
               est->countMedia,
               (double)est->sumEsperaMedia / est->countMedia);
    if (est->countBaixa)
        printf("  Baixa  : %d chamadas (media espera: %.1f min)\n",
               est->countBaixa,
               (double)est->sumEsperaBaixa / est->countBaixa);

    printf("\nClientes atendidos:\n");
    for (HistNo* p = topo; p; p = p->prox) {
        printf("  - %s\n", p->chamada->nome);
    }
    printf("=====================================\n\n");
}