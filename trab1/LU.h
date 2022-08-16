#ifndef __LU__
#define __LU__
#include "matriz.h"
#include "dados.h"
/**
 * @brief ESTRUTURA USADA PARA LU
 * 
 */
typedef struct Sist_LU
{
    double **L;
    double **U;
    double **I;
    double *X;
    int n;
} LU;

//* OPERACOES DE COPIA/ TRANSFORMACOES E PREENCHIMENTO DE ESTRUTURAS DE DADOS*//

/**
 * @brief converte uma coluna de uma matriz em um vetor
 * 
 * @param Iden 
 * @param v 
 * @param coluna 
 * @param tam 
 */
void convert_M_to_V(double **Iden, double *v, int coluna, int tam);

/**
 * @brief copia o sistema seja L ou U para sistema linear e seus vetores
 * 
 * @param lu 
 * @param sis 
 * @param m 
 * @param v 
 */
void convert_LU_SL(LU *lu, SL *sis, double **m, double *v);

/**
 * @brief converte um vetor em uma coluna de uma matriz
 * 
 * @param m 
 * @param v 
 * @param coluna 
 * @param tam 
 */
void convert_V_to_M(double **m, double *v, int coluna, int tam);

/**
 * @brief preeenche sistema lu inicial com a entrada padrao
 * 
 * @param sis 
 * @param m 
 * @param argumentos 
 */
void preenche_LU_Inicial(LU *sis, double **m, args *argumentos); 

/**
 * @brief insere matriz inicial do sistema lu
 * 
 * @param tam 
 * @return double** 
 */
double **matriz_inicial(int tam);                             


/**
 * @brief 
 * 
 * @param sis 
 * @param coef_max 
 */
void iniSisLU(LU * sis, double coef_max);

/**
 * @brief  preenche a matriz identidade de lu
 * 
 * @param sis 
 * @param m 
 */
void preenche_mId(LU *sis, double **m);

/**
 * @brief preenche o sistema LU com a entrada de entrada e a matriz inversa caLculada
 * 
 * @param sis 
 * @param mI 
 * @param A 
 */
void preenche_LU(LU *sis, double **mI, double **A);

//* ALOCAMENTO DE ESTRUTURAS DE DADOS*//

/**
 * @brief aloca  o sistema lu
 * 
 * @return LU* 
 */
LU *aloca_LU();

//* PIVOTEAMENTO *//

/**
 * @brief troca linha de todos os sistemas  L / Y / I
 * 
 * @param sis 
 * @param linha_1 
 * @param linha_n 
 */
void trocalinhaLU(LU *sis, int linha_1, int linha_n);

/**
 * @brief  realiza o pivoteamento
 * 
 * @param colun_inicial 
 * @param sis 
 */
void pivoteamentoLU(int colun_inicial, LU *sis);

//* RESOLVE L U *//

/**
 * @brief  converte a matriz entrada em matriz U E L  acomapanhada do pivoteamento
 * 
 * @param sis 
 * @param argumentos 
 */
void FatoracaoLU(LU *sis, args *argumentos);

//* FUNCTIONS SL *//

/**
 * @brief resolve Ly 
 * 
 * @param lu 
 * @param argumentos 
 * @return double** 
 */
double **resolve_sisL(LU *lu,args *argumentos);

/**
 * @brief converte o sistema LU em sisU-> e realiza a eliminacao de gauss para resolver o sistema linear
 * 
 * @param lu 
 * @param argumentos 
 * @return double** 
 */
double **resolve_sisU(LU *lu,args *argumentos);

/**
 * @brief RESOLVE O SISTEMA LINEAR
 * 
 * @param lu 
 * @param argumentos 
 * @return double** 
 */
double **resolveLU(LU *lu,args* argumentos);

//* RESIDUO E ||R||*//

/**
 * @brief CALCULA NORMA L2
 * 
 * @param m 
 * @param tam 
 * @param it 
 * @param out 
 * @return double 
 */
double Norma_LU(double **m, int tam, int it, FILE *out);

/**
 * @brief RESOLVE R = I − A ∗ A−1
 * 
 * @param result 
 * @param m 
 * @param mInv 
 * @param tam 
 */
void matriz_residuo(double **result, double **m, double **mInv, int tam);

//* FUNCTION PRINCIPAL *//

/**
 * @brief FUNCTION PRINCIPAL PARA REFINAMENTO E RESOLUCAO DO SISTEMA E DECOMPOSICAO LU
 * 
 * @param argumentos ENTRADAS
 */
void refLU(args *argumentos);

//* SAIDA *//

/**
 * @brief PRINTA A MEDIA DE TEMPO DO PROGRAMA POR FUNCAO
 * 
 * @param out //FILE DE SAIDA OU STDIN
 * @param it // NUMERO DE ITERACOES
 * @param sLU // SOMA DO TEMPO DE LU
 * @param sSL // SOMA DO TEMPO DE RESOLUCAO DO SISTEMA LINEAR
 * @param sR // SOMA DO TEMPO DO RESIDUO
 */
void print_tempo(FILE *out, int it, double sLU, double sSL, double sR);

//* OPERACOES DE COPIA/ TRANSFORMACOES E PREENCHIMENTO DE ESTRUTURAS DE DADOS*//

/**
 * @brief MULTIPLICA MATRIZ 
 * 
 * @param result MATRIZ QUE RECEBE MULTIPLICACAO
 * @param m  MATRIZ INICIAL
 * @param mInv MATRIZ INVERSA
 * @param tam TAMANHO DAS MATRIZES
 */
void matriz_mult(double **result, double **m, double **mInv, int tam);
#endif