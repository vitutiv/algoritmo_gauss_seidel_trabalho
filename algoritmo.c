#include <stdio.h>
int main()
{
    int nMax;
    printf("Por favor digite o numero maximo de iteracoes: ");
    scanf("%d", &nMax);
    int dimensao;
    printf("Por favor digite a dimensao da matriz aumentada: ");
    scanf("%d", &dimensao);
    double matriz_a[dimensao][dimensao], matriz_b[dimensao], matriz_x[dimensao];

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
    // Primeiro chute: todos os itens x = 0;
    for (int linha = 0; linha < dimensao; linha++)
    {
        matriz_x[linha] = 0;
    }
    // Iteracoes do metodo gauss-seidel
    for (int iteracao = 1; iteracao <= nMax; iteracao++)
    {
        printf("ITERACAO %d: \n", iteracao);
        for (int linha = 0; linha < dimensao; linha++)
        {
            matriz_x[linha] = matriz_b[linha];
            for (int coluna = 0; coluna < dimensao; coluna++)
            {
                matriz_x[linha] = matriz_x[linha] - (matriz_a[linha][coluna] * matriz_x[coluna]);
            }
            matriz_x[linha] = matriz_x[linha] / matriz_a[linha][linha];
            printf("x%d = %.2f \n", linha + 1, matriz_x[linha]);
        }
    }
}