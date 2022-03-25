#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LEN 80
char* history[10][MAX_LEN/2 + 1];
int historyWait[10];
//紀錄目前的指令數
int cmdCounter = 0;
void HistoryInitialize(void){
    for (int i=0;i<10;i++){
        for (int j=0;j<(MAX_LEN/2 + 1);j++){
            history[i][j] = NULL;
        }
        historyWait[i] = 0;
    }
}
void AddHistory(char *args,int isWait){
    cmdCounter++;
    if (cmdCounter <=9){
        for(int i=0;i<(MAX_LEN/2 + 1);i++){
            if(args[i] == NULL) break;
            history[cmdCounter][i] = args[i];
        }
        historyWait[cmdCounter] = isWait;
    }
}

//cmdCounter一直記
//history,historyWait在超過10個東西以後要把東西往前移
void ShowHistory(void){
    if (cmdCounter > 9){
        int x = 0;
        for (int i = (cmdCounter-9);i <= cmdCounter; i++){
            printf("[%d]",i);
            int j = 0;
            while(history[x][j] != NULL){
                printf("%s ",history[x][j]);
                j++;
            }
            if (historyWait[x]){
                printf("&");
            }
            printf("\n");
            x++;
        }
    }
    else{
        for (int i = 0;i <= cmdCounter; i++){
            printf("[%d]",i);
            int j = 0;
            while(history[i][j] != NULL){
                printf("%s ",history[i][j]);
                j++;
            }
            if (historyWait[i]){
                printf("&");
            }
            printf("\n");
        }
    }
}

int main(void){
    HistoryInitialize();
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
        else if(strcmp(args[0],"history")==0){
            ShowHistory();
            continue;
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