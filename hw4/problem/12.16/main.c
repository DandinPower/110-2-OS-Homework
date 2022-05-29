#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_LENGTH 10
#define START 0
#define OVER 4999

int head;
int waitingList[LIST_LENGTH] = {2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681};

int abs(int x){
    if (x < 0) return -x;
    else return x;
}

int FindBiggerElement(){
    for (int i=0; i<LIST_LENGTH; i++){
        if (head < waitingList[i]) return i;
    }
    return -1;
}

int FindClosetIndex(int *subList, int current){
    int minIndex = 0;
    int minDistance = abs(current - subList[0]);
    int subListLength = (int)(sizeof(subList)/sizeof(subList[0]));
    for (int i = 0 ;i < subListLength; i++){
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

int main(int argc, char *argv[]){
    head = atoi(argv[1]);
    printf("FCFS: %d",FCFS());
}