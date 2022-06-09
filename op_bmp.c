#include <stdlib.h>
#include <stdio.h>
#include ".\libs\matlib.h"
#include ".\libs\Types.h"

int main(int argc, char** argv){

    // Em prog existem 2 tipos de arquivos texto ou binario 
    // para arquivos binarios devemos saber a estrutura do arquivo (exemplo arquivo bmp)

    if(argc != 4){
        printf("Numero de parametros errado\n%s <img_entrada.bmp> <arquivo_saida.bmp> <tamanho_filtro>\n", argv[0]);
        exit(0);
    }

    int tamanhoMatrizFiltro = atoi(argv[3]);
    if(tamanhoMatrizFiltro%2 == 0){
        printf("Tamanho de matriz par nao eh possivel aplicar filtro %d\n", tamanhoMatrizFiltro);
        exit(0);
    }

    FILE *arquivoEntrada = fopen(argv[1], "rb"); // Parametro rb indica que o arquivo eh binario 'b' (por default ele eh texto) e o caractere 'r' indica q eh para leitura
    if(arquivoEntrada == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        exit(0);
    }

    CABECALHO cabecalhoImg;
    // Explicacao funcao fread
    // parametros (endereco de memoria em que serao escritos os bytes do arquivo lido)
    //            (quantidade de bytes que serao lidas do arquivo para variavel criada)
    //            (numero de cabecalhos que serao lidos no caso 1)
    //            (de qual arquivo serao buscados a informacao neste caso os bytes do cabecalho)
    fread(&cabecalhoImg, sizeof(cabecalhoImg), 1, arquivoEntrada);
                  
    int i, j;

    // Alocando memoria para leitura de pixels da imagem que sera aplicado o filtro mediana e matrizes auxiliares temporarias de cada cor
    PIXEL **img = (PIXEL**)malloc(cabecalhoImg.altura * sizeof(PIXEL*));
    unsigned char **matrizRed = (unsigned char**)malloc(cabecalhoImg.altura*sizeof(unsigned char*));
    unsigned char **matrizGreen = (unsigned char**)malloc(cabecalhoImg.altura*sizeof(unsigned char*));
    unsigned char **matrizBlue = (unsigned char**)malloc(cabecalhoImg.altura*sizeof(unsigned char*));
    for(i=0; i<cabecalhoImg.largura; i++){
        img[i] = (PIXEL*)malloc(cabecalhoImg.largura * sizeof(PIXEL));
        matrizRed[i] = (unsigned char*)malloc(cabecalhoImg.largura * sizeof(unsigned char));
        matrizGreen[i] = (unsigned char*)malloc(cabecalhoImg.largura * sizeof(unsigned char));
        matrizBlue[i] = (unsigned char*)malloc(cabecalhoImg.largura * sizeof(unsigned char));
    }

    // Realizando a leitura dos pixels do arquivo de entrada
    for(i=0; i<cabecalhoImg.altura; i++){
        for(j=0; j<cabecalhoImg.largura; j++){
            fread(&img[i][j], sizeof(PIXEL), 1, arquivoEntrada);
        }
    }

    // Populando matrizes temporarias de cada cor com as matrizes de cores da imagem original (antes do filtro)
    for(i=0; i<cabecalhoImg.altura; i++){
        for(j=0; j<cabecalhoImg.largura; j++){
            matrizBlue[i][j] = img[i][j].blue;
            matrizGreen[i][j] = img[i][j].green;
            matrizRed[i][j] = img[i][j].red;
        }
    }

    matrizMediana(matrizBlue, cabecalhoImg.altura, cabecalhoImg.largura, tamanhoMatrizFiltro);
    matrizMediana(matrizRed, cabecalhoImg.altura, cabecalhoImg.largura, tamanhoMatrizFiltro);
    matrizMediana(matrizGreen, cabecalhoImg.altura, cabecalhoImg.largura, tamanhoMatrizFiltro);

    // Criacao imagem de saida

    FILE *arquivoSaida = fopen(argv[2], "wb");
    if(arquivoSaida == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[2]);
        exit(0);
    }

    fwrite(&cabecalhoImg, sizeof(CABECALHO), 1, arquivoSaida);
    for(i=0; i<cabecalhoImg.altura; i++){
        for(j=0; j<cabecalhoImg.largura; j++){
            img[i][j].blue = matrizBlue[i][j];
            img[i][j].green = matrizGreen[i][j];
            img[i][j].red = matrizRed[i][j];
            fwrite(&img[i][j], sizeof(PIXEL), 1, arquivoSaida);
        }
    }
    
    // Tem que realizar um filtro pra testar se o numero de colunas eh multiplo de 4 e caso nao seja descontar o resto das operacoes realizadas na imagem
    // no final tem que somar esse resto de volta no arquivo de saida para conservar a estrutura da imagem 
    // eh do padrao do tipo do arquivo bmp usar multiplo de 4 nas linhas 

    char aux;

    for(i=0; i<cabecalhoImg.altura; i++){

		int ali = (cabecalhoImg.largura * 3) % 4;

		if (ali != 0){
			ali = 4 - ali;
		}

		for(j=0; j<cabecalhoImg.largura; j++){
			fread(&img[i][j], sizeof(PIXEL), 1, arquivoEntrada);
        }
        
        for(j=0; j<ali; j++){
			fread(&aux, sizeof(unsigned char), 1, arquivoEntrada);
    	}
    }

    for(i=0; i<cabecalhoImg.altura; i++){

		int ali = (cabecalhoImg.largura * 3) % 4;

		if (ali != 0){
			ali = 4 - ali;
		}

		for(j=0; j<cabecalhoImg.largura; j++){
	        fwrite(&img[i][j], sizeof(PIXEL), 1, arquivoSaida);
        }
        
        for(j=0; j<ali; j++){
	        fwrite(&aux, sizeof(unsigned char), 1, arquivoSaida);
    	}
    }
    
    // Desalocando memoria dos mallocs
    free(img);
    free(matrizRed);
    free(matrizGreen);
    free(matrizBlue);

    //Fechamento dos arquivos    
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    return 0;
}