#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_LENGTH 11

int* sort(int *list, int length){
    for (int i=length;i>=0;i--){
        for (int j = 0; j < i-1; j++){
            if (list[j] > list[j+1]){
                int temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

void ShowList(int *list, int length){
    for (int i=0;i<length;i++){
        printf("%d ",list[i]);
    }
    printf("\n");
}


int main(int argc,char *argv[]){
    int *listA;
    int *listB;
    int list[LIST_LENGTH] = {5, 1, 19, 6, 87, 10, 3, 55, 21, 30, 100};
    int aLength = LIST_LENGTH / 2;
    int bLength = LIST_LENGTH - aLength;
    listA = (int *)malloc(aLength * sizeof(int));
    listB = (int *)malloc(bLength * sizeof(int));
    for (int i=0;i<aLength;i++){
        listA[i] = list[i];
    }
    for (int i=0;i<bLength;i++){
        listB[i] = list[i+aLength];
    };
    sort(listA,aLength);
    sort(listB,bLength);
    ShowList(listA,aLength);
    ShowList(listB,bLength);
    return 0;
}