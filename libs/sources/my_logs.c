#include<stdio.h>

void printMatriz(int**matriz, int linhas, int colunas){
    int i, j;

    for(i=0; i<linhas; i++){
        for(j=0; j<colunas; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}

void printMatrizQuadrada(int**matriz, int dimensaoMatriz){
    int i, j;

    for(i=0; i<dimensaoMatriz; i++){
        for(j=0; j<dimensaoMatriz; j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}

void printVetor(int*vetor, int tamanhoVetor){
    int i;
    for(i=0; i<tamanhoVetor; i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
}