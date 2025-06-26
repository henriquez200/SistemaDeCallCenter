// main.c
//AUTOR: FELYPPE MARCELO DA SILVA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chamadas.h"
#include "atendimento.h"

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
        printf("4. Gerar relatorio e sair\n");
        printf("==========================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparEntrada();

        if (opcao == 1) {
            DadosChamada dados;
            printf("\nDigite o nome do cliente: ");
            fgets(dados.nome, MAX_NOME, stdin);
            dados.nome[strcspn(dados.nome, "\n")] = '\0';  // remove \n

            printf("Digite o motivo da ligacao: ");
            fgets(dados.motivo, MAX_MOTIVO, stdin);
            dados.motivo[strcspn(dados.motivo, "\n")] = '\0';

            printf("Prioridade (1 = alta, 2 = media, 3 = baixa): ");
            scanf("%d", &dados.prioridade);
            limparEntrada();

            InserirChamada(&alta, &media, &baixa, dados);
            printf("\n✅ Chamada adicionada com sucesso!\n\n");

        } else if (opcao == 2) {
            ExibirFila(&alta, PRIORIDADE_ALTA);
            ExibirFila(&media, PRIORIDADE_MEDIA);
            ExibirFila(&baixa, PRIORIDADE_BAIXA);
            printf("\n");

        } else if (opcao == 3) {
            atenderProximaChamada(&alta, &media, &baixa, &historico, &est);

        } else if (opcao == 4) {
            gerarRelatorio(&est, historico);
            break;

        } else {
            printf("\n❌ Opcao invalida! Tente novamente.\n\n");
        }

    } while (1);

    return 0;
}
