#include <stdio.h>
#include <stdbool.h>
int main()
{
    int nMax;
    printf("Por favor digite o numero maximo de iteracoes: ");
    scanf("%d", &nMax);
    int dimensao;
    printf("Por favor digite a dimensao da matriz aumentada: ");
    scanf("%d", &dimensao);
    double precisao;
    printf("Por favor digite a precisao relativa desejada: ");
    scanf("%lf", &precisao);

    double matriz_a[dimensao][dimensao], matriz_b[dimensao], matriz_x[dimensao], erro_absoluto[dimensao];

    printf("ENTRADA DE DADOS: \n");
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
    for (int linha = 0; linha < dimensao; linha++)
    {

        printf("CHUTES: \n");
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

            // Calculo do erro absoluto
            erro_absoluto[linha] = (erro_absoluto[linha] - matriz_x[linha]) / matriz_x[linha];
            // Modulo
            if (erro_absoluto[linha] < 0)
            {
                erro_absoluto[linha] = erro_absoluto[linha] * -1;
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
    printf("SOLUCAO APROXIMADA DO SISTEMA: (");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("%lf", matriz_x[linha]);
        if (linha != dimensao - 1)
        {
            printf(", ");
        }
    }
    printf(" )t");
}