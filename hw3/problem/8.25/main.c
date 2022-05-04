#include <stdio.h>
#include <stdlib.h>

//page size 為4KB
#define PAGE_SIZE 4096

//由於為32bits
unsigned int virtualAddress,pageNumber,offset;

int main(int argc, char *argv[]){
    virtualAddress = atoi(argv[1]);
    pageNumber = virtualAddress / PAGE_SIZE;
    offset = virtualAddress % PAGE_SIZE;
    printf("The address %u contains:\n", virtualAddress);
    printf("page number = %u", pageNumber);
    printf("offset = %u", offset);
    return 0;
}