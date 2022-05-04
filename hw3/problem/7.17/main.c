#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NORTH_NUMS 5
#define SOUTH_NUMS 5
sem_t north;
sem_t south;

pthread_mutex_t northAccess = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t southAccess = PTHREAD_MUTEX_INITIALIZER;

int northCounter = 0;
int southCounter = 0;

int GetRandomTime(){
    return (rand()%10 + 1);
}

void *SouthBound(void *param){
    int* index = (int*)param;
    printf("[%d]'s farmers from south want to across the bridge...\n",*index);
    sem_wait(&south);
    pthread_mutex_lock(&southAccess);
    southCounter++;
    if (southCounter == 1) sem_wait(&north);
    pthread_mutex_unlock(&southAccess);
    printf("[%d]'s farmers from south acrossing the bridge...\n",*index);
    sleep(GetRandomTime());
    printf("[%d]'s farmers from south leaving the bridge...\n",*index);
    pthread_mutex_lock(&southAccess);
    southCounter++;
    if (southCounter == 0) sem_post(&north);
    printf("The bridge is empty!\n");
    pthread_mutex_unlock(&southAccess);
    sem_post(&south);
    int* index = (int*)param;
    pthread_exit(0);
}

void *NorthBound(void *param){
    int* index = (int*)param;
    printf("[%d]'s farmers from north want to across the bridge...\n",*index);
    sem_wait(&north);
    pthread_mutex_lock(&northAccess);
    northCounter++;
    if (northCounter == 1) sem_wait(&south);
    pthread_mutex_unlock(&northAccess);
    printf("[%d]'s farmers from north acrossing the bridge...\n",*index);
    sleep(GetRandomTime());
    printf("[%d]'s farmers from north leaving the bridge...\n",*index);
    pthread_mutex_lock(&northAccess);
    northCounter++;
    if (northCounter == 0) sem_post(&south);
    printf("The bridge is empty!\n");
    pthread_mutex_unlock(&northAccess);
    sem_post(&north);
    int* index = (int*)param;
    pthread_exit(0);
}

int main(int argc,char* argv[]){
    srand(time(NULL));
    int ids[5] = {0,1,2,3,4};
    sem_init(&north,0,1);
    sem_init(&south,0,1);
    pthread_t *northFarmers;
    pthread_t *southFarmers;
    northFarmers = (pthread_t *)malloc(NORTH_NUMS * sizeof(pthread_t));
    southFarmers = (pthread_t *)malloc(SOUTH_NUMS * sizeof(pthread_t));
    for (int i = 0; i < NORTH_NUMS; i++){
        pthread_create(&northFarmers[i], NULL, NorthBound, (void*)&ids[i]);
    }
    for (int i = 0; i < SOUTH_NUMS; i++){
        pthread_create(&southFarmers[i], NULL, SouthBound, (void*)&ids[i]);
    }
    for (int i = 0; i < NORTH_NUMS; i++){
        pthread_join(northFarmers[i],NULL);
    }
    for (int i = 0; i < SOUTH_NUMS; i++){
        pthread_join(southFarmers[i],NULL);
    }
    free(northFarmers);
    free(southFarmers);
    sem_destroy(&north);
    sem_destroy(&south);
    return 0;
}