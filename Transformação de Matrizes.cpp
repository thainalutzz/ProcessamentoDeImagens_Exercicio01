#include <stdio.h>
#include<math.h>
#include <string.h>

int calculaQtdElementosArquivo (FILE *arq, int qtdElementos){
    char Linha[100];
    char *result;
    while (!feof(arq))
    {
        result = fgets(Linha, 100, arq);
        //printf("%s/", Linha);
        char * pch;
        pch = strtok (Linha," ");
        while (pch != NULL)
        {
            //printf ("%s|",pch);
            if(strcmp(pch, "\n") != 0)
            {
                qtdElementos++;
            }
            pch = strtok (NULL, " ");
        }
    }
    //printf("\n");
    //printf("%d", qtdElementos);
    //printf("\n");
    //printf("\n");
    return qtdElementos;
}

int calculaOrdemMatriz (int qtdElementos, int ordem){
    if(sqrt(qtdElementos) == (int)sqrt(qtdElementos)){
        ordem = sqrt(qtdElementos);
        return ordem;
    }
    else{
        return 0;
    }
}

int main()
{
    FILE *arq;
    FILE *arqFinal;
    int qtdElementos = 0, ordem = 0;

    //Abre o arquivo de Entrada com a Matriz Inicial
    arq = fopen("entrada.txt", "r");
    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("O arquivo não foi encontrado.\n");
        return 0;
    }
    
    qtdElementos = calculaQtdElementosArquivo(arq, qtdElementos);
    ordem = calculaOrdemMatriz(qtdElementos, ordem);
    if(ordem == 0){
        printf("O arquivo não contém uma matriz quadrada.");
        return 0;
    }
    if(ordem < 10 || ordem > 20){
        printf("A matriz quadrada do arquivo deve ser de ordem entre 10 e 20.");
        return 0;
    }
    
    //Preenche a Matriz Inicial
    char *matrizInicial[ordem][ordem];
    arq = fopen("entrada.txt", "r");
    while (!feof(arq))
    {
	    for (int i=0; i<ordem; i++)
        {
            for (int j=0; j<ordem; j++)
            {
                fscanf(arq, "%s", &matrizInicial[i][j]);
            }
        }
    }
    
    //Imprime a Matriz Inicial
    printf("MATRIZ INICIAL\n");
    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            printf("%s ", &matrizInicial[i][j]);
        }
        printf("\n");
    }

    //Preenche a Matriz Final
    char *matrizFinal[ordem][ordem];
    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            matrizFinal[j][i] = matrizInicial[i][j];
        }
    }

    //Imprime a Matriz Final
    printf("\nMATRIZ FINAL\n");
    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            printf("%s ", &matrizFinal[i][j]);
        }
        printf("\n");
    }
    fclose(arq);

    //Cria e preenche o arquivo de Saida com a Matriz Final
    arqFinal = fopen("saida.txt", "w");
    for (int i=0; i<ordem; i++)
    {
        for (int j=0; j<ordem; j++)
        {
            fputc(matrizFinal[i][j], arqFinal);
            fputc(' ', arqFinal);
        }
        fputc('\n', arqFinal);
    }
    
    fclose(arqFinal);
    
    return 0;
}

