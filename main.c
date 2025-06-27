//main.c
// AUTOR: FELYPPE MARCELO DA SILVA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chamadas.h"
#include "atendimento.h"
#include "historico.h"

void limparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Fila alta, media, baixa;
    InicializarFila(&alta);
    InicializarFila(&media);
    InicializarFila(&baixa);

    Estatisticas est;
    HistNo* historico;

    inicializarAtendimento(&est, &historico);

    int opcao;
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

                InserirChamada(&alta, &media, &baixa, dados);
                printf("\n✅ Chamada adicionada com sucesso!\n\n");
                break;
            }

            case 2:
                ExibirFila(&alta, PRIORIDADE_ALTA);
                ExibirFila(&media, PRIORIDADE_MEDIA);
                ExibirFila(&baixa, PRIORIDADE_BAIXA);
                printf("\n");
                break;

            case 3:
                atenderProximaChamada(&alta, &media, &baixa, &historico, &est);
                break;

            case 4:
                exibirHistorico(historico);
                break;

            case 5:
                gerarRelatorio(&est, historico);
                liberarHistorico(&historico); // evita vazamento de memória
                break;

            default:
                printf("\n❌ Opcao invalida! Tente novamente.\n\n");
        }
    } while (opcao != 5);

    return 0;
}
