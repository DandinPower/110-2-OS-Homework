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

#define TLB_NUMS 16
#define PAGE_ENTRIES 256
#define PAGE_SIZE 256
#define FRAME_SIZE 256
#define FRAME_NUMS 256
#define MEMORY_SIZE 65536

int tlbHits = 0;
int pageFaults = 0;
int pageCounter = 0;
int tlb[TLB_NUMS][2];
int tlbCounter = 0;
int pageTable[PAGE_ENTRIES];
int memory[MEMORY_SIZE];

//DISK DATA
int diskTable[PAGE_ENTRIES];

//初始化STORE DATA
void InitializeDisk(){
	for (int i=0; i<PAGE_ENTRIES; i++){
		diskTable[i] = i;
	}
}

//回傳store data
int ReadDataFromDisk(int pageNumber){
	return diskTable[pageNumber];
}

//初始化TLB cache
void InitializeTlb(){
	for (int i=0; i<TLB_NUMS; i++){
		tlb[i][0] = -1;
		tlb[i][1] = -1;
	}
}

//初始化PageTable
void InitializeTable(){
	for (int i=0; i<PAGE_ENTRIES; i++){
		pageTable[i] = -1;
	}
}

//檢查是否在TLB -> 有的話回傳index,沒有的話回傳-1
int FindPageInTlb(int pageIndex){
	for (int i=0; i<TLB_NUMS; i++) if (tlb[i][0] == pageIndex) return i;
	return -1;
}

//根據logicalAddress取得pagenumber
int GetPageNumber(int logicalAddress){
	return logicalAddress >> 8;
}
//根據logicalAddress取得offset
int GetOffset(int logicalAddress){
	int mask = 255;
	return logicalAddress & mask;
}

//更新tlb
void UpdateTlb(int pageNumber, int frames){
	int index = tlbCounter % (TLB_NUMS - 1);
	tlb[index][0] = pageNumber;
	tlb[index][1] = frames;	
	tlbCounter++;
}

//根據logicaladdress轉換成physicaladdress
int GetPhysicalAddress(int logicalAddress){
	pageCounter++;
	//先將logicalAddress轉換成pagenumber,offset
	int pageNumber = GetPageNumber(logicalAddress);
	int offset = GetOffset(logicalAddress);
	printf("%d\n",pageNumber);
	printf("%d\n",offset);
	int frames;
	//先檢查是否在TLB
	frames = FindPageInTlb(pageNumber);
	if (frames != -1){
		tlbHits++;
	}
	else {
		frames = pageTable[pageNumber];
		if (frames == -1){
			pageFaults++;
			frames = ReadDataFromDisk(pageNumber);
			pageTable[pageNumber] = frames; 
		}
		UpdateTlb(pageNumber, frames);
	}
	int physicalAddress = frames * PAGE_SIZE + offset;
	return physicalAddress;
}

//檢查是否在PageTable
int main(int argc, char*argv[]){
	InitializeTlb();
	InitializeTable();
	InitializeDisk();
	int logical = 8913;
	int physical = GetPhysicalAddress(logical);
	printf("virtual address: %d, physical address: %d\n",8913,physical);
	return 0;
}