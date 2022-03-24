#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 2

int main(int argc, char *argv[]){
    int fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];
    pipe (fd);
    int sourceFile = open(argv[1],0);
    int destinationFile = open(argv[2],0666);
    if ( sourceFile == -1 || destinationFile == -1 ) {
        printf("Open Failed\n");
        return 1;
    }
    pid = fork();
    if (pid < 0) { 
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0) {
        close(fd[1]);
        while( read( fd[0], buffer, sizeof( buffer ) ) > 0 )  {
            write( destinationFile, buffer, strlen( buffer ) - 1 );
        }
        close(fd[0]);
        close(destinationFile);
    }
    else {
        close(fd[0]);
        while( read( sourceFile, buffer, sizeof( buffer ) ) > 0 )  {
            write( fd[1], buffer, sizeof( buffer ) );
        }
        close(fd[1]);
        close(sourceFile);
        wait(NULL);
    }
    return 0;
}