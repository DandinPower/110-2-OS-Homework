#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CUSTOMERS_NUMS 5
#define RESOURCES_NUMS 4
#define DISABLE_VALUE 9999

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

int CheckSafe(int availableList[RESOURCES_NUMS],int allocationList[CUSTOMERS_NUMS][RESOURCES_NUMS],int needList[CUSTOMERS_NUMS][RESOURCES_NUMS]){
    int pass[CUSTOMERS_NUMS] = {0, 0, 0, 0, 0};
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        int index = WhichIsAvailable(availableList,needList,pass);
        printf("%d ",index);
        if (index == -1) return -1;
        pass[index] = DISABLE_VALUE;
        for (int j=0; j<RESOURCES_NUMS; j++){
            availableList[j] += allocationList[index][j];
        }
    }
    return 0;
}

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
    }
    return state;
}

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

void InitializeAvailable(char *argv[]){
    for (int i=0; i<RESOURCES_NUMS; i++){
        available[i] = atoi(argv[i+1]);
    }
}

void ShowAvailable(){
    printf("Available:\n");
    for(int j=0; j<RESOURCES_NUMS; j++){
        printf("%d ", available[j]);
    }
    printf("\n\n");
}

void ShowMax(){
    printf("Maximum:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", maximum[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ShowAllocation(){
    printf("Allocation:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ShowNeed(){
    printf("Need:\n");
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ShowData(){
    ShowAvailable();
    ShowMax();
    ShowAllocation();
    ShowNeed();
    
}

int main(int argc,char* argv[]){
    InitializeAvailable(argv);
    //InitializeMax
    for (int i=0; i<CUSTOMERS_NUMS; i++){
        for(int j=0; j<RESOURCES_NUMS; j++){
            scanf("%d", &maximum[i][j]);
            getchar();
            need[i][j] = maximum[i][j];
        }
    }
    while(1){
        char input[80];
        scanf("%s",&input);
        getchar();
        if(strcmp(input,"*")==0){
            ShowData();
            break;
        }
        int customerIndex;
        scanf("%d",&customerIndex);
        getchar();
        int resource[RESOURCES_NUMS];
        for (int i=0; i<RESOURCES_NUMS; i++){
            scanf("%d", &resource[i]);
            getchar();
        }
        if(strcmp(input,"RQ")==0){
            if(RequestResources(customerIndex,resource)==-1){
                printf("Request Reject!\n");
            }
            else{
                printf("Request accept!\n");
            }
        }
        else if(strcmp(input,"RL")==0){
            ReleaseResources(customerIndex,resource);
        }
        else{
            printf("Invalid input\n");
            break;
        }
        
    }
    return 0;
}