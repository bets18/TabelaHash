// Rafaela Bessa || 2420043 
// Pedro Loschi || 
#include <stdio.h>
#include <stdlib.h>

// foi pedido o primeiro primo depois de 1200 (1000 chaves + 20% de folga)
#define TAMANHO_TABELA 1201

// constante para melhorar o espalhamento (sugestao dos slides)
#define K 31 

// metodo da divisao que deu o melhor resultado
// a primeira versao que fizemos sem usar a constante K deu 30 colisoes a mais 
int hash_principal(long long cpf) {
    return (cpf * K) % TAMANHO_TABELA;
}

// essa aqui e pro passo do duplo hash, o +1 garante que o passo nunca e zero
int hash_secundaria(long long cpf) {
    return 1 + (cpf % (TAMANHO_TABELA - 1));
}

// limpando a tabela antes de usar para evitar lixo de memoria
// testamos sem essa função e da errado
void inicializar_tabela(long long tabela[]) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        tabela[i] = 0;
    }
}

// funcao para inserir cada cpf na tabela
void inserir(long long tabela[], long long cpf, int* conta_colisoes) {
    int pos_inicial = hash_principal(cpf);
    int pos = pos_inicial;
    int passo = hash_secundaria(cpf);
    int i = 0;

    // se a posicao nao for 0, deu colisao. procuro a proxima
    while (tabela[pos] != 0) {
        (*conta_colisoes)++; 
        i++;
        // essa e a formula do duplo hash dos slides pra achar a proxima posicao
        pos = (pos_inicial + i * passo) % TAMANHO_TABELA; 
    }

    tabela[pos] = cpf;
}

int main() {
    long long tabela[TAMANHO_TABELA];
    inicializar_tabela(tabela);

    FILE *arq = fopen("cpfs.txt", "r"); 
    if (arq == NULL) {
        printf("Erro ao abrir o arq 'cpfs.txt'");
        return 1;
    }

    long long cpf_atual;
    int conta_chaves = 0;
    int colisoes_totais = 0;

    printf("Chaves Inseridas X Colisões\n\n");

    // le o arquivo de cpfs linha por linha
    while (fscanf(arq, "%lld", &cpf_atual) == 1) {
        conta_chaves++;
        inserir(tabela, cpf_atual, &colisoes_totais);

        // o trabalho pede pra mostrar o resultado a cada 100 chaves
        if (conta_chaves % 100 == 0) {
            printf("Chaves Inseridas: %-4d | Total de Colisões: %d\n", conta_chaves, colisoes_totais);
        }
    }
    
    fclose(arq);
    return 0;
}