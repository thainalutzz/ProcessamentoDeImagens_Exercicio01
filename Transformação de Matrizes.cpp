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

void geraArquivoComMatrizFinal (FILE *arqFinal, int ordem, char matriz[ordem][ordem], int numEfeito){
    int i=0, j=0;

    char efeito[100] = "saidaEfeito";
    char num[3];
    sprintf (num, "%d", numEfeito);
    strcat(efeito, num);
    strcat(efeito, ".txt");
    
    arqFinal = fopen(efeito, "w");

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

void menu (int ordem, char matriz[ordem][ordem], char matrizAuxiliar[ordem][ordem]){
    int efeito = 0, qtdEfeitos = 0;
    do{
        FILE *arqFinal;
        printf("::: Efeitos Disponiveis para a Matriz :::\n");
        printf("1 - Matriz com as linhas no lugar das colunas\n");
        printf("2 - Matriz com as colunas no lugar das linhas\n");
        printf("3 - Substituir um caractere por outro\n");
        printf("0 - Sair\n");
        printf(":::::::::::::::::::::::::::::::::::::::::::::\n\n");
        
        do
        {
            printf("Digite o numero do efeito desejado: ");
            scanf("%d", &efeito);
        }while(efeito != 1 && efeito != 2 && efeito != 3 && efeito != 0);

        switch (efeito)
        {
            case 1:
                printf("\n:: EFEITO TROCA LINHAS POR COLUNAS ::\n");
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
                //Contador de Efeitos aumenta em 1
                qtdEfeitos++;
                //Gera arquivo com a aplicação do efeito
                geraArquivoComMatrizFinal(arqFinal, ordem, matriz, qtdEfeitos);
                break;
            case 2:
                printf("\n:: EFEITO TROCA COLUNAS POR LINHAS ::\n");
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
                //Contador de Efeitos aumenta em 1
                qtdEfeitos++;
                //Gera arquivo com a aplicação do efeito
                geraArquivoComMatrizFinal(arqFinal, ordem, matriz, qtdEfeitos);
                break;
            case 3:
                printf("\n:: EFEITO SUBSTITUI CARACTERE POR OUTRO ::\n");
                char caractereAntigo;
                char caractereNovo;
                printf("Digite o caractere a ser substituindo: ");
                scanf(" %c", &caractereAntigo);
                printf("Digite o novo caractere: ");
                scanf(" %c", &caractereNovo);
                //Imprime a Matriz Inicial
                printf(":: MATRIZ ANTES ::\n");
                imprimeMatriz(ordem, matriz);
                printf(":::::::::::::::::::::\n");
                //Troca o caractereAntigo pelo caractereNovo
                preencheMatrizSubstituindoCaractere (ordem, matriz, caractereAntigo, caractereNovo);
                //Imprime a Matriz Alterada
                printf(":: MATRIZ DEPOIS ::\n");
                imprimeMatriz(ordem, matriz);
                printf(":::::::::::::::::::::\n");
                //Atualiza a Matriz Auxiliar com a nova Matriz alterada
                atualizaMatrizAuxiliar(ordem, matriz, matrizAuxiliar);
                //Contador de Efeitos aumenta em 1
                qtdEfeitos++;
                //Gera arquivo com a aplicação do efeito
                geraArquivoComMatrizFinal(arqFinal, ordem, matriz, qtdEfeitos);
                break;
            case 0:
                if(qtdEfeitos > 0)
                {
                    printf("Gerado(s) %d arquivo(s) com os efeito(s) aplicado(s)!", qtdEfeitos);
                }
                else
                {
                    printf("Nenhum efeito aplicado!");
                }

                break;
        }
    }while(efeito != 0);

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
    
    //MENU
    menu(ordem, matriz, matrizAuxiliar);
    
    return 0;
}
