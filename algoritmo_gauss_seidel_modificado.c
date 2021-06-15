#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    int nMax;
    do
    {
        printf("Por favor digite o numero maximo de iteracoes: ");
        scanf("%d", &nMax);
        if (nMax <= 0)
        {
            printf("nMax invalido. Digite um numero maior ou igual a 1.");
        }
    } while (nMax <= 0);
    int dimensao;
    do
    {
        printf("Por favor digite a dimensao da matriz aumentada: ");
        scanf("%d", &dimensao);
        if (dimensao <= 0)
        {
            printf("Dimensao invalida. Digite um numero maior ou igual a 1.");
        }
    } while (dimensao <= 0);
    double precisao;
    do
    {
        printf("Por favor digite a precisao relativa desejada: ");
        scanf("%lf", &precisao);
        if (precisao < 0)
        {
            printf("Precisao invalida, por favor digite um numero nao-negativo.");
        }
    } while (precisao < 0);
    double matriz_a[dimensao][dimensao], matriz_b[dimensao], matriz_x[dimensao], erro_absoluto[dimensao];
    printf("PREENCHER CHUTE INICIAL: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("Por favor digite o valor inicial de x%d: ", linha + 1);
        scanf("%lf", &matriz_x[linha]);
    }
    printf("PREENCHENDO MATRIZ COM A DIMENSAO DADA... \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        for (int coluna = 0; coluna < dimensao; coluna++)
        {
            if (coluna >= linha - 1 && coluna < linha + 2)
            {
                if ((coluna - linha) % 2 == 0)
                {
                    matriz_a[linha][coluna] = -2;
                }
                else
                {
                    matriz_a[linha][coluna] = 1;
                }
            }
            else
            {
                matriz_a[linha][coluna] = 0;
            }
        }
        matriz_b[linha] = (linha + 1) % 2; // 1 para indice par ou 0 para indice impar
    }
    printf("MATRIZ AUMENTADA: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("| ");
        for (int coluna = 0; coluna < dimensao; coluna++)
        {
            if (matriz_a[linha][coluna] >= 0) //Formatacao da array
            {
                printf(" ");
            }
            printf("%.0lf ", matriz_a[linha][coluna]);
        }
        printf("| %.0lf  | \n", matriz_b[linha]);
    }
    printf("ITERAÇÃO 0: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("x%d: %lf \n", linha, matriz_x[linha]);
    }
    // Iteracoes do metodo gauss-seidel
    for (int iteracao = 1; iteracao <= nMax; iteracao++)
    {
        bool atendeuPrecisao = true;
        printf("ITERACAO %d: \n", iteracao);
        for (int linha = 0; linha < dimensao; linha++)
        {
            erro_absoluto[linha] = matriz_x[linha];
            matriz_x[linha] = matriz_b[linha];
            for (int coluna = linha - 1; coluna <= linha + 1; coluna++)
            {
                if (coluna == linha || coluna < 0)
                {
                    continue;
                }
                matriz_x[linha] = matriz_x[linha] - (matriz_a[linha][coluna] * matriz_x[coluna]);
            }
            matriz_x[linha] = matriz_x[linha] / matriz_a[linha][linha];
            printf("x%d = %lf \n", linha + 1, matriz_x[linha]);
            // Calculo do erro absoluto: Valor absoluto da subtraçao entre o x linha anterior (armazenado anteriormente) e o x linha encontrado no passo atual, dividido por x linha encontrado no passo atual
            erro_absoluto[linha] = (erro_absoluto[linha] - matriz_x[linha]) / matriz_x[linha];
            if (erro_absoluto[linha] < 0)
            {
                erro_absoluto[linha] *= -1;
            }
            printf("Erro absoluto x%d: %lf \n", linha + 1, erro_absoluto[linha]);
            if (erro_absoluto[linha] > precisao)
            {
                atendeuPrecisao = false;
            }
        }
        if (atendeuPrecisao)
        {
            printf("Criterio de precisao atendido, parando execucao...");
            break;
        }
    }
    // Resultado aproximado
    printf("SOLUCAO APROXIMADA DO SISTEMA: (");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("%lf", matriz_x[linha]);
        if (linha != dimensao - 1)
        {
            printf(", ");
        }
    }
    printf(" )t \n");
}