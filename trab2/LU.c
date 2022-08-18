#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matriz.h"
#include "LU.h"
#include "utils.h"
#include <math.h>

#define EPLISON1 1.0e-15
#define EPLISON2 0.001
#define c_max 10

void iniSisLU(LU *sis, double coef_max)
{
    int n = sis->n;
    // para gerar valores no intervalo [0,coef_max]
    double invRandMax = ((double)coef_max / (double)RAND_MAX);

    // inicializa sistema normal
    // inicializa a matriz A
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            sis->U[i][j] = (double)rand() * invRandMax;
        }
        sis->X[i] = 0.0;
        sis->L[i][i] = 1;
    }
}
/**
 * @brief
 *
 * @param argumentos
 * @return LU*
 */
LU *aloca_LU(args *argumentos) // aloca  o sistema lu
{
    int tam;
    argumentos->N ? tam = argumentos->N : fscanf(argumentos->IN, "%d ", &tam);
    LU *sist = malloc(tam * tam * sizeof(LU *));
    sist->n = tam;

    sist->L = aloca_matriz(sist->n);
    sist->U = aloca_matriz(sist->n);
    sist->I = aloca_matriz(sist->n);
    sist->X = aloca_vetor(sist->n);

    return sist;
}
/**
 * @brief
 *
 * @param tam
 * @return double**
 */
double **matriz_inicial(int tam) // insere matriz inicial do sistema lu
{
    double **m = aloca_matriz(tam);
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            if (i == j)
            {
                m[i][j] = 1.0;
            }
            else
            {
                m[i][j] = 0.0;
            }
        }
    }
    return m;
}

/**
 * @brief
 *
 * @param sis
 * @param m
 */
void preenche_mId(LU *sis, double **m) // preenche a matriz identidade de lu
{
    sis->I = copia_matriz(m, sis->n);
}

/**
 * @brief
 *
 * @param sis
 * @param m
 * @param argumentos
 */
void preenche_LU_Inicial(LU *sis, double **m, args *argumentos) // preeenche sistema lu inicial com a entrada padrao
{
    if (argumentos->N)
    {
        iniSisLU(sis, c_max);
        preenche_mId(sis, m);
        return;
    }
    for (int i = 0; i < sis->n; i++)
    {
        for (int j = 0; j < sis->n; j++)
        {
            fscanf(argumentos->IN, "%lf ", &(sis->U[i][j]));
        }
        sis->X[i] = 0.0;
        sis->L[i][i] = 1;
    }
    preenche_mId(sis, m);
}
/**
 * @brief
 *
 * @param sis
 * @param mI
 * @param A
 */
void preenche_LU(LU *sis, double **mI, double **A) // preenche o sistema LU com a entrada de entrada e a matriz inversa cakculada
{

    for (int i = 0; i < sis->n; i++)
    {
        for (int j = 0; j < sis->n; j++)
        {
           
                sis->L[i][j] = 0;
            //A[i][j] = sis->U[i][j];
            sis->U[i][j] = A[i][j];
        }
                sis->L[i][i] = 1;

        sis->X[i] = 0.0; // Zera os valores de X
    }
    preenche_mId(sis, mI);

}
/**
 * @brief
 *
 * @param sis
 * @param linha_1
 * @param linha_n
 */
void trocalinhaLU(LU *sis, int linha_1, int linha_n) // troca linha de todos os sistemas  L / Y / I
{
    double aux1, aux2, aux3;
    for (int k = 0; k < sis->n; k++)
    {
        aux1 = sis->U[linha_1][k];
        sis->U[linha_1][k] = sis->U[linha_n][k];
        sis->U[linha_n][k] = aux1;

        aux2 = sis->L[linha_1][k];
        sis->L[linha_1][k] = sis->L[linha_n][k];
        sis->L[linha_n][k] = aux2;

        aux3 = sis->I[linha_1][k];
        sis->I[linha_1][k] = sis->I[linha_n][k];
        sis->I[linha_n][k] = aux3;
    }
}
/**
 * @brief
 *
 * @param colun_inicial
 * @param sis
 */
void pivoteamentoLU(int colun_inicial, LU *sis) // realiza o pivoteamento
{
    int maior_i = colun_inicial;
    for (int i = colun_inicial; i < sis->n; i++)
    {
        if (fabs(sis->U[i][colun_inicial]) > fabs(sis->U[maior_i][colun_inicial]))
        {
            maior_i = i;
        }
    }
    trocalinhaLU(sis, colun_inicial, maior_i);
}
/**
 * @brief
 *
 * @param sis
 * @param argumentos
 */
void FatoracaoLU(LU *sis, args *argumentos) // converte a matriz entrada em matriz U E L  acomapanhada do pivoteamento
{

    for (int i = 0; i < sis->n; i++)
    {
        pivoteamentoLU(i, sis); // realiza o pivoteamento
        for (int j = i + 1; j < sis->n; j++)
        {
            double m = sis->U[j][i] / sis->U[i][i];
            sis->U[j][i] = 0.0;
            sis->L[j][i] = m;
            for (int k = i + 1; k < sis->n; k++)
            {
                sis->U[j][k] -= sis->U[i][k] * m;
            }
        }
    }

    for (int i = 0; i < sis->n; i++)
    {
        for (int j = i + 1; j < sis->n; j++)
        {
            sis->L[i][j] = 0.0;
        }
        sis->L[i][i] = 1.0;
    }
}
/**
 * @brief
 *
 * @param Iden
 * @param v
 * @param coluna
 * @param tam
 */
void convert_M_to_V(double **Iden, double *v, int coluna, int tam) // converte uma coluna de uma matriz em um vetor
{
    for (int i = 0; i < tam; i++)
    {
        v[i] = Iden[i][coluna];
    }
}
/**
 * @brief
 *
 * @param lu
 * @param sis
 * @param m
 * @param v
 */
void convert_LU_SL(LU *lu, SL *sis, double **m, double *v)
{ // copia o sistema seja L ou U para sistema linear e seus vetores
    sis->n = lu->n;
    sis->A = copia_matriz(m, sis->n);
    sis->B = copia_vetor(v, sis->n);
    for (int i = 0; i < lu->n; i++)
    {
        sis->X[i] = 0.0;
    }
}
/**
 * @brief
 *
 * @param m
 * @param v
 * @param coluna
 * @param tam
 */
void convert_V_to_M(double **m, double *v, int coluna, int tam) // converte um vetor em uma coluna de uma matriz
{
    for (int i = 0; i < tam; i++)
    {
        m[i][coluna] = v[i];
    }
}
/**
 * @brief
 *
 * @param lu
 * @param argumentos
 * @return double**
 */
double **resolve_sisL(LU *lu, args *argumentos) // resolve Ly
{
    SL *sis = aloca_sist(lu->n);
    double *v = aloca_vetor(lu->n);
    double **m = aloca_matriz(lu->n);
    for (int colunaI = 0; colunaI < lu->n; colunaI++) //// converte cada coluna da matriz LU->I em sisU->X;
    {
        convert_M_to_V(lu->I, v, colunaI, lu->n); // coverte lu->I[i][coluna] em sisU->X
        convert_LU_SL(lu, sis, lu->L, v);         // Converte em sistema lu->U em sisU->A
        retrossubsinver(sis);
        convert_V_to_M(m, sis->X, colunaI, lu->n);
    }
    return m;
}
/**
 * @brief
 *
 * @param lu
 * @param argumentos
 * @return double**
 */
double **resolve_sisU(LU *lu, args *argumentos) // converte o sistema LU em sisU-> e realiza a eliminacao de gauss para resolver o sistema linear
{
    SL *sis = aloca_sist(lu->n);
    double *v = aloca_vetor(lu->n);
    double **m = aloca_matriz(lu->n);
    for (int colunaI = 0; colunaI < lu->n; colunaI++) // converte cada coluna da matriz Ly->I em sisU->X;
    {
        convert_M_to_V(lu->I, v, colunaI, lu->n);
        convert_LU_SL(lu, sis, lu->U, v);          // coverte lu->I[i][coluna ] em sisU->X
        retrossubs(sis);                           // realiza a retrosubstituicao obtendo um conjunto de n vetores que unidos geram a matriz inversa
        convert_V_to_M(m, sis->X, colunaI, lu->n); // une os vetores resultantes e gera a matriz inversa
    }
    return m;
}
/**
 * @brief
 *
 * @param lu
 * @param argumentos
 * @return double**
 */
double **resolveLU(LU *lu, args *argumentos) // resolve o sistema Ly e U  dando origem a matriz identidade a partir da resolucao dos sistemas
{
    lu->I = copia_matriz(resolve_sisL(lu, argumentos), lu->n); // calcula sis->X[I] que entra como sis->B[I] no sistema lu

    double **matriz_Inv = resolve_sisU(lu, argumentos); // resolve sisU com sisU->B = sisL->I
    return matriz_Inv;
}
/**
 * @brief
 *
 * @param result
 * @param m
 * @param mInv
 * @param tam
 */
void matriz_residuo(double **result, double **m, double **mInv, int tam) // realiza a operacao de multiplicao e subtracao de matrizes
{

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < tam; k++)
            {
                result[i][j] += m[i][k] * mInv[k][j]; // A*A'
            }
            result[i][j] = (i == j ? 1.0 - (result[i][j]) : -(result[i][j])); // ao fazer assim dispensa a identidade
            // R = IDENTIDADE - A*A'
        }
    }
}
/**
 * @brief
 *
 * @param result
 * @param m
 * @param mInv
 * @param tam
 */
void matriz_mult(double **result, double **m, double **mInv, int tam) // realiza a multiplicacao de duas matrizes
{

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < tam; k++)
            {
                result[i][j] += m[i][k] * mInv[k][j];
            }
        }
    }
}
/**
 * @brief
 *
 * @param m
 * @param tam
 * @param it
 * @param out
 * @return double
 */
double Norma_LU(double **m, int tam, int it, FILE *out) // calcula a norma lu somando os valores do do residuo elevados ao quadrado
{
    double soma = 0;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            soma = soma + (m[i][j] * m[i][j]);
        }
    }
    soma = sqrt(soma);
    fprintf(out, "# iter %d: <%.15g>\n", it, soma);
    return soma;
}

/**
 * @brief auxiliar do determinante
 * 
 * @param mat matriz do determinante
 * @param temp matriz temporaria auxiliar
 * @param p 
 * @param q 
 * @param n 
 */
void functionAuxiliarDet(double **mat, double **temp, int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/**
 * @brief usa a matriz como triangular superior usando propriedades dos determinantes, o determinante da matriz triangular superior é o produto de todos os elementos diagonais 
 * 
 * @param mat 
 * @param n 
 * @return int 
 */
int achaDeterminante(double **mat, int n)
{
    int D = 0;// determinante

    double **matrizA = aloca_matriz(n);

    int sinal = 1;// sinal da multiplicacao

    //calcula o determinante recursivamente
    for (int f = 0; f < n; f++)
    {
        functionAuxiliarDet(mat, matrizA, 0, f, n);
        D += sinal * mat[0][f] * achaDeterminante(matrizA, n - 1);
        sinal = -sinal;
    }
    return D;
}

/**
 * @brief
 *
 * @param argumentos
 */
void refLU(args *argumentos)
{

    double tLU, sLU = 0;
    double tSL, sSL = 0;
    double tR, sR = 0;

    int it = 1;

    LU *lu = aloca_LU(argumentos);

    double **matrizA = aloca_matriz(lu->n);
    double **matriz_Inv = aloca_matriz(lu->n);
    double **matriz_Inv_n = aloca_matriz(lu->n);
    double **mResiduo = aloca_matriz(lu->n);
    double **Identidade = aloca_matriz(lu->n);

    double norma = 1;

    Identidade = matriz_inicial(lu->n);              // matriz identidade inicial
    preenche_LU_Inicial(lu, Identidade, argumentos); // preenche matriz U antes do pivoteamento

    matrizA = copia_matriz(lu->U, lu->n); // salva matriz de entrada
    
    /*
    if (achaDeterminante(matrizA, lu->n) < EPLISON1)// ve se eh invertivel
    {
        perror("A MATRIZ NAO EH INVERSIVEL");
        exit(-1);
    }
    */
    tLU = timestamp();
    FatoracaoLU(lu, argumentos); // converte a matriz L e U EM DOIS SISTEMAS LINEARES
    tLU = timestamp() - tLU;
    sLU += tLU;

    tSL = timestamp();
    matriz_Inv = resolveLU(lu, argumentos);
    tSL = timestamp() - tSL;
    sSL += tSL;

    fprintf(argumentos->OUT, "#\n");

    lee_matriz(matriz_Inv, lu->n, argumentos->OUT);

    do
    {
        tR = timestamp();
        matriz_residuo(mResiduo, matrizA, matriz_Inv, lu->n); // R = I − A∗A−1
        tR = timestamp() - tR;
        sR += tR;

        norma = Norma_LU(mResiduo, lu->n, it, argumentos->OUT); // ||R|| = ∑R[i,j]2
        if (norma < EPLISON1)
        {
            break;
        }

        // Nova matriz inversa R = A ∗ W−1
        preenche_LU(lu, mResiduo, matrizA);
        tLU = timestamp();
        FatoracaoLU(lu, argumentos); // converte a matriz L e U EM DOIS SISTEMAS LINEARES
        tLU = timestamp() - tLU;
        sLU += tLU;

        tSL = timestamp();
        matriz_Inv_n = resolveLU(lu, argumentos);
        tSL = timestamp() - tSL;
        sSL += tSL;

        // Soma matrizes para aproximar do valor verdadeiro
        soma_matriz(matriz_Inv_n, matriz_Inv, lu->n);
        matriz_Inv = copia_matriz(matriz_Inv_n, lu->n);
        //lee_matriz(matriz_Inv_n, lu->n, argumentos->OUT);

        it = it + 1;
    } while (it < argumentos->K);

    print_tempo(argumentos->OUT, it, sLU, sSL, sR);
    lee_matriz(matriz_Inv, lu->n, argumentos->OUT);
}

/**
 * @brief
 *
 * @param sis
 */
void print_tempo(FILE *out, int it, double sLU, double sSL, double sR)
{
    fprintf(out, "# Tempo LU: <%.15g>\n", sLU / it);
    fprintf(out, "# Tempo iter: <%.15g>\n", sSL / it);
    fprintf(out, "# Tempo residuo: <%.15g>\n", sR / it);
    fprintf(out, "#\n");
}