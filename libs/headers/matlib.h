#include <stdio.h>
#include <stdlib.h>
#include "..\sources\matlib.c"

int *vetorizaMatrizQuadrada(int**matriz, int dimensaoMatriz);
int calculaMedianaDoVetor(int*vetor, int tamanhoVetor);
int calculaMedianaMatrizQuadrada(int**matriz, int dimensaoMatriz);
void copiaMatriz(int**matrizCopiada, int**matrizCopia, int linhasMatriz, int colunasMatriz);

// Essa funcao ira substituir elemento a elemento da matriz pela mediana dos valores vizinhos em um dado tamanho de filtro
void matrizMediana(int**matriz, int linhasMatriz, int colunasMatriz, int tamanhoMatrizFiltro);