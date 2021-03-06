#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int ThreeNPlusOne_Recursive(int n){
    if (n== 1)printf("%d.\n",n);
    else printf("%d,",n);
    if (n== 1) return 1;
    else if(n % 2 == 1) return ThreeNPlusOne_Recursive(3*n + 1) + 1;
    else return ThreeNPlusOne_Recursive(n/2) + 1;
}

int main(int argc,char *argv[]){
    char *n = argv[1];
    if (atoi(n) <= 0) {
        printf("error n\n");
        return 1;
    }
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) {
        ThreeNPlusOne_Recursive(atoi(n));
    }
    else {
        wait(NULL);
        printf("Child Complete\n");
    }
    return 0;
}