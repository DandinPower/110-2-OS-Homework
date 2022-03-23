#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

char *string_concat(char *str1, char *str2) {   
   int length=strlen(str1)+strlen(str2)+1;  
   char *result = (char*)malloc(sizeof(char) * length);  
   strcpy(result, str1);  
   strcat(result, str2);  
   return result;  
} 

char *ThreeNPlusOne_Recursive(int n,char *output){
    char str[10];
    if (n== 1) {
        sprintf(str,"%d.\n",n);
        output = string_concat(output,str);    
    }
    else {
        sprintf(str,"%d,",n);
        output = string_concat(output,str);    
    }
    if (n== 1) return output;
    else if(n % 2 == 1) return ThreeNPlusOne_Recursive(3*n + 1,output);
    else return ThreeNPlusOne_Recursive(n/2,output);
}

int main(int argc, char *argv[]){
    char *n = argv[1];
    if (atoi(n) <= 0) {
        printf("error n\n");
        return 1;
    }
    char *output = "";
    const int SIZE = 4096;
    const char *name = "OS";
    int fd;
    char *ptr;
    fd = shm_open(name,O_CREAT | O_RDWR,0666);
    ftruncate(fd, SIZE);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) {
        char *answer = ThreeNPlusOne_Recursive(atoi(n),output);
        sprintf(ptr,"%s",answer);
    }
    else {
        wait(NULL);
        printf("%s",(char *)ptr);
        shm_unlink(name);
        printf("Child Complete\n");
    }
    return 0;
}