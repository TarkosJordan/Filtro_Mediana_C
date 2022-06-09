#include <stdio.h>
#include <stdlib.h>
#include ".\Types.h"
#include ".\matlib.c"

PIXEL calculaMedianaDoVetorDePixels(PIXEL*vetorPixels, int tamanhoVetor);
void copiaMatrizPixels(PIXEL**matrizCopiada, PIXEL**matrizCopia, int linhasMatriz, int colunasMatriz);

// Essa funcao ira substituir elemento a elemento da matriz pela mediana dos valores vizinhos em um dado tamanho de filtro
void matrizMediana(PIXEL**matriz, int linhasMatriz, int colunasMatriz, int tamanhoMatrizFiltro);