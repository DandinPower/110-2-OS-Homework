#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

/* Global definitions. */
#define PAGE_SIZE 256 // Page size, in bytes.
#define PAGE_ENTRIES 256 // Max page table entries.
#define PAGE_NUM_BITS 8 // Page number size, in bits.
#define FRAME_SIZE 256 // Frame size, in bytes.
#define FRAME_ENTRIES 256 // Number of frames in physical memory.
#define MEM_SIZE (FRAME_SIZE * FRAME_ENTRIES) // Mem size, in bytes.
#define TLB_ENTRIES 16 // Max TLB entries.

int mem_index = 0; // Points to beginning of first empty frame.
char* store_file; // Store file name.
char* store_data; // Store file data.
int store_fd; // Store file descriptor.
FILE* in_ptr; // Address file pointer.
FILE* out_ptr; // Output file pointer.
char memory[MEM_SIZE]; // Physical memory. Each char is 1 byte.
int main(int argc, char*argv[]){
    store_fd = open(store_file, O_RDONLY);
    store_data = mmap(0, MEM_SIZE, PROT_READ, MAP_SHARED, store_fd, 0);
    int page_address = 256;
    memcpy(memory + mem_index, store_data + page_address, PAGE_SIZE);
    printf("%d", mem_index);
	return 0;
}