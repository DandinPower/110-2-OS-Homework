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

char* storeData; 
int storeFd;

int memoryIndex = 0;
char memory[MEMORY_SIZE];

FILE *addressFile;
FILE *outputFile;

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

//初始化storeData
void InitializeStore(char *storeFile){
	storeFd = open(storeFile, O_RDONLY);
	storeData = mmap(0, MEMORY_SIZE, PROT_READ, MAP_SHARED, storeFd, 0);
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
void GetPhysicalAndFrames(int logicalAddress){
	pageCounter++;
	//先將logicalAddress轉換成pagenumber,offset
	int pageNumber = GetPageNumber(logicalAddress);
	int offset = GetOffset(logicalAddress);
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
			int pageAddress = (pageNumber*PAGE_SIZE);
			memcpy(memory + memoryIndex,storeData + pageAddress, PAGE_SIZE);
			frames = memoryIndex;
			pageTable[pageNumber] = frames;
			memoryIndex += FRAME_SIZE; 
			if (memoryIndex >= MEMORY_SIZE){
				memoryIndex = -1;
				printf("Memory is full!\n");
			}
		}
		UpdateTlb(pageNumber, frames);
	}
	int physicalAddress = frames + offset;
	int values = memory[physicalAddress];
	char *str;
	sprintf(str,"virtual address: %d, physical address: %d, values: %d\n",logicalAddress,physicalAddress,values);
	fwrite(str,1,strlen(str),outputFile);
}

//檢查是否在PageTable
int main(int argc, char*argv[]){
	InitializeTlb();
	InitializeTable();
	InitializeStore(argv[1]);
	addressFile = fopen(argv[2],"r");
	outputFile = fopen(argv[3],"w+");
	char *contents = NULL;
	size_t len = 0;
	while(getline(&contents,&len,addressFile)!= -1){
		int address = atoi(contents);
		GetPhysicalAndFrames(address);
	}
	fclose(addressFile);
	fclose(outputFile);
	free(contents);
	printf("Tlb Hit: %d\n",tlbHits);
	printf("Page Faults: %d\n",pageFaults);
	return 0;
}