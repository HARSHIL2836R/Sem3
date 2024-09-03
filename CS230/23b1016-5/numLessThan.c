#include <stdio.h>

typedef struct {

int re; int im;

} complex;

complex A[4] = { {0,0}, {-1,2}, {0,2}, {-1,-1} };

int len=4;

int isLessThan(complex e1, complex e2){
    return (e1.re < e2.re) || (e1.re == e2.re && e1.im < e2.im);
}

int numLessThan(complex elt, complex* A, int start, int end){
    int count = 0;
    int index = start;
    while (index != end){
        if (isLessThan(A[index],elt)){
            count++;
        }
        index ++;
    }
    return count;
}

int main(){
    complex x;
    x.re = 1;
    x.im = 1;
    int result = numLessThan(x,&A,0,len);
}