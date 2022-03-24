#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd[2];
    pid_t pid;
    char readBuffer[100];
    char writeBuffer[100];
    int readCounter;
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
        read( fd[0], readBuffer, sizeof( readBuffer ) ); 
        write( destinationFile, readBuffer, strlen( readBuffer ) - 1 );
    }
    else {
        close(fd[0]);
        while( (readCounter = read( sourceFile, readBuffer, sizeof( readBuffer ) ) > 0 ) )  {
            write( fd[1], readBuffer, sizeof( readBuffer ) );
        }
        close(fd[1]);
    }
    return 0;
}