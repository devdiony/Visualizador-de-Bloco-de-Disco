#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BLOCK_SIZE 4096

// Função auxiliar para imprimir uma linha no formato solicitado
void imprimir_linha(unsigned char* buffer, int tamanho, int offset_base) {
    // 1. Imprime o offset (endereço) da linha
    printf("%08X: ", offset_base);

    // 2. Imprime os bytes em hexadecimal
    for (int i = 0; i < 16; i++) {
        if (i < tamanho) {
            printf("%02X ", buffer[i]);
        } else {
            printf("   "); // Espaço para bytes que não existem (final do bloco)
        }
        if (i == 7) {
            printf(" "); // Espaço extra no meio para legibilidade
        }
    }
    printf("|");

    // 3. Imprime a representação ASCII
    for (int i = 0; i < 16; i++) {
        if (i < tamanho) {
            // Usa isprint() para verificar se o caractere é imprimível
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // --- 1. Validação dos Argumentos de Entrada ---
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <caminho_do_disco> <indice_do_bloco>\n", argv[0]);
        return 1;
    }

    char *caminho_arquivo = argv[1];
    int indice_bloco = atoi(argv[2]); // Converte o argumento string para inteiro

    if (indice_bloco < 0) {
        fprintf(stderr, "Erro: O indice do bloco nao pode ser negativo.\n");
        return 1;
    }

    // --- 2. Abertura e Posicionamento no Arquivo ---
    FILE *arquivo = fopen(caminho_arquivo, "rb"); // "rb" = read binary
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Calcula a posição do início do bloco desejado
    long offset = (long)indice_bloco * BLOCK_SIZE;

    // Posiciona o ponteiro do arquivo no início do bloco
    if (fseek(arquivo, offset, SEEK_SET) != 0) {
        // fseek pode falhar se o offset for além do final do arquivo,
        // mas vamos tratar isso na leitura para preencher com zeros.
        // Um erro aqui seria algo mais sério.
        perror("Erro ao posicionar no arquivo com fseek");
        fclose(arquivo);
        return 1;
    }

    // --- 3. Leitura do Bloco de Dados ---
    unsigned char buffer[BLOCK_SIZE] = {0}; // Inicializa o buffer com zeros

    // Lê até BLOCK_SIZE bytes do arquivo para o buffer.
    // A função fread retorna o número de itens lidos com sucesso.
    size_t bytes_lidos = fread(buffer, 1, BLOCK_SIZE, arquivo);

    // fread não diferencia fim de arquivo de erro, mas para este caso,
    // o comportamento é o desejado: o resto do buffer permanecerá com zeros.
    if (bytes_lidos < BLOCK_SIZE && ferror(arquivo)) {
        perror("Erro durante a leitura do arquivo");
    }

    fclose(arquivo); // Fecha o arquivo assim que a leitura termina

    // --- 4. Impressão Formatada do Conteúdo ---
    for (int i = 0; i < BLOCK_SIZE; i += 16) {
        int tamanho_linha = BLOCK_SIZE - i;
        if (tamanho_linha > 16) {
            tamanho_linha = 16;
        }
        imprimir_linha(&buffer[i], tamanho_linha, i);
    }

    return 0;
}
