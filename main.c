//main.c
// AUTOR: FELYPPE MARCELO DA SILVA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chamadas.h"
#include "atendimento.h"
#include "historico.h"

// limpa o buffer do teclado
void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
// inicializa as filas de prioridade
    Fila alta, media, baixa;
    InicializarFila(&alta);
    InicializarFila(&media);
    InicializarFila(&baixa);

// inicializa estatisticas e historicos
    Estatisticas est;
    HistNo* historico;

    inicializarAtendimento(&est, &historico);

    int opcao;
// mostra o menu por loop para não ficar fechando o sistema
    do {
        printf("========== MENU ==========\n");
        printf("1. Adicionar nova chamada\n");
        printf("2. Visualizar filas\n");
        printf("3. Atender proxima chamada\n");
        printf("4. Visualizar historico\n");
        printf("5. Gerar relatorio e sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparEntrada();

        switch (opcao) {
            // lê os dados da chamada
            case 1: {
                DadosChamada dados;
                printf("\nDigite o nome do cliente: ");
                fgets(dados.nome, MAX_NOME, stdin);
                dados.nome[strcspn(dados.nome, "\n")] = '\0';

                printf("Digite o motivo da ligacao: ");
                fgets(dados.motivo, MAX_MOTIVO, stdin);
                dados.motivo[strcspn(dados.motivo, "\n")] = '\0';

                printf("Prioridade (1 = alta, 2 = media, 3 = baixa): ");
                scanf("%d", &dados.prioridade);
                limparEntrada();

                // insere na fila correta
                InserirChamada(&alta, &media, &baixa, dados);
                printf("\n✅ Chamada adicionada com sucesso!\n\n");
                break;
            }

            case 2:
            // mostra as chamadas em cada fila
                ExibirFila(&alta, PRIORIDADE_ALTA);
                ExibirFila(&media, PRIORIDADE_MEDIA);
                ExibirFila(&baixa, PRIORIDADE_BAIXA);
                printf("\n");
                break;

            case 3:
            // atende a proxima chamada com base na prioridade
                atenderProximaChamada(&alta, &media, &baixa, &historico, &est);
                break;

            case 4:
            // exibe historico detalhado
                exibirHistorico(historico);
                break;

            case 5:
            // gera relatorio e libera memória
                gerarRelatorio(&est, historico);
                liberarHistorico(&historico); 
                break;

            default:
                printf("\n❌ Opcao invalida! Tente novamente.\n\n");
        }
    } while (opcao != 5);

    return 0;
}
