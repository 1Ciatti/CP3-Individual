#include <stdio.h>
#include "funcoes.h"

int main() {
    Pergunta perguntas[MAX_PERGUNTAS];
    Jogador jogadores[MAX_JOGADORES];

    int totalPerguntas = 0;
    int totalJogadores = 0;
    int somaPontuacoes = 0;
    int opcao;
    int i;

    carregarPerguntas(perguntas, &totalPerguntas);
    carregarHistorico(jogadores, &totalJogadores);

    for (i = 0; i < totalJogadores; i++) {
        somaPontuacoes += jogadores[i].acertos;
    }

    do {
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida! Por favor, digite um numero.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1: {
                Jogador novaPartida;
                int acertosPartida = jogar(perguntas, totalPerguntas, &novaPartida);
                if (totalPerguntas > 0) {
                    somaPontuacoes += acertosPartida;
                    if (totalJogadores < MAX_JOGADORES) {
                        jogadores[totalJogadores] = novaPartida;
                        totalJogadores++;
                    }
                }
                break;
            }
            case 2:
                totalPerguntas = cadastrarPergunta(perguntas, totalPerguntas);
                break;
            case 3:
                listarPerguntas(perguntas, totalPerguntas);
                break;
            case 4:
                exibirRanking(jogadores, totalJogadores);
                break;
            case 5:
                exibirEstatisticas(totalPerguntas, totalJogadores, somaPontuacoes);
                break;
            case 0:
                printf("\nSaindo do programa... Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Escolha um numero entre 0 e 5.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
