💾 blkdump - Visualizador de Blocos de Arquivo em C

📜 Visão Geral

blkdump é uma ferramenta de linha de comando desenvolvida em C como parte de um exercício para a disciplina de Sistemas Operacionais. O programa lê um bloco específico de 4 KB de qualquer arquivo (simulando um "disco" binário) e exibe seu conteúdo nos formatos hexadecimal e ASCII.

Este projeto demonstra a manipulação de arquivos em baixo nível, o uso de ponteiros e a formatação de saída, conceitos fundamentais em sistemas operacionais.

✨ Funcionalidades

Leitura de blocos de dados de tamanho fixo (4096 bytes).

Posicionamento eficiente no arquivo utilizando fseek().

Saída formatada exibindo o offset, a representação hexadecimal e a representação ASCII de cada linha (16 bytes).

Tratamento robusto de erros para argumentos inválidos, arquivos inexistentes ou índices de bloco negativos.

🚀 Como Compilar e Executar

1. Pré-requisitos:

Um compilador C (como o GCC).

A ferramenta make.

2. Compilação:
No terminal, dentro da pasta do projeto, execute o comando:

make


Isso irá gerar o executável blkdump.

3. Execução:
O programa utiliza a seguinte sintaxe:

./blkdump <caminho_do_arquivo> <indice_do_bloco>


Exemplo: Para ler o primeiro bloco (índice 0) de um arquivo chamado disco.bin:

./blkdump disco.bin 0


📝 Exemplo de Saída

A saída do programa é formatada para exibir 16 bytes por linha, seguindo o padrão clássico de editores hexadecimais.

00000000: 4F 6C 61 2C 20 6D 75 6E  64 6F 21 20 45 73 74 65 |Ola, mundo! Este|
00000010: 20 65 20 75 6D 20 74 65  73 74 65 20 70 61 72 61 | e um teste para|
00000020: 20 6F 20 70 72 6F 67 72  61 6D 61 20 62 6C 6B 64 | o programa blkd|
00000030: 75 6D 70 2E 0D 0A                                 |ump...|
00000040: 00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00 |................|
... (restante do bloco preenchido com zeros) ...


🛠️ Tecnologias Utilizadas

Linguagem: C (Padrão C99)

Bibliotecas Padrão: stdio.h, stdlib.h, ctype.h

Build System: Makefile com GCC