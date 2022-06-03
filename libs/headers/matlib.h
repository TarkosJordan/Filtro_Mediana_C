#include <stdio.h>
#include <stdlib.h>
#include "..\sources\matlib.c"

unsigned char *vetorizaMatrizQuadrada(unsigned char**matriz, int dimensaoMatriz);
unsigned char calculaMedianaDoVetor(unsigned char*vetor, int tamanhoVetor);
unsigned char calculaMedianaMatrizQuadrada(unsigned char**matriz, int dimensaoMatriz);
void copiaMatriz(unsigned char**matrizCopiada, unsigned char**matrizCopia, int linhasMatriz, int colunasMatriz);

// Essa funcao ira substituir elemento a elemento da matriz pela mediana dos valores vizinhos em um dado tamanho de filtro
void matrizMediana(unsigned char**matriz, int linhasMatriz, int colunasMatriz, int tamanhoMatrizFiltro);