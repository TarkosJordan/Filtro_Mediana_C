#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include "./libs/matlib.h"


#define img(numeroLinha,numeroColuna) img[numeroLinha*larguraImagem +numeroColuna]

int main(int argc, char** argv){

    if(argc != 5){
        printf("Numero de parametros errado\n%s <img_entrada.bmp> <arquivo_saida.bmp> <tamanho_filtro> <numero_processos>\n", argv[0]);
        exit(0);
    }

    int numeroProcessos = atoi(argv[4]);
    if(numeroProcessos < 1){
        printf("Numero de processos escolhido deve ser pelo menos 1, quantidade de processos escolhida %d eh invalida\n", numeroProcessos);
        exit(0);
    }

    int tamanhoMatrizFiltro = atoi(argv[3]);
    if(tamanhoMatrizFiltro%2 == 0){
        printf("Tamanho da matriz de filtro, par nao eh possivel aplicar filtro, tamanho: %d invalido\n", tamanhoMatrizFiltro);
        exit(0);
    }

    FILE *arquivoEntrada = fopen(argv[1], "rb"); 
    if(arquivoEntrada == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        exit(0);
    }

    CABECALHO cabecalhoImg;
    fread(&cabecalhoImg, sizeof(cabecalhoImg), 1, arquivoEntrada);

    unsigned int larguraImagem = cabecalhoImg.largura;
    unsigned int alturaImagem = cabecalhoImg.altura;
                  
    unsigned int i, j;

    //PIXEL *img = (PIXEL*)malloc(alturaImagem *larguraImagem * sizeof(PIXEL));

    int chave = 5;

	int shmid = shmget(chave, larguraImagem*alturaImagem*sizeof(PIXEL), IPC_CREAT | 0600);	

	PIXEL *img = shmat(shmid, 0, 0);

    // Realizando a leitura dos pixels do arquivo de entrada
    for(i=0; i<alturaImagem; i++){
        for(j=0; j<larguraImagem; j++){
            fread(&img(i,j), sizeof(PIXEL), 1, arquivoEntrada);
        }
    }

	/*int li, i, id;

	li = 0;
	for (i = 1; i < np; i++) {
		id = fork();
		if (id == 0) {
			li = i;
			break;
		}
	}*/



    matrizMediana(img, alturaImagem, larguraImagem, tamanhoMatrizFiltro);

    // Criacao imagem de saida

    FILE *arquivoSaida = fopen(argv[2], "wb");
    if(arquivoSaida == NULL){
        printf("Erro ao abrir o arquivo %s\n", argv[2]);
        exit(0);
    }

    fwrite(&cabecalhoImg, sizeof(CABECALHO), 1, arquivoSaida);
    for(i=0; i<alturaImagem; i++){
        for(j=0; j<larguraImagem; j++){
            fwrite(&img(i,j), sizeof(PIXEL), 1, arquivoSaida);
        }
    }
    
    // Tem que realizar um filtro pra testar se o numero de colunas eh multiplo de 4 e caso nao seja descontar o resto das operacoes realizadas na imagem
    // no final tem que somar esse resto de volta no arquivo de saida para conservar a estrutura da imagem 
    // eh do padrao do tipo do arquivo bmp usar multiplo de 4 nas linhas 

    char aux;

    for(i=0; i<alturaImagem; i++){

		int ali = (larguraImagem * 3) % 4;

		if (ali != 0){
			ali = 4 - ali;
		}

		for(j=0; j<larguraImagem; j++){
			fread(&img(i,j), sizeof(PIXEL), 1, arquivoEntrada);
        }
        
        for(j=0; j<ali; j++){
			fread(&aux, sizeof(unsigned char), 1, arquivoEntrada);
    	}
    }

    for(i=0; i<alturaImagem; i++){

		int ali = (larguraImagem * 3) % 4;

		if (ali != 0){
			ali = 4 - ali;
		}

		for(j=0; j<larguraImagem; j++){
	        fwrite(&img(i,j), sizeof(PIXEL), 1, arquivoSaida);
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