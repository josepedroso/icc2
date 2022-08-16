#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matriz.h"
#include "time.h"
#include "dados.h"
#include "math.h"
/**
 * @brief 
 *  realiza a retrossubstituicao
 * @param sis 
 */
void retrossubs(SL *sis) // realiza a retrossubstituicao
{
    for (int i = (sis->n) - 1; i >= 0; --i)
    {
        sis->X[i] = sis->B[i];
        for (int j = i + 1; j < sis->n; j++)
        {
            sis->X[i] -= sis->A[i][j] * sis->X[j];
        }
        sis->X[i] /= sis->A[i][i];
    }
}


void retrossubsinver(SL *sis)
{
    for (int i = 0 ; i < sis->n; i++)
    {
        sis->X[i] = sis->B[i];
        for (int j = 0; j < i; j++)
        {
            sis->X[i] -= sis->A[i][j] * sis->X[j];
        }
        sis->X[i] /= sis->A[i][i];
    }
}

/**
 * @brief 
 * 
 * @param sis 
 * @param linha_1 
 * @param linha_n 
 */
void trocalinha(SL *sis, int linha_1, int linha_n) // troca duas linhas dentro de um sistema linear
{
    double aux;
    for (int k = 0; k < sis->n; k++)
    {
        aux = sis->A[linha_1][k];
        sis->A[linha_1][k] = sis->A[linha_n][k];
        sis->A[linha_n][k] = aux;
    }
}
/**
 * @brief 
 * 
 * @param colun_inicial 
 * @param sis 
 */
void pivoteamento(int colun_inicial, SL *sis) //realiza o pivoteamento do sistema linear
{
    int maior_i = colun_inicial;
    for (int i = colun_inicial; i < sis->n; i++)
    {
        if (sis->A[i][colun_inicial] > sis->A[maior_i][colun_inicial])
        {
            maior_i = i;
        }
    }
    trocalinha(sis, colun_inicial, maior_i);
}
/**
 * @brief 
 * 
 * @param sis 
 */
void eliminacaoGauss(SL *sis) //realiza a eliminacao de ga
{

    for (int i = 0; i < sis->n; i++)
    {
        pivoteamento(i, sis);
        for (int j = i + 1; j < sis->n; j++)
        {
            double m = sis->A[j][i] / sis->A[i][i];
            sis->A[j][i] = 0.0;
            for (int k = i + 1; k < sis->n; k++)
            {
                sis->A[j][k] -= sis->A[i][k] * m;
            }
            sis->B[j] -= sis->B[i] * m;
        }
    }
}
/**
 * @brief 
 * 
 * @param v1 
 * @param v2 
 * @param tam 
 * @return double* 
 */
double *sub_vetor(double *v1, double *v2, int tam)
{ // subtrai vetor
    double *v_resul = aloca_vetor(tam);
    for (int i = 0; i < tam; i++)
    {
        v_resul[i] = v1[i] - v2[i];
    }
    return v_resul;
} // ax-b
/**
 * @brief 
 * 
 * @param v1 
 * @param v2 
 * @param tam 
 * @return double* 
 */
double *soma_vetor(double *v1, double *v2, int tam)
{ // soma o x anterior ao w  x(i)+w
    double *v_result = aloca_vetor(tam);
    for (int i = 0; i < tam; i++)
    {
        v_result[i] = v1[i] + v2[i];
    }
    return v_result;
}


void soma_matriz(double **m1, double **m2, int tam)
{ // soma o x anterior ao w  x(i)+w
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            m1[i][j] = m1[i][j] + m2[i][j];
        }        
    }
}
