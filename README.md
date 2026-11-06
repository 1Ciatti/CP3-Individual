# Quiz em C - Checkpoint Final (CP3)

Projeto integrador desenvolvido para a disciplina de Computational Thinking em C, englobando structs, manipulação de arquivos texto, passagem de vetores e ordenação por Bubble Sort[cite: 5, 8].

## Link do Vídeo de Demonstração
[Link do Vídeo no YouTube (Não-listado)](https://seu-link-do-video-aqui)

## Estrutura do Projeto
- `src/main.c`: Ponto de entrada, menu interativo e gerenciamento de carregamento inicial.
- `src/funcoes.c`: Implementação das structs, persistência de arquivos, lógica do quiz, estatísticas e ordenação (Bubble Sort).
- `include/funcoes.h`: Definições das estruturas (`Pergunta` e `Jogador`), macros e protótipos de funções.
- `data/perguntas.txt`: Arquivo de persistência das perguntas cadastradas.
- `data/historico.txt`: Arquivo de persistência do histórico e ranking dos jogadores.
- `README.md`: Documentação e instruções de compilação.

## Como Compilar
No terminal, dentro da raiz do projeto (`meu-projeto-c/`), execute o comando de compilação com inclusão da pasta include[cite: 8]:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c -o programa
