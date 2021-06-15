#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int main()
{
    char usarPadrao;
    int nMax = 10; // Criterio de parada: Numero maximo de interacoes
    printf("Usar nMax padrao (%d)? (s/n): ", nMax);
    scanf(" %c", &usarPadrao);

    if (usarPadrao == 'n')
    {
        do
        {
            printf("Por favor digite o numero maximo de iteracoes: ");
            scanf("%d", &nMax);
            if (nMax <= 0)
            {
                printf("nMax invalido. Digite um numero maior ou igual a 1.");
            }
        } while (nMax <= 0);
    }

    double precisao = 0.001; //Criterio de parada: Erro relativo maximo
    printf("Usar precisao padrao (%lf)? (s/n): ", precisao);
    scanf(" %c", &usarPadrao);

    if (usarPadrao == 'n')
    {
        do
        {
            printf("Por favor digite a precisao relativa desejada: ");
            scanf("%lf", &precisao);
            if (precisao < 0)
            {
                printf("Precisao invalida, por favor digite um numero nao-negativo.");
            }
        } while (precisao < 0);
    }

    int dimensao; // Dimensao da matriz (n x n)
    // Perguntar a dimensao da matriz para o usuario
    do
    {
        printf("Por favor digite a dimensao da matriz aumentada: ");
        scanf("%d", &dimensao);
        if (dimensao <= 0)
        {
            printf("Dimensao invalida. Digite um numero maior ou igual a 1.");
        }
    } while (dimensao <= 0);

    double matriz_a[dimensao][dimensao], matriz_b[dimensao], matriz_x[dimensao], erro_absoluto[dimensao], matriz_beta[dimensao];

    printf("PREENCHER MATRIZ: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        for (int coluna = 0; coluna < dimensao; coluna++)
        {
            printf("Por favor, digite o valor de a[%d%d]: ", linha + 1, coluna + 1);
            scanf("%lf", &matriz_a[linha][coluna]);
        }
        printf("Por favor, digite o valor de b[%d]: ", linha + 1);
        scanf("%lf", &matriz_b[linha]);
    }

    //Pedir o chute inicial ao usuario
    printf("PREENCHER CHUTE INICIAL: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("Por favor digite o valor inicial de x%d: ", linha + 1);
        scanf("%lf", &matriz_x[linha]);
    }

    printf("MATRIZ AUMENTADA: \n");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("|  ");
        for (int coluna = 0; coluna < dimensao; coluna++)
        {
            printf("%lf ", matriz_a[linha][coluna]);
        }
        printf("| %lf  | \n", matriz_b[linha]);
    }
    printf("VERIFICACAO DO CRITERIO DE SASSENFELD: ");
    bool sassenfeld = true;
    for (int linha = 0; linha < dimensao; linha++)
    {
        matriz_beta[linha] = 0;
        for (int coluna = 0; coluna < dimensao - 1; coluna++)
        {
            if (coluna != linha)
            {
                matriz_beta[linha] = matriz_beta[linha] + matriz_a[linha][coluna];
            }
        }
        matriz_beta[linha] = matriz_beta[linha] / matriz_a[linha][linha];
        if (matriz_beta[linha] > 1 || matriz_beta[linha] > -1)
        {
            sassenfeld = false;
            printf("A matriz nao atende ao Criterio de Sassenfeld. \n");
            break;
        }
    }
    if (sassenfeld)
    {
        printf("A matriz atende ao Criterio de Sassenfeld, logo as iteracoes irao converter para o resultado. \n");
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
            for (int coluna = 0; coluna < dimensao; coluna++)
            {
                if (linha != coluna)
                {
                    matriz_x[linha] = matriz_x[linha] - (matriz_a[linha][coluna] * matriz_x[coluna]);
                }
            }
            matriz_x[linha] = matriz_x[linha] / matriz_a[linha][linha];
            printf("x%d = %lf \n", linha + 1, matriz_x[linha]);

            // Calculo do erro absoluto: Valor absoluto da subtraçao entre o x linha anterior (armazenado anteriormente) e o x linha encontrado no passo atual, dividido por x linha encontrado no passo atual
            erro_absoluto[linha] = (erro_absoluto[linha] - matriz_x[linha]) / matriz_x[linha];
            if (erro_absoluto[linha] < 0)
            {
                erro_absoluto[linha] *= -1;
            }
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