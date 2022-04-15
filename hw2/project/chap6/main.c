#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define STUDENT_NUMS 5

//控制椅子
sem_t chairs[3];

//控制學生去叫醒TA
sem_t taSleep;

//控制學生等待ta是否完成
sem_t studentWaitTa;

//控制學生或ta能不能變更椅子空位數
pthread_mutex_t chairAccess = PTHREAD_MUTEX_INITIALIZER;

//目前椅子數
int chairCounter = 0;

//剩餘學生數
int studentsCounter = STUDENT_NUMS;
//pthread_mutex_lock( &mutex_1 );
//pthread_mutex_unlock( &mutex_1 );
//sem_wait(&mutex);
//sem_post(&mutex);

int GetRandomTime(){
    return (rand()%10 + 1);
}

void *TaWorking(){
    while(1){
        //sleeping
        printf("Ta is sleeping\n");
        sem_wait(&taSleep);
        printf("Ta is wake up\n");
        //直到有人叫醒Ta進入辦公迴圈
        while(1){
            //檢查有沒有在椅子上
            pthread_mutex_lock( &chairAccess );
            if (chairCounter == 0){
                //沒有人在椅子上就去睡覺
                pthread_mutex_unlock( &chairAccess );
                break;
            }
            else if(studentsCounter == 0){
                printf("All Done!\n");
                break; 
                pthread_exit(0);
            }
            else{
                //開始幫助學生
                //從椅子上抓人進來
                int chairIndex = chairCounter - 1;
                chairCounter--;
                pthread_mutex_unlock( &chairAccess );
                sem_post(&chairs[chairIndex]);
                printf("Ta Starting help students who sits in [%d]chair...\n",chairIndex);
                //等待一段教學時間後結束
                sleep(GetRandomTime());
                studentsCounter--;
                printf("Ta Ask students leave\n");
                sem_post(&studentWaitTa);
                sleep(1);
            }
        }
    }
}

void *StudentWorking(void *param){
    int* index = (int*)param;
    while(1){
        printf("Student %d needs help\n",*index);
        sleep(GetRandomTime());
        //檢查座位有沒有人
        pthread_mutex_lock( &chairAccess );
        if (chairCounter < 3){

            //如果位子沒有人叫Ta起床
            if (chairCounter == 0) sem_post(&taSleep);
            int chairIndex = chairCounter;
            chairCounter++;

            //並且在座位上等待Ta->
            printf("Student %d Sits in [%d]chair waiting Ta\n",*index,chairIndex);
            pthread_mutex_unlock( &chairAccess );
            sem_wait(&chairs[chairIndex]);
            //等待ta教學完成->
            printf("Student %d into office getting help with Ta\n",*index);
            sem_wait(&studentWaitTa);

            //結束程序
            printf("Student %d Leaving office...\n",*index);  
            break;
            pthread_exit(0);
        }
        else{
            //如果有人就重跑迴圈
            printf("Student %d come again later\n",*index);
            pthread_mutex_unlock( &chairAccess );
        }          
    }
}

int main(int argc,char* argv[]){
    srand(time(NULL));
    int ids[5] = {0,1,2,3,4};
    for (int i=0;i<3;i++){
        sem_init(&chairs[i],0,0);
    }
    sem_init(&taSleep, 0, 0);
    sem_init(&studentWaitTa, 0, 0);
    pthread_t ta;
    pthread_t *students;
    students = (pthread_t *)malloc(STUDENT_NUMS * sizeof(pthread_t));
    pthread_create(&ta, NULL, TaWorking, NULL);
    for (int i = 0; i < STUDENT_NUMS; i++){
        pthread_create(&students[i], NULL, StudentWorking, (void*)&ids[i]);
    }
    pthread_join(ta,NULL);
    for (int i = 0; i < STUDENT_NUMS; i++){
        pthread_join(students[i],NULL);
    }
    free(students);
    sem_destroy(&taSleep);
    sem_destroy(&studentWaitTa);
    for (int i=0;i<3;i++){
        sem_destroy(&chairs[i]);
    }
    return 0;
}