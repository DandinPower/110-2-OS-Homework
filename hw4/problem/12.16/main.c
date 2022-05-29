#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_LENGTH 10
#define START 0
#define OVER 4999
#define NEGATIVE_LIMIT -9999

int head;
int waitingList[LIST_LENGTH] = {2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};

int abs(int x){
    if (x < 0) return -x;
    else return x;
}

int * AppendArray(int *list, int length, int value){
    int* new = (int *)malloc(sizeof(int) * (length+1));
    for (int i=0; i< length; i++)new[i] = list[i];
    new[length] = value;
    return new;
}

void SortArray(int *list){
    int i,j,temp;
    for(i = 0; i < LIST_LENGTH; i++){
        for(j = 0; j< LIST_LENGTH; j++){
            if(list[i] < list[j]){ 
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
        
    }
}   

int * ReverseArray(int *list, int length){
    int* reverse = (int *)malloc(sizeof(int) * length);
    int i = 0;
    for (int j = length-1; j >= 0; j--) {
        reverse[i] = list[j]; 
        i++;
    }
    return reverse;
}

int* GetSmallerSlice(int *list, int index){
    int length = index;
    int *small = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i<length; i++)small[i] = list[i];
    return small;
}

//取得較大的array切片
int* GetBiggerSlice(int *list, int index){
    int length = LIST_LENGTH - index;
    int *big = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i<length; i++)big[i] = list[i+index];
    return big;
}

int FindBiggerElement(int *list){
    for (int i=0; i<LIST_LENGTH; i++){
        if (head < list[i]) return i;
    }
    return -1;
}

int FindClosetIndex(int *subList, int current){
    int minIndex = 0;
    int minDistance = abs(current - subList[0]);
    for (int i = 0 ;i < LIST_LENGTH; i++){
        int tempDistance = abs(current - subList[i]);
        if (tempDistance < minDistance){
            minIndex = i;
            minDistance = tempDistance;
        }
    }
    return minIndex;
}

int *CopyList(int list[LIST_LENGTH]){
    int *b;
    b = (int*) malloc( LIST_LENGTH * sizeof(int));
    for (int i=0; i<LIST_LENGTH; i++) b[i] = list[i];
    return b;
}

int FCFS(){
    int total = 0;
    int *list = CopyList(waitingList);
    printf("%d ",head);
    int current = head;
    for (int i = 0; i < LIST_LENGTH; i++){
        printf("%d ",list[i]);
        total = total + abs(list[i] - current);
        current = list[i];
    }
    printf("\n");
    return total;
}

int SSTF(){
    int *list = CopyList(waitingList);
    int total = 0;
    printf("%d ",head);
    int current = head;
    for (int i = 0; i < LIST_LENGTH; i++){
        int index = FindClosetIndex(list,current);
        int data = list[index];
        printf("%d ",data);
        total = total + abs(data - current);
        current = data;
        list[index] = NEGATIVE_LIMIT;
    }
    printf("\n");
    return total;
}

int SCAN(){
    int total = 0;
    int *sortList = CopyList(waitingList);
    SortArray(sortList);
    int biggerIndex = FindBiggerElement(sortList);
    int smallLength = biggerIndex;
    int bigLength = LIST_LENGTH - biggerIndex;
    int* smallList = GetSmallerSlice(sortList,smallLength);
    smallList = ReverseArray(smallList,smallLength);
    int* bigList = GetBiggerSlice(sortList,biggerIndex);
    //會需要appendArray是因為目前版本是一定先會往上
    bigList = AppendArray(bigList, bigLength,OVER);
    printf("%d ",head);
    int current = head;
    //bigLength + 1是因為目前版本是一定先會往上
    for (int i=0; i < bigLength + 1; i++){
        printf("%d ",bigList[i]);
        total = total + abs(bigList[i] - current);
        current = bigList[i];
    }
    for (int i=0; i < smallLength; i++){
        printf("%d ",smallList[i]);
        total = total + abs(smallList[i] - current);
        current = smallList[i];
    }
    printf("\n");
    return total;
}

int main(int argc, char *argv[]){
    head = atoi(argv[1]);
    printf("FCFS: %d\n",FCFS());
    printf("SSTF: %d\n",SSTF());
    printf("SCAN: %d\n",SCAN());
}