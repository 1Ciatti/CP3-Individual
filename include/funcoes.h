#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_PERGUNTAS 50
#define MAX_JOGADORES 100

typedef struct {
    char enunciado[200];
    char altA[100];
    char altB[100];
    char altC[100];
    char altD[100];
    char respostaCorreta;
} Pergunta;

typedef struct {
    char nome[50];
    int acertos;
    int totalPerguntas;
    float percentual;
} Jogador;

void exibirMenu(void);
int carregarPerguntas(Pergunta perguntas[], int *totalPerguntas);
void salvarPerguntaArquivo(Pergunta p);
int carregarHistorico(Jogador jogadores[], int *totalJogadores);
void salvarHistoricoArquivo(Jogador j);
int cadastrarPergunta(Pergunta perguntas[], int totalPerguntas);
void listarPerguntas(Pergunta perguntas[], int totalPerguntas);
int jogar(Pergunta perguntas[], int totalPerguntas, Jogador *jPartida);
void ordenarRanking(Jogador jogadores[], int totalJogadores);
void exibirRanking(Jogador jogadores[], int totalJogadores);
void exibirEstatisticas(int totalPerguntas, int totalPartidas, int somaPontuacoes);

#endif
