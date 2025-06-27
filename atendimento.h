// atendimento.h
// AUTOR: THIAGO TANAKA PECZEK
#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H

#include "chamadas.h"   // para usar Fila, Chamada, DadosChamada
#include "historico.h"  // para usar HistNo e funções de histórico

// estruturas para acumular estatísticas
typedef struct {
    int countAlta, sumEsperaAlta;
    int countMedia, sumEsperaMedia;
    int countBaixa, sumEsperaBaixa;
} Estatisticas;

// inicializa pilha e dados
void inicializarAtendimento(Estatisticas* est, HistNo** topo);

// retira a próxima chamada de prioridade (alta > média > baixa),
// calcula um tempo de espera (simulado) e empilha no histórico
void atenderProximaChamada(Fila* alta, Fila* media, Fila* baixa, HistNo** topo, Estatisticas* est);

// exibe relatório final baseado nas estatísticas
void gerarRelatorio(Estatisticas* est, HistNo* topo);

#endif
