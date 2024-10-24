#include <time.h>
#include <stdio.h>
#define SIZE 100
double A[SIZE][SIZE] = {0.0}, B[SIZE][SIZE] = {0.0}, C[SIZE][SIZE]={0.0};

double mul(){
    clock_t start = clock();
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
                A[i][j] = A[i][j] + B[i][k]*C[k][j];
            }
        }
    }
    clock_t end = clock();
    double duration = (double)(end - start)/CLOCKS_PER_SEC;
    return duration;
}
void cache_check(){
    for (int i = 0; i < SIZE; i++){
        fprintf(stderr, "Index %d\n", i);
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
                printf("%d %p\n",0,(double*)&B[i][k]);
                printf("%d %p\n",0,(double*)&C[k][j]);
                printf("%d %p\n",0,(double*)&A[i][j]);
                A[i][j] = A[i][j] + B[i][k]*C[k][j];
                printf("%d %p\n",1,(double*)&A[i][j]);
            }
        }
    }
}
int main(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (i == j) B[i][j] = 2;
            if (i == 0) C[i][j] = j;
        }   
    }
    FILE *stream = fopen("run.out","w");
    for (int a = 0; a < 5; a++)
    {
        fprintf(stream,"Run %d: %.6f seconds\n",a+1,mul());
    }
    fclose(stream);
    cache_check();
}