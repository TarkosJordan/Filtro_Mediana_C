#include <stdlib.h>
#include <stdio.h>
#include ".\libs\matlib.h"

int main(int argc, char** argv){

    if(argc != 4){
        printf("Numero de parametros errado\n%s <img_entrada.bmp> <arquivo_saida.bmp> <tamanho_filtro>\n", argv[0]);
        exit(0);
    }

    int tamanhoMatrizFiltro = atoi(argv[3]);
    if(tamanhoMatrizFiltro%2 == 0){
        printf("Tamanho de matriz par nao eh possivel aplicar filtro %d\n", tamanhoMatrizFiltro);
        exit(0);
    }

    FILE *arquivoEntrada = fopen(argv[1], "rb"); 
    if(arquivoEntrada == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        exit(0);
    }

    CABECALHO cabecalhoImg;
    fread(&cabecalhoImg, sizeof(cabecalhoImg), 1, arquivoEntrada);
                  
    int i, j;

    PIXEL **img = (PIXEL**)malloc(cabecalhoImg.altura * sizeof(PIXEL*));
    for(i=0; i<cabecalhoImg.largura; i++){
        img[i] = (PIXEL*)malloc(cabecalhoImg.largura * sizeof(PIXEL));
    }

    // Realizando a leitura dos pixels do arquivo de entrada
    for(i=0; i<cabecalhoImg.altura; i++){
        for(j=0; j<cabecalhoImg.largura; j++){
            fread(&img[i][j], sizeof(PIXEL), 1, arquivoEntrada);
        }
    }

    matrizMediana(img, cabecalhoImg.altura, cabecalhoImg.largura, tamanhoMatrizFiltro);

    // Criacao imagem de saida

    FILE *arquivoSaida = fopen(argv[2], "wb");
    if(arquivoSaida == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[2]);
        exit(0);
    }

    fwrite(&cabecalhoImg, sizeof(CABECALHO), 1, arquivoSaida);
    for(i=0; i<cabecalhoImg.altura; i++){
        for(j=0; j<cabecalhoImg.largura; j++){
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

    //Fechamento dos arquivos    
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    return 0;
}