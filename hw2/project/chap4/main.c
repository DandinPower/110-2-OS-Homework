#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_NUMS 3
#define LIST_LENGTH 11
#define LIMIT 9999

int *listA;
int *listB;

sem_t mutex;

void* sort(int *list, int length){
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

int* merge(int *listA, int *listB, int aLength, int bLength){
    int aIndex = 0;
    int bIndex = 0;
    int *newList = (int *)malloc((aLength+bLength)*sizeof(int));
    for (int i=0; i<(aLength + bLength);i++){
        int smaller = LIMIT;
        if (aIndex < aLength){
            smaller = listA[aIndex];
            aIndex++;
        }
        if (bIndex < bLength){
            if (listB[bIndex] < smaller){
                if (smaller != LIMIT) aIndex--;
                smaller = listB[bIndex];
                bIndex++;
            }
        }
        newList[i] = smaller;
    }
    return newList;
}

void *runnerAB(void *param);

void *runnerC(void *param);

void *runnerAB(void *param){
    int *index = ((int *)param);
    if (index[0] == 0) sort(listA,index[1]);
    else sort(listB,index[1]);
    sleep(1);
    printf("finish\n");
    sem_post(&mutex);
    pthread_exit(0);
}

void *runnerC(void *param){
    int *length = ((int *)param);
    sem_wait(&mutex);
    printf("first List: ");
    ShowList(listA,length[0]);
    printf("second List: ");
    ShowList(listB,length[1]);
    int *newList = merge(listA,listB,length[0],length[1]);
    ShowList(newList,length[0]+length[1]);
    sem_post(&mutex);
    pthread_exit(0);
}


int main(int argc,char* argv[]){
    int listLength;
    printf("input list length: ");
    scanf("%d",&listLength);
    getchar();
    int *list = (int *)malloc(listLength * sizeof(int));
    for (int i=0;i<listLength;i++){
        scanf("%d",&list[i]);
        getchar();
    }
    int aLength = listLength / 2;
    int bLength = listLength - aLength;
    listA = (int *)malloc(aLength * sizeof(int));
    listB = (int *)malloc(bLength * sizeof(int));
    int aIndex[2] = {0,aLength};
    int bIndex[2] = {1,bLength};
    int length[2] = {aLength,bLength};
    for (int i=0;i<aLength;i++){
        listA[i] = list[i];
    }
    for (int i=0;i<bLength;i++){
        listB[i] = list[i+aLength];
    }
    sem_init(&mutex,0,-1);
    pthread_t tid_1,tid_2,tid_3;
    pthread_create(&tid_3, NULL, runnerC, (void *)&length);
    pthread_create(&tid_1, NULL, runnerAB, (void *)&aIndex);
    pthread_create(&tid_2, NULL, runnerAB, (void *)&bIndex);
    pthread_join(tid_1,NULL);
    pthread_join(tid_2,NULL);
    pthread_join(tid_3,NULL);
    sem_destroy(&mutex);
    return 0;
}