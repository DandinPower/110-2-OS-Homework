#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LEN 80

int main(void){
    while(1){
        char *args[MAX_LEN/2 + 1];
        char input[MAX_LEN];
        printf("osh>");
        gets(input);
        char *p = strtok(input, " ");
        int i = 0;
        args[i] = p;
        while(p != NULL){
            i++;
            p = strtok(NULL, " ");
            args[i] = p;
        }
        args[i+1] = NULL;
        //args已經完成
        pid_t pid;
        pid = fork();
        if (pid == 0) {
            for(int j=0;j<=i;j++){
                printf("%s\n",args[j]);
            }
        }
        else {
            /*
            if (strcmp(args[i], "&")){
                wait(NULL);
                printf("%s\n",args[i]);
                printf("Child Complete\n");
            }*/
        }

    }
    return 0;
}