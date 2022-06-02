#include<stdio.h>

int* vetorizaMatrizQuadrada(int**matriz, int dimensaoMatriz){
    int i, j, indiceVetor = 0;
    int tamanhoVetor = dimensaoMatriz*dimensaoMatriz;   
    int*vetorResultante = (int*)malloc(tamanhoVetor*sizeof(int));
    
    for(i = 0; i<dimensaoMatriz; i++){
        for(j = 0; j < dimensaoMatriz; j++){
            vetorResultante[indiceVetor] = matriz[i][j];
            indiceVetor++;
        }
    }
    return vetorResultante;
}

int calculaMedianaDoVetor(int*vetor, int tamanhoVetor){
    int paridadeVetor = tamanhoVetor % 2;
    int elementoCentralVetor;
    int i,j; 
    int mediana;

    for(i=0; i<tamanhoVetor; i++){
        for(j=0; j<tamanhoVetor -1; j++){
            if(vetor[j]>vetor[j+1]){
                mediana = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = mediana;
            }
        }            
    }
    if(paridadeVetor == 0){    
        mediana = (vetor[tamanhoVetor/2] + vetor[(tamanhoVetor/2)-1])/2;
    }else{
        elementoCentralVetor = tamanhoVetor/2;
        mediana = vetor[elementoCentralVetor];
    }
    return mediana;
}
int calculaMedianaMatrizQuadrada(int**matriz, int dimensaoMatriz){
    int *vetor = vetorizaMatrizQuadrada(matriz, dimensaoMatriz);
    int mediana = calculaMedianaDoVetor(vetor, dimensaoMatriz*dimensaoMatriz);

    return mediana;
}
// Copia elemento a elemento de uma matriz quadrada para outra
void copiaMatriz(int**matrizCopiada, int**matrizCopia, int linhasMatriz, int colunasMatriz){    
    int i, j;

    for(i=0; i<linhasMatriz; i++){
        for(j=0; j<colunasMatriz; j++){
            matrizCopia[i][j] = matrizCopiada[i][j];
        }
    }
}

void matrizMediana(int**matriz, int linhasMatriz, int colunasMatriz, int tamanhoMatrizFiltro){
    int sizeConjuntoElementos;
    int i, j, k, metadeMatrizFiltro;
    int posExtracaoLinha, posExtracaoLinhaInicial, posExtracaoLinhaFinal; 
    int posExtracaoColuna, posExtracaoColunaInicial, posExtracaoColunaFinal;
    int*conjutoElementosExtraidos;
    int**matrizInalterada = (int**)malloc(linhasMatriz*sizeof(int*));
    for(i = 0; i<linhasMatriz; i++){
        matrizInalterada[i] = (int*)malloc(colunasMatriz*sizeof(int));
    }

    copiaMatriz(matriz, matrizInalterada, linhasMatriz, colunasMatriz);

    metadeMatrizFiltro = tamanhoMatrizFiltro/2;

    sizeConjuntoElementos = tamanhoMatrizFiltro*tamanhoMatrizFiltro;  // matriz quadrada de filtro lado*lado
    conjutoElementosExtraidos = (int*)malloc(sizeConjuntoElementos*sizeof(int));

    for(i=0; i<linhasMatriz; i++){
        for(j=0; j<colunasMatriz; j++){
            if((i - metadeMatrizFiltro >= 0 && j - metadeMatrizFiltro >= 0) && (i + metadeMatrizFiltro < linhasMatriz && j + metadeMatrizFiltro < colunasMatriz)){ // Significa que a matriz de filtro cabe inteiramente na matriz principal
               // O range da vizinhanca vai de [-metadeMatrizFiltro, metadeMatrizFiltro+1] utilizando a posicao i,j como referencia (elemento central da matriz)
                posExtracaoLinhaInicial = i - metadeMatrizFiltro;
                posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                posExtracaoColunaInicial = j - metadeMatrizFiltro;
                posExtracaoColunaFinal = j + metadeMatrizFiltro;
            } else{ //significa que a matriz de filtro nao tem todos os elementos vizinhos ao elemento central disponiveis, desta forma estamos nos elementos das bordas ou cantos
                // Necessario testar em que posicao da matriz o laco esta percorrendo para aplicar um algoritmo de extracao de elementos vizinhos diferente                
                if(i - metadeMatrizFiltro < 0  && (j - metadeMatrizFiltro >=0 && j + metadeMatrizFiltro < colunasMatriz)){   // Borda superior da matriz
                    posExtracaoLinhaInicial = 0;
                    posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                    posExtracaoColunaInicial = j - metadeMatrizFiltro;
                    posExtracaoColunaFinal = j + metadeMatrizFiltro;
                } else if((i - metadeMatrizFiltro >= 0 && i + metadeMatrizFiltro < linhasMatriz) && j - metadeMatrizFiltro < 0){   // Borda esquerda da matriz
                    posExtracaoLinhaInicial = i - metadeMatrizFiltro;
                    posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                    posExtracaoColunaInicial = 0;
                    posExtracaoColunaFinal = j + metadeMatrizFiltro;
                } else if((i - metadeMatrizFiltro >= 0 && i + metadeMatrizFiltro < linhasMatriz) && j + metadeMatrizFiltro >= colunasMatriz){    // Borda direita da matriz 
                    posExtracaoLinhaInicial = i - metadeMatrizFiltro;
                    posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                    posExtracaoColunaInicial = j - metadeMatrizFiltro;
                    posExtracaoColunaFinal = colunasMatriz -1;
                } else if(i + metadeMatrizFiltro >= linhasMatriz && (j - metadeMatrizFiltro >=0 && j + metadeMatrizFiltro < colunasMatriz)){   // Borda inferior da matriz
                    posExtracaoLinhaInicial = i - metadeMatrizFiltro;
                    posExtracaoLinhaFinal = linhasMatriz - 1; 
                    posExtracaoColunaInicial = j - metadeMatrizFiltro;
                    posExtracaoColunaFinal = j + metadeMatrizFiltro;
                } else if(i + metadeMatrizFiltro >= linhasMatriz && j - metadeMatrizFiltro < 0){    // Canto inferior esquerdo da matriz
                    posExtracaoLinhaInicial =  i - metadeMatrizFiltro;
                    posExtracaoLinhaFinal = linhasMatriz - 1; 
                    posExtracaoColunaInicial = 0;
                    posExtracaoColunaFinal = j + metadeMatrizFiltro;
                } else if(i - metadeMatrizFiltro < 0 && j - metadeMatrizFiltro < 0){   // Canto superior esquerdo da matriz
                    posExtracaoLinhaInicial = 0;
                    posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                    posExtracaoColunaInicial = 0;
                    posExtracaoColunaFinal = j + metadeMatrizFiltro;
                } else if(i + metadeMatrizFiltro >= linhasMatriz && j + metadeMatrizFiltro >= colunasMatriz){       // Canto inferior direito da matriz
                    posExtracaoLinhaInicial = i - metadeMatrizFiltro;
                    posExtracaoLinhaFinal = linhasMatriz - 1;
                    posExtracaoColunaInicial = j - metadeMatrizFiltro;
                    posExtracaoColunaFinal = j -1 + metadeMatrizFiltro;
                } else if(i - metadeMatrizFiltro < 0 && j + metadeMatrizFiltro >= colunasMatriz){   // Canto superior direito da matriz
                    posExtracaoLinhaInicial = 0;
                    posExtracaoLinhaFinal = i + metadeMatrizFiltro;
                    posExtracaoColunaInicial = j - metadeMatrizFiltro;
                    posExtracaoColunaFinal = j -1 + metadeMatrizFiltro;
                }
            }
            k = 0;
            for(posExtracaoLinha = posExtracaoLinhaInicial; posExtracaoLinha <= posExtracaoLinhaFinal; posExtracaoLinha++){
                for(posExtracaoColuna = posExtracaoColunaInicial; posExtracaoColuna <= posExtracaoColunaFinal; posExtracaoColuna++){
                    conjutoElementosExtraidos[k] = matrizInalterada[posExtracaoLinha][posExtracaoColuna];
                    k++;
                }
            }
            matriz[i][j] = calculaMedianaDoVetor(conjutoElementosExtraidos, k);
        }
    }
    free(conjutoElementosExtraidos);
    free(matrizInalterada);
}
