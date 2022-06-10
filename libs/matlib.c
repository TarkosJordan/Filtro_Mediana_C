#include<stdio.h>
#include<stdlib.h>

#define matriz(numeroLinha,numeroColuna)            matriz[numeroLinha*colunasMatriz +numeroColuna]
#define matrizInalterada(numeroLinha,numeroColuna)  matrizInalterada[numeroLinha*colunasMatriz +numeroColuna]

PIXEL calculaMedianaDoVetorDePixels(PIXEL*vetorPixels, int tamanhoVetor){
    int paridadeVetor = tamanhoVetor % 2;
    int elementoCentralVetor;
    int i,j; 
    unsigned char medianaRed, medianaGreen, medianaBlue;
    PIXEL pixelMediana;

    for(i=0; i<tamanhoVetor; i++){
        for(j=0; j<tamanhoVetor -1; j++){
            if(vetorPixels[j].red > vetorPixels[j+1].red)
            {
                medianaRed = vetorPixels[j].red;
                vetorPixels[j].red = vetorPixels[j+1].red;
                vetorPixels[j+1].red = medianaRed;
            }
            if(vetorPixels[j].green > vetorPixels[j+1].green)
            {
                medianaGreen = vetorPixels[j].green;
                vetorPixels[j].green = vetorPixels[j+1].green;
                vetorPixels[j+1].green = medianaGreen;
            }
            if(vetorPixels[j].blue > vetorPixels[j+1].blue)
            {
                medianaBlue = vetorPixels[j].blue;
                vetorPixels[j].blue = vetorPixels[j+1].blue;
                vetorPixels[j+1].blue = medianaBlue;
            }
        }            
    }
    if(paridadeVetor == 0){    
        medianaRed = (vetorPixels[tamanhoVetor/2].red + vetorPixels[(tamanhoVetor/2)-1].red)/2;
        medianaGreen = (vetorPixels[tamanhoVetor/2].green + vetorPixels[(tamanhoVetor/2)-1].green)/2;
        medianaBlue = (vetorPixels[tamanhoVetor/2].blue + vetorPixels[(tamanhoVetor/2)-1].blue)/2;
    }else{
        elementoCentralVetor = tamanhoVetor/2;
        medianaRed = vetorPixels[elementoCentralVetor].red;
        medianaGreen = vetorPixels[elementoCentralVetor].green;
        medianaBlue = vetorPixels[elementoCentralVetor].blue;
    }
    pixelMediana.red = medianaRed;
    pixelMediana.green = medianaGreen;
    pixelMediana.blue = medianaBlue;
    return pixelMediana;
}

void copiaMatrizPixels(PIXEL*matriz, PIXEL*matrizInalterada, int linhasMatriz, int colunasMatriz){    
    int i, j;
    for(i=0; i<linhasMatriz; i++){
        for(j=0; j<colunasMatriz; j++){
            matrizInalterada(i,j) = matriz(i,j);
        }
    }
}

void matrizMediana(PIXEL*matriz, int linhasMatriz, int colunasMatriz, int tamanhoMatrizFiltro, int linhaInicial, int step){
    int sizeConjuntoElementos;
    int i, j, k, metadeMatrizFiltro;
    int posExtracaoLinha, posExtracaoLinhaInicial, posExtracaoLinhaFinal; 
    int posExtracaoColuna, posExtracaoColunaInicial, posExtracaoColunaFinal;
    PIXEL*conjutoElementosExtraidos;
    PIXEL*matrizInalterada = (PIXEL*)malloc(linhasMatriz*colunasMatriz*sizeof(PIXEL*));

    copiaMatrizPixels(matriz, matrizInalterada, linhasMatriz, colunasMatriz);

    metadeMatrizFiltro = tamanhoMatrizFiltro/2;

    sizeConjuntoElementos = tamanhoMatrizFiltro*tamanhoMatrizFiltro;  // matriz quadrada de filtro lado*lado
    conjutoElementosExtraidos = (PIXEL*)malloc(sizeConjuntoElementos*sizeof(PIXEL));

    for(i=linhaInicial; i<linhasMatriz; i+= step){
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
                    conjutoElementosExtraidos[k] = matrizInalterada(posExtracaoLinha,posExtracaoColuna);
                    k++;
                }
            }
            matriz(i,j) = calculaMedianaDoVetorDePixels(conjutoElementosExtraidos, k);
        }
    }
    free(conjutoElementosExtraidos);
    free(matrizInalterada);
}