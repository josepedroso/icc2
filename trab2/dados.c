#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matriz.h"
#include "dados.h"
#include <string.h>
#include <unistd.h>

/**
 * @brief TRATA OS ARGUMENTOS VINDO DO USUARIO SENDO ESTES -e PARA ENTRADA NÃO PADRÃO
 * , -s PARA SAIDA NÃO PADRÃO, -r PARA TAMANHO DE UMA MATRIZ RANDOMICA E -i PARA NUMERO MAX DE ITERAÇÕES SEMPRE > 0
 * 
 * @param argc 
 * @param argv 
 * @param argumentos ESTRUTURA DE DADOS PARA OS ARGUMENTOS
 */
void trata_args(int argc, char **argv, args *argumentos)
{
    int opt;

    //TRATAMENTO DOS ARGUMENTOS DE ENTRADA E SETAGEM DA STRUCT ARGS
    while ((opt = getopt(argc, argv, "e:s:r:i")) != -1)
    {
        switch (opt)
        {
        case 'e':
            argumentos->IN = fopen(argv[optind - 1], "r");
            if (!argumentos->IN)
            {
                perror("ERRO AO ABRIR ARQUIVO DE ENTRADA");
                exit(-1);
            }
            break;
        case 's':
            argumentos->OUT = fopen(argv[optind - 1], "w");
            if (!argumentos->OUT)
            {
                perror("ERRO AO ABRIR ARQUIVO DE SAIDA");
                exit(-1);
            }
            break;
        case 'r':
            if (atoi(argv[optind - 1]) <= 0)
            {
                perror("PARAMETRO VAZIO OU INVALIDO EM -r, DEVE SEMPRE PASSAR UM INTEIRO > 0");
                exit(-1);
            }
            argumentos->N = atoi(argv[optind - 1]);
            break;
        case 'i':
            if (!argv[optind] || strlen(argv[optind]) == 0)
            {
                perror("PARAMETRO VAZIO EM -i");
                exit(-1);
            }
            argumentos->K = atoi(argv[optind]);
            if (argumentos->K <= 0)
            {
                perror("PARAMETRO INVALIDO EM -i, DEVE SEMPRE PASSAR UM INTEIRO > 0");
                exit(-1);
            }

            break;
        }
    }
    if (!argumentos->K)
    {
        perror("FALTA DO PARAMETRO -i, SEMPRE DEVE SER EXECUTADO COM -i");
        exit(-1);
    }
    if (argumentos->N && argumentos->IN != NULL)//CASO TENHA -e E -r
        argumentos->IN = stdin;
    if (argumentos->IN == NULL)//CASO NÃO TENHA -e
        argumentos->IN = stdin;
    if (argumentos->OUT == NULL)//CASO NÃO TENHA -s
        argumentos->OUT = stdout;
}

/**
 * @brief ALOCA UM VETOR DE TAM N DO TIPO DOUBLE
 * 
 * @param n TAMANHO DO VETOR
 * @return double* 
 */
double *aloca_vetor(int n)
{
    double *v;

    v = (double *)malloc(n * sizeof(double *));
    if (v == NULL)
    {
        perror("Memoria insuficiente");
        exit(1);
    }
    return v;
}

/**
 * @brief ALOCA UMA MATRIZ N*N DO TIPO DOUBLE
 * 
 * @param n TAMANHO DE UMA MATRIZ N*N 
 * @return double** 
 */
double **aloca_matriz(int n)
{
    double **m;
    int len = sizeof(double *) * n + sizeof(double) * n * n;
    m = (double **)malloc(len);
    if (m == NULL)
    {
        perror("Memoria insuficiente");
        exit(1);
    }

    double *b = (double *)(m+n);

    for(int i = 0; i < n; i++)
        m[i] = (b + n * i);
    
    return m;
}

/**
 * @brief FUNCTION PARA ALOCAR SISTEMA  
 * 
 * @return SL* 
 */
SL *aloca_sist(int n)
{

    SL *sist = malloc(n * n *  sizeof(SL *));
    sist->n = n;
    sist->A = aloca_matriz(sist->n);
    sist->B = aloca_vetor(sist->n);
    sist->X = aloca_vetor(sist->n);

    return sist;
}


/**
 * @brief PRINTA SISTEMA MATRIZ A / VERTOR B / VETOR X 
 * 
 * @param sis 
 */
void lee_sis(SL *sis, FILE *out)
{
    for (int i = 0; i < sis->n; i++)
    {
        for (int j = 0; j < sis->n; j++)
        {
            fprintf(out, "%lf ", (sis->A[i][j]));
        }
        fprintf(out, " B %lf", sis->B[i]);
        fprintf(out, " X %lf", sis->X[i]);
        fprintf(out, "\n");
    }
}

/**
 * @brief PRINTA MATRIZ
 * 
 * @param m MATRIZ
 * @param n TAMANHO DA MATRIZ
 */
void lee_matriz(double **m, int n, FILE *out)
{
    fprintf(out,"%d \n", n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(out, "%.15g ", (m[i][j]));
        }
        fprintf(out,"\n");
    }
    fprintf(out,"\n");
}

/**
 * @brief PRINTA VETOR
 * 
 * @param v VETOR
 * @param n TAMANHO N
 */
void lee_vetor(double *v, int n)
{

    for (int i = 0; i < n; i++)
    {

        printf("%lf ", (v[i]));
    }
    printf("\n");
}

/**
 * @brief COPIA E RETORNA A MATRIZ COPIADA
 * 
 * @param matriz_original MATRIZ A SER COPIADA
 * @param tam TAMANHO DA MATRIZ N*N
 * @return double** 
 */
double **copia_matriz(double **matriz_original, int tam)
{
    double **m;
    m = aloca_matriz(tam);
    for (int k = 0; k < tam; k++)
    {
        for (int w = 0; w < tam; w++)
        {
                //printf("%lf \n", matriz_original[w][k]);

            m[k][w] = matriz_original[k][w];
        }
    }
    return m;
}

/**
 * @brief COPIA VETOR
 * 
 * @param vetor 
 * @param tam VETOR TAMANHO
 * @return double* 
 */
double *copia_vetor(double *vetor, int tam)
{
    double *v;
    v = aloca_vetor(tam);
    for (int w = 0; w < tam; w++)
    {
        v[w] = vetor[w];
    }
    return v;
}


/**
 * @brief 
 * 
 * @param sis 
 * @param vetor 
 * @return SL* 
 */
SL *copia_sl(SL *sis, double *vetor)
{
    SL *novo_sis = aloca_sist(sis->n);

    novo_sis->A = copia_matriz(sis->A, sis->n);
    novo_sis->B = copia_vetor(vetor, sis->n);
    novo_sis->n = sis->n;

    return novo_sis;
}

