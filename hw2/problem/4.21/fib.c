#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

int *seq;
int count;

int fib(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fib(n-1) + fib(n-2);
}

int GetFibSeq(int nums){
    for (int i=0;i<nums;i++){
        seq[i] = fib(i);
    }
}

int main(int argc,char *argv[]){
    int n = atoi(argv[1]);
    count = 0;
    seq = (int *)malloc(n * sizeof(int));
    GetFibSeq(n);
    for (int i=0;i<n;i++){
        printf("%d ",seq[i]);
    }
    return 0;
}