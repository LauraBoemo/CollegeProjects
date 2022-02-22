#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PALAVRAS 16734

typedef struct {
    char sem_acento[5];
    char com_acento[10];
    bool usada;
} palavra_t;

palavra_t lista_de_palavras[NUM_PALAVRAS];

bool le_palavra(FILE *arquivo, palavra_t *p) {
    char palavraAux[4];
    
    while(!feof(arquivo)) {
        fscanf(arquivo, "%s", palavraAux);
        
        for(int i = 0; i < 15; i++){
            if(i < 5) {
                p -> sem_acento[i] = palavraAux[i];
            } else {
                if(palavraAux[i] >= 'a' && palavraAux[i] <= 'z') {
                    p -> com_acento[i] = palavraAux[i];
                    p -> com_acento[i + 1] = 0;
                } else {
                    p -> com_acento[i] = palavraAux[i];
                }
            }
        }
    }
    
    return true;
}

bool grava_palavra(FILE *arquivo, palavra_t *p) {
    for(int i = 0; i < NUM_PALAVRAS; i++){
        fprintf(arquivo, "%c %c", p -> sem_acento[i],  p -> com_acento[i]);
        if(feof(arquivo)){
            break;
        }
    }
    return true;
}

int main() {
    FILE *entrada;
    FILE *saida;
    entrada = fopen("palavras.txt", "r");
    // saida = fopen("copia-das-palavras", "w");
    // || saida == NUL
    if (entrada == NULL) {
        printf("Erro no acesso aos arquivos.\n");
        exit(1);
    }
    
    palavra_t palavra;
    
    while (le_palavra(entrada, &palavra)) {
        if (!grava_palavra(saida, &palavra)) {
            printf("problema na gravação.\n");
            break;
        }
    }

    fclose(entrada);
    // fclose(saida);
    return 0;
}