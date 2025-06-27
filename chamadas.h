// chamadas.h
// AUTOR: HENRIQUE MENESES DOS SANTOS CORRÊa
#ifndef CHAMADAS_H
#define CHAMADAS_H

#define MAX_NOME 100
#define MAX_MOTIVO 200

#define PRIORIDADE_ALTA 1
#define PRIORIDADE_MEDIA 2
#define PRIORIDADE_BAIXA 3

// estrutura pra chamada
typedef struct Chamada {
    char nome[MAX_NOME];
    char motivo[MAX_MOTIVO];
    int prioridade;
    struct Chamada* prox;
} Chamada;

// define a fila de prioridade
typedef struct {
    Chamada* frente;
    Chamada* tras;
} Fila;

// inicializa uma fila definindo os ponteiros frente e tras como NULL, que significa que a fila esta vazia
void InicializarFila(Fila* fila);

// Criação de nova chamada
typedef struct {
    char nome[MAX_NOME];
    char motivo[MAX_MOTIVO];
    int prioridade;
} DadosChamada;

// cria uma nova estrutura Chamada com os dados do cliente (nome, motivo e prioridade), e retorna um ponteiro para essa nova chamada
Chamada* CriarChamada(DadosChamada dados);

// seleciona uma fila apropriada com base na prioridade, inserindo uma chamada no final da fila
void InserirChamada(Fila* alta, Fila* media, Fila* baixa, DadosChamada dados);

// percorre uma fila e imprime todas as suas chamadas com nome do cliente e motivo da ligaçao. Inclue uma verificaçao caso a fila esteja vazia
void ExibirFila(Fila* fila, int prioridade);

//  retorna 1 se a fila estiver vazia ou 0 caso nao
int FilaVazia(Fila* fila);

#endif