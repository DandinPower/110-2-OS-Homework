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
        fflush(stdout);
        gets(input);
        char *p = strtok(input, " ");
        int i = 0;
        args[i] = p;
        while(p != NULL){
            i++;
            p = strtok(NULL, " ");
            args[i] = p;
        }
        if (i ==0) continue;
        //args已經完成
        if (strcmp(args[0],"exit")==0){
            break;
        }
        int isWait = 1;
        if (strlen(args[i-1])==1 && args[i-1][0] == '&'){
            isWait = 0;
            args[i-1] = NULL;
        }
        else{
            args[i] = NULL;
        }
        pid_t pid;
        pid = fork();
        if(pid < 0) {
            printf("FORK FAILED\n");
            return 1;
        }
        else if (pid == 0) {
            if(execvp(args[0], args)){
                printf("WRONG COMMAND\n");
                return 1;
            }
        }
        else {
            if(isWait){
                while(wait(NULL) != pid);
                printf("Child COMPLETE\n");
            }
            else{
                printf("ROOT COMPLETE\n");
            }  
        }
    }
    return 0;
}