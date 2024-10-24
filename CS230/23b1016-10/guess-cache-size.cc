#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(){
    FILE *stream = fopen("time.txt","w");
    struct timeval start,end;
    for (int guess_size = 1024*2; guess_size <= 1024*1024*5 ; guess_size = guess_size*2){
        int ARRAY_SIZE = guess_size/4;
        int A[ARRAY_SIZE];
        printf("Guess size: %d\n",guess_size);
        double duration = 0;int j = 0;
        for (int i = 0; j < 100; i = ARRAY_SIZE*(rand()/(1.0*RAND_MAX))){
            int a;
            printf("%d\n",i);
            gettimeofday(&start,NULL);
            a = A[i] + 1;
            gettimeofday(&end,NULL);
            duration += end.tv_usec - start.tv_usec;
            j++;
        }
        duration = duration/j;
        fprintf(stream,"%f\n",duration);
    }
    fclose(stream);
}