#include<stdlib.h>

//Para structs por default os compiladores alocam memoria de 4 em 4 bytes esse comando altera esse step de alocacao de memoria pelo valor passado para tornar os tamanhos das structs mais flexiveis
#pragma pack(1)

// Criacao de struct que define o cabecalho do arquivo da imagem bmp (devemos conhecer a estrutura do arquivo previamente)
struct cabecalho{
    unsigned short int tipoDaImg;   // 2 bytes (arquivo bmp retorna "BM" caracterizando o arquivo como bmp) 
    unsigned int tamanhoArquivo;    // 4 bytes (arquivo bmp reserve esses 4 bytes para guardar a informacao do tamanho do arquivo como um todo em bytes)
    unsigned short int reservado1;  // 2 bytes reservados (caso haja mudanca do tipo de arquivo da img)
    unsigned short int reservado2;  // mais 2 bytes reservados (caso haja mudanca do tipo de arquivo da img)
    unsigned int inicioImagemBmp;   // indica a posicao do comeco da imagem bmp (o comeco da img nao do cabecalho da img) consequentemente isso tbm passa a info do tamanho do cabecalho do arquivo em bytes

    // A continuacao da struct indica os atributos referentes ao cabecalho da imagem bmp 24bits
    unsigned int tamanhoCab;
    unsigned int largura;           // em pixels 
    unsigned int altura;            // em pixels
    unsigned short int planos;
    unsigned short int bitsPorPixel;
    unsigned int compressao;
    unsigned int tamanhoImgBmp;     // tamanho somente da imagem descontando o tamanho dos cabecalhos
    unsigned int larguraResolucao;
    unsigned int alturaResolucao;
    unsigned int coresUsadas;
    unsigned int coresImportantes;
};
typedef struct cabecalho CABECALHO;

// ordenacao de cores nos pixels por padrao vem 'bgr'
struct pixel{   // 8 bits para representar cada cor
    unsigned char blue; 
    unsigned char green;
    unsigned char red;
};
typedef struct pixel PIXEL;