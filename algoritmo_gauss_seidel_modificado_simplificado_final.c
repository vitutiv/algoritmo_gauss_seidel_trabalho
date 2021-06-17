#include <stdio.h>
#include <stdbool.h>
int main()
{
    /*
        nMax: Criterio de parada - numero maximo de iteracoes do metodo de gauss-seidel
        precisao: Criterio de parada - erro relativo do metodo de gauss-seidel
        dimensao: dimensao da matriz_a nxn e quantidade de incognitas das equacoes lineares
    */
    int nMax = 1000;
    double precisao = 0.000001;
    int dimensao = 30;
    /*  
        matriz_a = armazenam os valores de a[linha, coluna] (NAO USADO DIRETAMENTE NO CODIGO, POIS matriz_a[linha][linha-1] e matriz_a[linha][linha+1] sempre = 1, matriz_a[diagonal_principal] sempre = -2, e demais valores sempre = 0).; 
        vetor_b: armazena os valores de b[linha] (NAO USADO DIRETAMENTE NO CODIGO, POIS iniciando de b[1] ate b[n-2] sempre = 0 e b[0], b[n] = 1) 
        vetor_x: armazena os valores aproximados de x, encontrados em cada passo. Ao fim do programa, ele armazena a ultima solucao encontrada.
        erro_relativo: armazena o erro relativo de x no passo, pelo calculo | ( x_passo_anterior - x_passo_atual ) / x(passo_atual) |. Ao fim do programa, ele armazena os ul
    */
    double vetor_x[dimensao], erro_relativo[dimensao];
    // Popular a matriz aumentada
    for (int linha = 0; linha < dimensao; linha++)
    {
        // Atribuir chute inicial para todos os x = 0
        vetor_x[linha] = 0;
    }
    // Exibir a matriz aumentada
    printf("MATRIZ AUMENTADA: \n");
    int valor_elemento;
    for (int linha = 0; linha < dimensao; linha++)
    // Percorrer todas as linhas da matriz aumentada
    {
        printf("| ");
        for (int coluna = 0; coluna < dimensao; coluna++)
        // Percorrer todas as colunas da matriz_a
        {
            if (coluna >= linha - 1 && coluna <= linha + 1)
            // SE coluna estiver entre o intervalo [ linha-1, linha+1 ], atribuir a matriz_a[linha][coluna] um dos valores abaixo:
            {
                if (coluna == linha)
                    // SE (coluna-linha) for par, atribuir -2
                    valor_elemento = -2;
                else
                    // SENAO, atribuir 1
                    valor_elemento = 1;
            }
            else
                // SENAO, atribuir  0
                valor_elemento = 0;
            printf("%d ", valor_elemento); // Exibir valor do elemento[linha][coluna]
        }
        int valor_b = 0; // Armazenando valor de x do passo anterior para calcular o erro relativo depois
        if (linha == 0 || linha == dimensao - 1)
            valor_b = 1;               //  Atribuir vetor_x[linha] = 0 (valor_b da linha)
        printf("| %d  | \n", valor_b); // Exibir valor de b na linha
    }
    // Iteracoes do metodo gauss-seidel MODIFICADO
    for (int iteracao = 1; iteracao <= nMax; iteracao++)
    {
        bool atendeuPrecisao = true;
        for (int linha = 0; linha < dimensao; linha++)
        {
            erro_relativo[linha] = vetor_x[linha]; //Armazenando valor de x do passo anterior para calcular o erro relativo depois
            vetor_x[linha] = 0;                    // Atribuir vetor_x[linha] = 0 (valor_b da linha)
            if (linha == 0 || linha == dimensao - 1)
                // Atribuir vetor_x[linha] = 1 (valor_b da linha)
                vetor_x[linha] = 1;
            for (int coluna = linha - 1; coluna <= linha + 1 && coluna < dimensao; coluna++) // Nas demais colunas, o valor de matriz_a[linha][coluna] sempre = 0, portanto podemos ignora-los.
            {
                if (coluna == linha || coluna < 0)
                    // Pular diagonal principal e pular caso excecao para a linha 0, em que coluna (linha - 1) poderia ser de indice -1.
                    continue;
                vetor_x[linha] -= (vetor_x[coluna]); // Para todos os valores fora da diagonal principal que nao sao 0, o valor de matriz_a[linha][coluna] eh sempre 1 e por isso pode ser omitido da multiplicacao
            }
            vetor_x[linha] /= -2; // Dividir pelo valor na diagonal principal (na diagonal principal de matriz_a, o valor sempre é -2);
            // Calculo do erro absoluto: Valor absoluto da subtraçao entre o x linha anterior (armazenado anteriormente) e o x linha encontrado no passo atual, dividido por x linha encontrado no passo atual
            erro_relativo[linha] = (erro_relativo[linha] - vetor_x[linha]) / vetor_x[linha];
            if (erro_relativo[linha] < 0)
                erro_relativo[linha] *= -1;
            //printf("Erro absoluto x%d: %lf \n", linha + 1, erro_absoluto[linha]);
            if (erro_relativo[linha] > precisao)
                atendeuPrecisao = false;
        }
        if (atendeuPrecisao)
        {
            printf("Criterio de precisao atendido na iteracao %d, parando execucao... \n", iteracao);
            break;
        }
    }
    // Resultado aproximado
    printf("SOLUCAO APROXIMADA DO SISTEMA: (");
    for (int linha = 0; linha < dimensao; linha++)
    {
        printf("%lf", vetor_x[linha]);
        if (linha != dimensao - 1)
            printf(", ");
    }
    printf(" )t \n");
}