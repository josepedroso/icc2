#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "matriz.h"
#include "dados.h"
#include "LU.h"

#define EPLISON1 0.00001
#define EPLISON2 0.00001
// f == function

int main(int argc, char **argv)
{
    // inicializa gerador de números aleatóreos
    srand(202201);
    args *argumentos = (args *)malloc(sizeof(args *));

    trata_args(argc, argv, argumentos);
    refLU(argumentos);
}