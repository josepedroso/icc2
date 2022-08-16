#ifndef __MATRIZ__
#define __MATRIZ__
/**
 * @brief ESTRUTURA DO SISTEMA LINEAR
 * 
 */
typedef struct Sist_Linear{
    double **A;
    double *B;
    double *X;
    int n;
}SL;
/**
 * @brief RETROSUBISTITUICAO
 * 
 * @param sis 
 */
void retrossubs(SL * sis);

void retrossubsinver(SL *sis);

//* PIVOTEMAENTO *//

/**
 * @brief 
 * 
 * @param sis 
 * @param j 
 * @param i 
 */
void trocalinha(SL * sis,int j,int i);
/**
 * @brief 
 * 
 * @param colun_inicial 
 * @param sis 
 */
void pivoteamento(int colun_inicial,SL * sis);

//* GAUSS *//
/**
 * @brief 
 * 
 * @param sis 
 */
void eliminacaoGauss(SL * sis);

//* OPERACOES DE VETORES E MATRIZES *//
/**
 * @brief SUBTRAI DOIS VETORES
 * 
 * @param v1 
 * @param v2 
 * @param tam 
 * @return double* 
 */
double * sub_vetor (double * v1,double *v2,int tam);

/**
 * @brief COPIA SISTEMA LINEAR
 * 
 * @param sis 
 * @param vetor 
 * @return SL* 
 */
SL *copia_sl(SL * sis,double * vetor);

/**
 * @brief SOMA DOIS VETORES
 * 
 * @param v1 
 * @param v2 
 * @param tam 
 * @return double* 
 */
double * soma_vetor(double * v1,double * v2,int tam);

/**
 * @brief SOMA DUAS MATRIZES
 * 
 * @param mA 
 * @param mB 
 * @param tam 
 */
void soma_matriz(double **m1, double **m2, int tam);


#endif