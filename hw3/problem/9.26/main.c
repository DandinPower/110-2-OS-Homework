#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define PAGE_NUMS 20

int pageSequence[PAGE_NUMS] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};
int frameNums = 3;

//取得一個隨機0~9的數
int GetRandomNumber(){
    return (rand()%10);
}

//打亂pageSequence
void GetRandomSequence(){
    for (int i=0; i<PAGE_NUMS; i++){
        pageSequence[i] = GetRandomNumber();
    }
}

//展示目前的list
void ShowSequence(){
    for (int i=0; i<PAGE_NUMS; i++) printf("%d ",pageSequence[i]);
    printf("\n");
}

//展示目前的state
void ShowState(int *state){
    for (int i=0; i<frameNums; i++) printf("%d ",state[i]);
    printf("\n");
}

//檢查該page有無在frames裡
int CheckIsInFrames(int *state, int pageIndex){
    int answer = -1;
    for (int i=0; i<frameNums; i++) if(state[i]==pageIndex) answer = i;
    return answer;
}

//將pageIndex加進state(FIFO,LRU)
void AddFIFOState(int *state, int pageIndex){
    if(state[0]!=-1) for (int i=frameNums-1; i>0; i--) state[i] = state[i-1];
    state[0] = pageIndex;
}

//實現fifo algorithm
void FIFO(){
    int faults = 0;
    int *state;
    state = (int *)malloc(sizeof(int) * frameNums);
    for (int i=0; i<frameNums; i++) state[i] = -1;
    for (int i=0; i<PAGE_NUMS; i++){
        if(CheckIsInFrames(state, pageSequence[i])==-1){
            faults++;
            AddFIFOState(state, pageSequence[i]);
        }
    }
    printf("FIFO page faults: %d\n",faults);
}

//實現LRU當重複遇到時的處理
void UpdateLRUState(int *state, int pageIndex, int index){
    for (int i=index; i>0; i--) state[i] = state[i-1];
    state[0] = pageIndex;
}

//實現LRU algorithm
void LRU(){
    int faults = 0;
    int *state;
    state = (int *)malloc(sizeof(int) * frameNums);
    for (int i=0; i<frameNums; i++) state[i] = -1;
    for (int i=0; i<PAGE_NUMS; i++){
        int index = CheckIsInFrames(state, pageSequence[i]);
        if(index == -1){
            faults++;
            AddFIFOState(state, pageSequence[i]);
        }
        else{
            UpdateLRUState(state, pageSequence[i], index);
        }
    }
    printf("LRU page faults: %d\n",faults);
}

int main(int argc,char* argv[]){
    srand(time(NULL));
    frameNums = atoi(argv[1]);
    FIFO();
    LRU();
    return 0;
}