#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int calculaQtdElementosArquivo (FILE *arq, int qtdElementos){
    char ch;
    while((ch=fgetc(arq))!= EOF)
    {
        if(ch != '\n' && ch != '\r')
        {
            qtdElementos++;
        }
    }
    return qtdElementos;
}

int calculaOrdemMatriz (int qtdElementos, int ordem){
    //Verifica se o número é inteiro para saber se a matriz é quadrada
    if(sqrt(qtdElementos) == (int)sqrt(qtdElementos)){
        ordem = sqrt(qtdElementos);
        return ordem;
    }
    else{
        return 0;
    }
}

void imprimeMatriz (int ordem, char matriz[ordem][ordem]){
    int i=0, j=0;
    for (i=0; i<ordem; i++)
    {
        for (j=0; j<ordem; j++)
        {
            putchar(matriz[i][j]);
            //printf("%c", matrizInicial[i][j]);
        }
        printf("\n");
    }
}

char preencheMatrizComArquivo (FILE *arq, int ordem, char matriz[ordem][ordem]){
    arq = fopen("entrada.txt", "r");
    char ch;
    int i=0, j=0;

    while (!feof(arq))
    {
        while((ch=fgetc(arq))!= EOF)
        {
            if(ch != '\n' && ch != '\r')
            {
                matriz[i][j] = ch;
                if(j == ordem-1)
                {
                    j=0;
                    i++;
                }
                else
                {
                    j++; 
                }
            }
        }
    }
    
    //Fecha o aquivo com a matriz inicial
    fclose(arq);
    return matriz;
}

char atualizaMatrizAuxiliar (int ordem, char matriz[ordem][ordem], char matrizAuxiliar[ordem][ordem]){
    int i=0, j=0;

    for (i=0; i<ordem; i++)
    {
        for (j=0; j<ordem; j++)
        {
            matrizAuxiliar[i][j] = matriz[i][j];
        }
    }
}

void preencheMatrizTrocandoLinhasColunas (int ordem, char matriz[ordem][ordem], char matrizAuxiliar[ordem][ordem]){
    int i=0, j=0;
    
    for (i=0; i<ordem; i++)
    {
        for (j=0; j<ordem; j++)
        {
            matriz[j][i] = matrizAuxiliar[i][j];
        }
    }
}

void preencheMatrizSubstituindoCaractere (int ordem, char matriz[ordem][ordem], char caractereAntigo, char caractereNovo){
    int i=0, j=0;
    
    for (i=0; i<ordem; i++)
    {
        for (j=0; j<ordem; j++)
        {
            if(matriz[i][j] == caractereAntigo)
            {
                matriz[i][j] = caractereNovo;
            }
        }
    }
}

void geraArquivoComMatrizFinal (FILE *arqFinal, int ordem, char matriz[ordem][ordem]){
    int i=0, j=0;
    arqFinal = fopen("saida.txt", "w");
    for (i=0; i<ordem; i++)
    {
       for (j=0; j<ordem; j++)
        {
            fputc(matriz[i][j], arqFinal);
        } 
        fputc('\n', arqFinal);
    }
    
    fclose(arqFinal);
}

int main()
{

    //Abre o arquivo com a matriz inicial
    FILE *arq;
    arq = fopen("entrada.txt","r");
    if(arq == NULL)
    {
     printf("Erro, nao foi possivel abrir o arquivo\n");
     return 0;
    }
    
    //Conta a quantidade de elementos na matriz
    int qtdElementos = 0;
    qtdElementos = calculaQtdElementosArquivo(arq, qtdElementos);
    
    //Fecha o aquivo com a matriz inicial
    fclose(arq);
    
    //Verifica se a matriz eh quadrada e valida a ordem
    int ordem = 0;
    ordem = calculaOrdemMatriz(qtdElementos, ordem);
    if(ordem == 0){
        printf("O arquivo nao contem uma matriz quadrada.");
        return 0;
    }
    if(ordem < 10 || ordem > 20){
        printf("A matriz quadrada do arquivo deve ser de ordem entre 10 e 20.");
        return 0;
    }
    
    //Preenche a Matriz Inicial
    char matriz[ordem][ordem];
    matriz[ordem][ordem] = preencheMatrizComArquivo(arq, ordem, matriz);
    
    //Cria uma Matriz Axiliar igual a Matriz Inicial
    char matrizAuxiliar[ordem][ordem];
    atualizaMatrizAuxiliar(ordem, matriz, matrizAuxiliar);
    
    //Imprime a Matriz Inicial
    printf(":: MATRIZ ORIGINAL ::\n");
    imprimeMatriz(ordem, matriz);
    printf(":::::::::::::::::::::\n");
    
    //A partir daqui fazer um menu
    
    //Caso troca de linhas e colunas e colunas e linhas
    //Imprime a Matriz Inicial
    printf(":: MATRIZ ANTES ::\n");
    imprimeMatriz(ordem, matriz);
    printf(":::::::::::::::::::::\n");
    preencheMatrizTrocandoLinhasColunas (ordem, matriz, matrizAuxiliar);
    //Imprime a Matriz Alterada
    printf(":: MATRIZ DEPOIS ::\n");
    imprimeMatriz(ordem, matriz);
    printf(":::::::::::::::::::::\n");
    //Atualiza a Matriz Auxiliar com a nova Matriz alterada
    atualizaMatrizAuxiliar(ordem, matriz, matrizAuxiliar);
    
    //Caso substitui caracter
    //Imprime a Matriz Inicial
    printf(":: MATRIZ ANTES ::\n");
    imprimeMatriz(ordem, matriz);
    printf(":::::::::::::::::::::\n");
    char caractereAntigo;
    char caractereNovo;
    caractereAntigo = '2';
    caractereNovo = 't';
    preencheMatrizSubstituindoCaractere (ordem, matriz, caractereAntigo, caractereNovo);
    //Imprime a Matriz Alterada
    printf(":: MATRIZ DEPOIS ::\n");
    imprimeMatriz(ordem, matriz);
    printf(":::::::::::::::::::::\n");
    //Atualiza a Matriz Auxiliar com a nova Matriz alterada
    atualizaMatrizAuxiliar(ordem, matriz, matrizAuxiliar);
    
    FILE *arqFinal;
    geraArquivoComMatrizFinal(arqFinal, ordem, matriz);
    
    return 0;
}
