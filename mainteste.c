#include <stdio.h>
#include <stdlib.h>
//https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
//4) Using double pointer and one malloc call 
double **aloca_matriz(int n)
{
    double **m;
    int i;
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

int main(){
    double ** m = aloca_matriz(3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m[i][j] = 1+i+j;
        }
    }

    fprintf(stdout,"3 \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fprintf(stdout, "%.15g ", (m[i][j]));
        }
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
    /*
    */
}