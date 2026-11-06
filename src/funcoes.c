#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "funcoes.h"

void exibirMenu(void) {
    printf("\n========================================\n");
    printf("               QUIZ EM C                \n");
    printf("========================================\n");
    printf("1. Jogar\n");
    printf("2. Cadastrar Pergunta\n");
    printf("3. Listar Perguntas\n");
    printf("4. Exibir Ranking\n");
    printf("5. Estatisticas\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int carregarPerguntas(Pergunta perguntas[], int *totalPerguntas) {
    FILE *file = fopen("data/perguntas.txt", "r");
    if (file == NULL) {
        return 0;
    }

    *totalPerguntas = 0;
    while (*totalPerguntas < MAX_PERGUNTAS && 
           fscanf(file, " %[^;];%[^;];%[^;];%[^;];%[^;]; %c\n", 
                  perguntas[*totalPerguntas].enunciado, 
                  perguntas[*totalPerguntas].altA, 
                  perguntas[*totalPerguntas].altB, 
                  perguntas[*totalPerguntas].altC, 
                  perguntas[*totalPerguntas].altD, 
                  &perguntas[*totalPerguntas].respostaCorreta) == 6) {
        (*totalPerguntas)++;
    }

    fclose(file);
    return 1;
}

void salvarPerguntaArquivo(Pergunta p) {
    FILE *file = fopen("data/perguntas.txt", "a");
    if (file == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo de perguntas para salvamento.\n");
        return;
    }

    fprintf(file, "%s;%s;%s;%s;%s;%c\n", 
            p.enunciado, p.altA, p.altB, p.altC, p.altD, p.respostaCorreta);

    fclose(file);
}

int carregarHistorico(Jogador jogadores[], int *totalJogadores) {
    FILE *file = fopen("data/historico.txt", "r");
    if (file == NULL) {
        return 0;
    }

    *totalJogadores = 0;
    while (*totalJogadores < MAX_JOGADORES && 
           fscanf(file, " %[^;];%d;%d;%f\n", 
                  jogadores[*totalJogadores].nome, 
                  &jogadores[*totalJogadores].acertos, 
                  &jogadores[*totalJogadores].totalPerguntas, 
                  &jogadores[*totalJogadores].percentual) == 4) {
        (*totalJogadores)++;
    }

    fclose(file);
    return 1;
}

void salvarHistoricoArquivo(Jogador j) {
    FILE *file = fopen("data/historico.txt", "a");
    if (file == NULL) {
        printf("\n[ERRO] Nao foi possivel abrir o arquivo de historico para salvamento.\n");
        return;
    }

    fprintf(file, "%s;%d;%d;%.2f\n", j.nome, j.acertos, j.totalPerguntas, j.percentual);

    fclose(file);
}

int cadastrarPergunta(Pergunta perguntas[], int totalPerguntas) {
    if (totalPerguntas >= MAX_PERGUNTAS) {
        printf("\n[ERRO] Limite maximo de %d perguntas atingido!\n", MAX_PERGUNTAS);
        return totalPerguntas;
    }

    Pergunta novaP;

    printf("\n--- CADASTRO DA PERGUNTA %d ---\n", totalPerguntas + 1);

    printf("Digite o enunciado da pergunta: ");
    scanf(" %[^\n]", novaP.enunciado);

    printf("Digite a alternativa A: ");
    scanf(" %[^\n]", novaP.altA);

    printf("Digite a alternativa B: ");
    scanf(" %[^\n]", novaP.altB);

    printf("Digite a alternativa C: ");
    scanf(" %[^\n]", novaP.altC);

    printf("Digite a alternativa D: ");
    scanf(" %[^\n]", novaP.altD);

    do {
        printf("Digite a resposta correta (A, B, C ou D): ");
        scanf(" %c", &novaP.respostaCorreta);
        novaP.respostaCorreta = toupper(novaP.respostaCorreta);
    } while (novaP.respostaCorreta != 'A' && 
             novaP.respostaCorreta != 'B' && 
             novaP.respostaCorreta != 'C' && 
             novaP.respostaCorreta != 'D');

    perguntas[totalPerguntas] = novaP;
    salvarPerguntaArquivo(novaP);

    printf("\nPergunta cadastrada e salva com sucesso!\n");
    return totalPerguntas + 1;
}

void listarPerguntas(Pergunta perguntas[], int totalPerguntas) {
    int i;

    if (totalPerguntas == 0) {
        printf("\nNenhuma pergunta cadastrada ate o momento.\n");
        return;
    }

    printf("\n========================================\n");
    printf("         PERGUNTAS CADASTRADAS          \n");
    printf("========================================\n");

    for (i = 0; i < totalPerguntas; i++) {
        printf("\n[%d] PERGUNTA: %s\n", i + 1, perguntas[i].enunciado);
        printf("A) %s\n", perguntas[i].altA);
        printf("B) %s\n", perguntas[i].altB);
        printf("C) %s\n", perguntas[i].altC);
        printf("D) %s\n", perguntas[i].altD);
        printf("Resposta Correta: %c\n", perguntas[i].respostaCorreta);
        printf("----------------------------------------\n");
    }
}

int jogar(Pergunta perguntas[], int totalPerguntas, Jogador *jPartida) {
    int i;
    int acertos = 0;
    char respostaJogador;

    if (totalPerguntas == 0) {
        printf("\nNao ha perguntas cadastradas para jogar! Cadastre ao menos uma.\n");
        return 0;
    }

    printf("\nDigite o seu nome para o historico: ");
    scanf(" %[^\n]", jPartida->nome);

    printf("\n========================================\n");
    printf("            INICIANDO O QUIZ            \n");
    printf("========================================\n");

    for (i = 0; i < totalPerguntas; i++) {
        printf("\n--- PERGUNTA %d de %d ---\n", i + 1, totalPerguntas);
        printf("%s\n", perguntas[i].enunciado);
        printf("A) %s\n", perguntas[i].altA);
        printf("B) %s\n", perguntas[i].altB);
        printf("C) %s\n", perguntas[i].altC);
        printf("D) %s\n", perguntas[i].altD);

        do {
            printf("Sua resposta (A, B, C ou D): ");
            scanf(" %c", &respostaJogador);
            respostaJogador = toupper(respostaJogador);
        } while (respostaJogador != 'A' && respostaJogador != 'B' && 
                 respostaJogador != 'C' && respostaJogador != 'D');

        if (respostaJogador == perguntas[i].respostaCorreta) {
            printf("Resposta Correta!\n");
            acertos++;
        } else {
            printf("Resposta Incorreta! A correta era %c.\n", perguntas[i].respostaCorreta);
        }
    }

    jPartida->acertos = acertos;
    jPartida->totalPerguntas = totalPerguntas;
    jPartida->percentual = ((float)acertos / totalPerguntas) * 100;

    salvarHistoricoArquivo(*jPartida);

    printf("\n========================================\n");
    printf("FIM DA PARTIDA!\n");
    printf("Jogador: %s\n", jPartida->nome);
    printf("Voce acertou %d de %d pergunta(s).\n", acertos, totalPerguntas);
    printf("Aproveitamento: %.2f%%\n", jPartida->percentual);
    printf("========================================\n");

    return acertos;
}

void ordenarRanking(Jogador jogadores[], int totalJogadores) {
    int i, j;
    Jogador temp;

    for (i = 0; i < totalJogadores - 1; i++) {
        for (j = 0; j < totalJogadores - i - 1; j++) {
            if (jogadores[j].percentual < jogadores[j + 1].percentual) {
                temp = jogadores[j];
                jogadores[j] = jogadores[j + 1];
                jogadores[j + 1] = temp;
            }
        }
    }
}

void exibirRanking(Jogador jogadores[], int totalJogadores) {
    int i;

    if (totalJogadores == 0) {
        printf("\nNenhum historico de partida registrado ainda.\n");
        return;
    }

    ordenarRanking(jogadores, totalJogadores);

    printf("\n========================================\n");
    printf("          RANKING DE JOGADORES          \n");
    printf("========================================\n");
    for (i = 0; i < totalJogadores; i++) {
        printf("%d. Nome: %s | Acertos: %d/%d | Percentual: %.2f%%\n", 
               i + 1, jogadores[i].nome, jogadores[i].acertos, 
               jogadores[i].totalPerguntas, jogadores[i].percentual);
    }
    printf("========================================\n");
}

float calcularMediaHistorico(Jogador jogadores[], int totalJogadores) {
    int i;
    float soma = 0;
    if (totalJogadores == 0) return 0.0;
    for (i = 0; i < totalJogadores; i++) {
        soma += jogadores[i].acertos;
    }
    return soma / totalJogadores;
}

void exibirEstatisticas(int totalPerguntas, int totalJogadores, int somaPontuacoes) {
    printf("\n========================================\n");
    printf("         ESTATISTICAS DO SISTEMA        \n");
    printf("========================================\n");
    printf("Total de perguntas cadastradas: %d\n", totalPerguntas);
    printf("Total de partidas jogadas: %d\n", totalJogadores);
    if (totalJogadores > 0) {
        float media = (float)somaPontuacoes / totalJogadores;
        printf("Pontuacao media por partida: %.2f acerto(s)\n", media);
    } else {
        printf("Pontuacao media por partida: 0.00 acerto(s)\n");
    }
    printf("========================================\n");
}
