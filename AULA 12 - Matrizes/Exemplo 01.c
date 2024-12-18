#include <stdio.h>
#include <stdlib.h>

void soma(int A[3], int i){
    printf("%d", A[0]);
    A[0]=5;
}

void main(){
    int i = 3;
    int A[3]={0,1,2};
    printf("%d", A[0]);
    soma(A,i);
    printf("%d", A[0]);
}