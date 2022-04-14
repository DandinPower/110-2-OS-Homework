#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

int n;
int *seq;

void *runner(void *param);

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

void *runner(void *param){
    int n = atoi(param);
    GetFibSeq(n);
    pthread_exit(0);
}

int main(int argc,char* argv[]){
    int n = atoi(argv[1]);
    seq = (int *)malloc(n * sizeof(int));
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid,NULL);
    for (int i=0;i<n;i++){
        printf("%d ",seq[i]);
    }
    printf("\n");
    return 0;
}