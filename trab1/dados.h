#ifndef __DADOS__
#define __DADOS__

#include <stdio.h>
#include <unistd.h>

/**
 * @brief ESTRUTURA PARA TRATAR ENTRADAS
 * 
 */
typedef struct args{
    FILE *IN;
    FILE *OUT;
    int N;
    int K;
}args;

//* TRATAMENTO DE ENTRADA *//
/**
 * @brief TRATA OS ARGUMENTOS VINDO DO USUARIO SENDO ESTES -e PARA ENTRADA NÃO PADRÃO
 * , -s PARA SAIDA NÃO PADRÃO, -r PARA TAMANHO DE UMA MATRIZ RANDOMICA E -i PARA NUMERO MAX DE ITERAÇÕES SEMPRE > 0
 * 
 * @param argc 
 * @param argv 
 * @param argumentos ESTRUTURA DE DADOS PARA OS ARGUMENTOS
 */
void trata_args(int argc, char **argv, args *argumentos);


//* ALOCACOES *//

/**
 * @brief ALOCA UM VETOR DE TAM N DO TIPO DOUBLE
 * 
 * @param n TAMANHO DO VETOR
 * @return double* 
 */
double *aloca_vetor(int n);

/**
 * @brief ALOCA UMA MATRIZ N*N DO TIPO DOUBLE
 * 
 * @param n TAMANHO DE UMA MATRIZ N*N 
 * @return double** 
 */
double **aloca_matriz(int n);

/**
 * @brief FUNCTION PARA ALOCAR SISTEMA  
 * 
 * @return SL* 
 */
SL *aloca_sist(int n);

//* PRINTS *//

/**
 * @brief PRINTA MATRIZ
 * 
 * @param m MATRIZ
 * @param n TAMANHO DA MATRIZ
 */
void lee_matriz(double **m, int n, FILE *out);

/**
 * @brief PRINTA VETOR
 * 
 * @param v VETOR
 * @param n TAMANHO N
 */
void lee_vetor(double *v, int n);


/**
 * @brief PRINTA SISTEMA MATRIZ A / VERTOR B / VETOR X 
 * 
 * @param sis 
 */
void lee_sis(SL *sis, FILE *out);

//* COPIA INFORMACOES PARA UM RECEPTOR *//
/**
 * @brief COPIA E RETORNA A MATRIZ COPIADA
 * 
 * @param matriz_original MATRIZ A SER COPIADA
 * @param tam TAMANHO DA MATRIZ N*N
 * @return double** 
 */
double **copia_matriz(double **matriz_original, int tam);

/**
 * @brief COPIA VETOR
 * 
 * @param vetor 
 * @param tam VETOR TAMANHO
 * @return double* 
 */
double *copia_vetor(double *vetor, int tam);

/**
 * @brief 
 * 
 * @param sis 
 * @param vetor 
 * @return SL* 
 */
SL *copia_sl(SL *sis, double *vetor);

#endif