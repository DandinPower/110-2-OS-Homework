#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define CUSTOMERS_NUMS 5
#define RESOURCES_NUMS 4
#define DISABLE_VALUE 9999

void InitializeAvailable(char *argv[]);
void InitializeMaximum();
int WhichIsAvailable(int availableList[RESOURCES_NUMS], int needList[CUSTOMERS_NUMS][RESOURCES_NUMS], int pass[CUSTOMERS_NUMS]);
int CheckSafe(int availableList[RESOURCES_NUMS],int allocationList[CUSTOMERS_NUMS][RESOURCES_NUMS],int needList[CUSTOMERS_NUMS][RESOURCES_NUMS]);
void *CustomerRunner(void *param);
int RequestResources(int customerIndex, int requestList[RESOURCES_NUMS]);
void ReleaseResources(int customerIndex, int releaseList[RESOURCES_NUMS]);
void ShowData();

//用來保護不同customer不會產生race condition
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_lock(&mutex);
//pthread_mutex_unlock(&mutex);

int available[RESOURCES_NUMS] = {0, 0, 0, 0};
int maximum[CUSTOMERS_NUMS][RESOURCES_NUMS] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};
int allocation[CUSTOMERS_NUMS][RESOURCES_NUMS] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};
int need[CUSTOMERS_NUMS][RESOURCES_NUMS] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};

//根據argv初始化available
void InitializeAvailable(char *argv[]){
    for (int i=0; i<RESOURCES_NUMS; i++){
        available[i] = atoi(argv[i+1]);
    }
}

//根據available隨機初始化max
void InitializeMaximum(){
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for (int j=0; j<RESOURCES_NUMS; j++) {
            maximum[i][j] = rand()%(available[j]+1);
            need[i][j] = maximum[i][j];
        }
    }
}

//找出單個符合現在條件的Process來執行
int WhichIsAvailable(int availableList[RESOURCES_NUMS], int needList[CUSTOMERS_NUMS][RESOURCES_NUMS], int pass[CUSTOMERS_NUMS]){
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        int isAvailable = 1;
        if (pass[i] == DISABLE_VALUE) continue;
        for (int j=0; j<RESOURCES_NUMS; j++){
            if (needList[i][j] > availableList[j]) isAvailable = 0;
        }
        if (isAvailable) return i;
    }
    return -1;
}

//檢查現在的狀態是否是safestate
int CheckSafe(int availableList[RESOURCES_NUMS],int allocationList[CUSTOMERS_NUMS][RESOURCES_NUMS],int needList[CUSTOMERS_NUMS][RESOURCES_NUMS]){
    //複製一個available來檢查
    int copyAvailable[RESOURCES_NUMS];
    for (int i=0; i<RESOURCES_NUMS; i++)copyAvailable[i] = availableList[i];
    //宣告一個pass來記錄誰已經通過了
    int pass[CUSTOMERS_NUMS] = {0, 0, 0, 0, 0};
    //開始找出一個符合條件的順序
    printf("Sequence: ");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        int index = WhichIsAvailable(copyAvailable,needList,pass);
        printf("%d ",index);
        if (index == -1) return -1;
        pass[index] = DISABLE_VALUE;
        for (int j=0; j<RESOURCES_NUMS; j++){
            copyAvailable[j] += allocationList[index][j];
        }
    }
    return 0;
}

//customer request
int RequestResources(int customerIndex, int requestList[RESOURCES_NUMS]){
    int error = 0;
    for (int i=0; i<RESOURCES_NUMS; i++) {
        available[i] -= requestList[i];
        allocation[customerIndex][i] += requestList[i];
        need[customerIndex][i] -= requestList[i];
        if (need[customerIndex][i] < 0) error = 1;
    }
    int state = CheckSafe(available,allocation,need);
    //需要回復狀態
    if (error || state == -1){
        for (int i=0; i<RESOURCES_NUMS; i++) {
            available[i] += requestList[i];
            allocation[customerIndex][i] -= requestList[i];
            need[customerIndex][i] += requestList[i];
        }
        if (error) printf("Invalid Request because request more than need\n");
        if (state == -1) printf("Request is Reject because can't find sequence,so it's in unsafe state\n");
    }
    return state;
}

//customer release
void ReleaseResources(int customerIndex, int releaseList[RESOURCES_NUMS]){
    int error = 0;
    for (int i=0; i<RESOURCES_NUMS; i++) {
        available[i] += releaseList[i];
        allocation[customerIndex][i] -= releaseList[i];
        need[customerIndex][i] += releaseList[i];
        if (allocation[customerIndex][i] < 0) error = 1;
    }
    //需要回復狀態
    if (error){
        for (int i=0; i<RESOURCES_NUMS; i++) {
            available[i] -= releaseList[i];
            allocation[customerIndex][i] += releaseList[i];
            need[customerIndex][i] -= releaseList[i];
        }
        printf("Invalid Release because release more than allocation\n");
    }
}

//根據該customer的need隨機產生request
void RandomRequest(int index, int request[RESOURCES_NUMS]){
    for (int j=0; j<RESOURCES_NUMS; j++) {
        request[j] = rand()%(need[index][j]+1);
    }
}

//根據該customer的allocation隨機產生release
void RandomRelease()(int index, int release[RESOURCES_NUMS]){
    for (int j=0; j<RESOURCES_NUMS; j++) {
        release[j] = rand()%(allocation[index][j]+1);
    }
}

//customer thread
void *CustomerRunner(void *param){
    int* index = (int*)param;
    int requestRandomList[RESOURCES_NUMS];
    int releaseRandomList[RESOURCES_NUMS];
    RandomRequest(*index, requestRandomList);
    RandomRelease(*index, releaseRandomList);
    printf("[%d]customer is request: ");
    for (int j=0; j<RESOURCES_NUMS; j++) printf("%d ",requestRandomList[j]);
    printf("\n");
    printf("[%d]customer is release: ");
    for (int j=0; j<RESOURCES_NUMS; j++) printf("%d ",releaseRandomList[j]);
    printf("\n");
    pthread_exit(0);
}

//印出狀態
void ShowData(){
    printf("Available:\n");
    for(int j=0; j<RESOURCES_NUMS; j++){
        printf("%d ", available[j]);
    }
    printf("\n\n");
    printf("Maximum:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Allocation:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Need:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc,char *argv[]){
    srand(time(NULL));
    InitializeAvailable(argv);
    InitializeMaximum();
    ShowData();
    int ids[CUSTOMERS_NUMS] = {0,1,2,3,4};
    pthread_t *customers;
    customers = (pthread_t *)malloc(CUSTOMERS_NUMS * sizeof(pthread_t));
    for (int i = 0; i < CUSTOMERS_NUMS; i++){
        pthread_create(&customers[i], NULL, CustomerRunner, (void*)&ids[i]);
    }
    for (int i = 0; i < CUSTOMERS_NUMS; i++){
        pthread_join(customers[i],NULL);
    }
    free(customers);
    return 0;
}