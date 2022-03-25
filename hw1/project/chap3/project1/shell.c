#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_LEN 80
char history[10][MAX_LEN/2 + 1][MAX_LEN];
char backup[MAX_LEN/2 + 1][MAX_LEN];
int historyWait[10];
int backupWait;
int cmdCounter = 0;
void HistoryInitialize(void){
    for (int i=0;i<10;i++){
        for (int j=0;j<(MAX_LEN/2 + 1);j++){
            sprintf(history[i][j],"%s","NULL");
        }
        historyWait[i] = 0;
    }
}

void ShowHistory(void){
    int startIndex,stopIndex,printSymbol;
    printSymbol = 0;
    if(cmdCounter<=9) {
        startIndex = 0;
        stopIndex = cmdCounter;
    }
    else {
        startIndex = cmdCounter%10;
        stopIndex = startIndex + 10;
    }
    for (int i=startIndex;i<stopIndex;i++){
    	int j = 0;
    	printf("[%d]",printSymbol);
    	while(strcmp(history[i%10][j],"NULL")){
            printf("%s ",history[i%10][j]);
	    j++;
    	}
    	if (historyWait[i%10]==0) printf("&");
    	printf("\n");
    	printSymbol ++;
    }
}

void DeleteLastHistory(void){
    cmdCounter = cmdCounter -1;
    for (int j=0;j<(MAX_LEN/2 + 1);j++){
        if(cmdCounter > 9) sprintf(history[cmdCounter%10][j],"%s",backup[j]);
        else sprintf(history[cmdCounter%10][j],"%s","NULL");
    }
    if(cmdCounter > 9)historyWait[cmdCounter%10] = backupWait;
    else historyWait[cmdCounter%10] = 0;
}


void AddHistory(char *args[MAX_LEN/2 +1],int isWait){
    int z =0;
    backupWait = historyWait[cmdCounter%10];
    for (int j=0;j<(MAX_LEN/2 + 1);j++){
        sprintf(backup[j],"%s",history[cmdCounter%10][j]);
        sprintf(history[cmdCounter%10][j],"%s","NULL");
    }
    while(args[z]!=NULL){
        strcpy(history[cmdCounter%10][z],args[z]);
	z++;
    }
    historyWait[cmdCounter%10] = isWait;
    cmdCounter = cmdCounter + 1;
}

int main(void){
    HistoryInitialize();
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
        if (i ==0) continue;
        if (strcmp(args[0],"exit")==0){
            break;
        }
        else if(strcmp(args[0],"history")==0){
            ShowHistory();
            continue;
        }
        int isWait = 1;
        int isRecord = 1;
        if(args[0][0] == '!' && strlen(args[0])==2){
            if (args[0][1] == '!'){
                int index = (cmdCounter-1)%10;
                if (index < 0){
                    printf("THERE IS NO COMMAND CAN EXECUTE!\n");
                    continue;
                }
                isWait = historyWait[index];
                int j =0;
                while(strcmp(history[index][j],"NULL")){
                    args[j] = history[index][j];
                    j++;
                }
                args[j] = NULL;
                isRecord = 0;
            }
            else if ( args[0][1] >= 48 && args[0][1] <= 57){
                int index = args[0][1] - 48;
                if (cmdCounter >9) index = (index + (cmdCounter%10))%10;
                if (index > (cmdCounter -1)){
                    printf("THERE IS NO COMMAND CAN EXECUTE!\n");
                    continue;
                }
                isWait = historyWait[index];
                int j =0;
                while(strcmp(history[index][j],"NULL")){
                    args[j] = history[index][j];
                    j++;
                }
                args[j] = NULL;
                isRecord = 0;
            }
            else{
                args[i] = NULL;
            }
        } 
        else{
            if (strlen(args[i-1])==1 && args[i-1][0] == '&'){
                isWait = 0;
                args[i-1] = NULL;
            }
            else{
                args[i] = NULL;
            }
        }
        
        const int SIZE = 4096;
        const char *name = "OS";
        int fd;
        int *isBad;
        fd = shm_open(name,O_CREAT | O_RDWR,0666);
        ftruncate(fd, SIZE);
        isBad = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        *isBad = 0;
        
        if(isRecord)AddHistory(args,isWait);
        pid_t pid;
        pid = fork();
        if(pid < 0) {
            printf("FORK FAILED\n");
            return 1;
        }
        else if (pid == 0) {
            if(execvp(args[0], args)){
                
                printf("WRONG COMMAND\n");
                *isBad = 1;
                return 1;
            }
        }
        else {
            if(isWait){
                while(wait(NULL) != pid);
                if(*isBad && isRecord)DeleteLastHistory();
            }
        }
    }
    return 0;
}