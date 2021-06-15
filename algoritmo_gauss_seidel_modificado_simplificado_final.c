#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    /*
        nMax: Criterio de parada - numero maximo de iteracoes do metodo de gauss-seidel
        precisao: Criterio de parada - erro relativo do metodo de gauss-seidel
        dimensao: dimensao da matriz_a nxn e quantidade de incognitas das equacoes lineares
    */
    int nMax = 10;
    double precisao = 0.001;
    int dimensao = 10;
    /*  
        matriz_a = armazenam os valores de a[linha, coluna]; 
        vetor_b: armazena os valores de b[linha] (NAO USADO, POIS iniciando de 0, b[linha_par] sempre = 0 e b[linha_impar] sempre = 1)
        vetor_x: armazena os valores aproximados de x, encontrados em cada passo. Ao fim do programa, ele armazena a ultima solucao encontrada.
        erro_relativo: armazena o erro relativo de x no passo, pelo calculo | ( x_passo_anterior - x_passo_atual ) / x(passo_atual) |. Ao fim do programa, ele armazena os ul
    */
    double matriz_a[dimensao][dimensao], vetor_x[dimensao], erro_relativo[dimensao];

    printf("POPULANDO AS MATRIZES... \n");
    for (int linha = 0; linha < dimensao; linha++)
    // Percorrer todas as linhas da matriz_a
    {
        for (int coluna = 0; coluna < dimensao; coluna++)
        // Percorrer todas as colunas da matriz_a
        {
            if (coluna >= linha - 1 && coluna <= linha + 1)
            // SE coluna estiver entre o intervalo [ linha-1, linha+1 ], atribuir a matriz_a[linha][coluna] um dos valores abaixo:
            {
                if ((coluna - linha) % 2 == 0)
                // SE (coluna-linha) for par, atribuir -2
                {
                    matriz_a[linha][coluna] = -2;
                }
                else
                // SENAO, atribuir 1
                {
                    matriz_a[linha][coluna] = 1;
                }
            }
            else
            // SENAO, atribuir  0
            {
                matriz_a[linha][coluna] = 0;
            }
        }
        // Atribuir chute inicial para todos os x = 0
        vetor_x[linha] = 0;
    }
    // Exibir a matriz aumentada
    printf("MATRIZ AUMENTADA: \n");
    for (int linha = 0; linha < dimensao; linha++)
    // Percorrer todas as linhas da matriz aumentada
    {
        printf("| ");
        for (int coluna = 0; coluna < dimensao; coluna++)
        // Percorrer todas as colunas da matriz_a
        {
            if (matriz_a[linha][coluna] >= 0) //Formatacao da array
            {
                printf(" ");
            }
            printf("%.0lf ", matriz_a[linha][coluna]); // Exibir valor do elemento[linha][coluna]
        }
        printf("| %.0lf  | \n", (linha + 1) % 2); // Exibir valor de b na linha: SE linha for par, b = 0; SENAO, b = 1
    }

    // Iteracoes do metodo gauss-seidel MODIFICADO
    for (int iteracao = 1; iteracao <= nMax; iteracao++)
    {
        bool atendeuPrecisao = true;
        for (int linha = 0; linha < dimensao; linha++)
        {
            erro_relativo[linha] = vetor_x[linha]; //Armazenando valor de x do passo anterior para calcular o erro relativo depois
            vetor_x[linha] = (linha + 1) % 2;      // 0 se linha for par, 1 se linha for impar
            for (int coluna = linha - 1; coluna <= linha + 1; coluna++)
            {
                if (coluna == linha || coluna < 0)
                {
                    continue;
                }
                vetor_x[linha] = vetor_x[linha] - (matriz_a[linha][coluna] * vetor_x[coluna]);
            }
            vetor_x[linha] = vetor_x[linha] / matriz_a[linha][linha];
            // Calculo do erro absoluto: Valor absoluto da subtraçao entre o x linha anterior (armazenado anteriormente) e o x linha encontrado no passo atual, dividido por x linha encontrado no passo atual
            erro_relativo[linha] = (erro_relativo[linha] - vetor_x[linha]) / vetor_x[linha];
            if (erro_relativo[linha] < 0)
            {
                erro_relativo[linha] *= -1;
            }
            //printf("Erro absoluto x%d: %lf \n", linha + 1, erro_absoluto[linha]);
            if (erro_relativo[linha] > precisao)
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
        printf("%lf", vetor_x[linha]);
        if (linha != dimensao - 1)
        {
            printf(", ");
        }
    }
    printf(" )t \n");
}