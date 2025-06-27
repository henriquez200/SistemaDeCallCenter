// historico.h
// AUTOR: PAULO ROBERTO GOMES BARROSO SCHIOCHET 
#ifndef HISTORICO_H
#define HISTORICO_H

#include "chamadas.h"
//#include "atendimento.h"


//estrutura do no da pilha de histórico(a mesma que a do thiago)
typedef struct HistNo {
    Chamada* chamada;
    int tempoEspera;          //usei ela por medo de achar que ela poderia talvez interlapsar com a do tanaka, apesar dos ponteiros (uma maneira de otimizar é so incluir o atendimento.h junto com chamadas.h)
    struct HistNo* prox;
} HistNo;

//inicializar a pilha de histórico
void inicializarHistorico(HistNo** topo);

//empilha uma chamada atendida no historico com seu tempo de espera
void empilharHistorico(HistNo** topo, Chamada* chamada, int tempoEspera);

//desempilha e retorna o ultimo atendimento do histórico
HistNo* desempilharHistorico(HistNo** topo);

//vai exibir todo o historico de atendimentos (recentes ao mais antigos)
void exibirHistorico(HistNo* topo);

//verifica se a pilha de historico esta vazia
int historicoVazio(HistNo* topo);

//conta o número total de atendimentos no historico
int contarAtendimentos(HistNo* topo);

//libera toda a memoria alocada para a pilha de historico
void liberarHistorico(HistNo** topo);

#endif