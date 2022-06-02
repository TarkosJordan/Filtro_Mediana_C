#include <stdio.h>
#include <stdlib.h>
#include ".\libs\headers\matlib.h"
#include ".\libs\headers\my_logs.h"

int main(int argc, char**argv){
    if(argc != 4){
        printf("Numero de parametros invalido para executar:\n %s <num_linhas> <num_colunas> <tam_filtro>\n", argv[0]);
        exit(0);
    }
    int linhasMatriz = atoi(argv[1]);
    int colunasMatriz = atoi(argv[2]);
    int tamanhoFiltro = atoi(argv[3]);

    int i, j;
    int medianaDaMatriz;
    int **matriz = (int**)malloc(linhasMatriz * sizeof(int*));
    for(i=0; i<linhasMatriz; i++){
        matriz[i] = (int*)malloc(colunasMatriz * sizeof(int));
    }
    printf("Insira os elementos da matriz de dimensao %dx%d\n", linhasMatriz, colunasMatriz);

    for(i = 0; i<linhasMatriz; i++){
        for(j = 0; j<colunasMatriz; j++){
            scanf("%d",&matriz[i][j]);
        }
    }

    printf("\nMatriz inserida:\n");

    printMatriz(matriz, linhasMatriz, colunasMatriz);

    matrizMediana(matriz, linhasMatriz, colunasMatriz, tamanhoFiltro);
    
    printf("\nMatriz Mediana Resultante:\n");
    
    printMatriz(matriz, linhasMatriz, colunasMatriz);

    return 0;
}