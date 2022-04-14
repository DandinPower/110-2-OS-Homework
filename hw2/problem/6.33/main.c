#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define THREAD_NUMS 3
#define GENERATE_NUMS 100000
#define RADIUS 100.0

int insideCounter;

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;

void *runner();

double Distance(double x1, double y1, double x2, double y2){
    double X = (x1 - x2);
    double Y = (y1 - y2);
    return sqrt(pow(X,2) + pow(Y,2));
}

//parent
double CountPi(int insideCounter){
    double temp = (double)(4 * insideCounter);
    return temp / (GENERATE_NUMS * THREAD_NUMS);
}

void *runner(){
    insideCounter = 0;
    srand(time(NULL));
    double min = 0.0;
    double max = 2 * RADIUS;
    for(int i = 0; i<GENERATE_NUMS; i++){
        double x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        double y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        if (Distance(x,y,RADIUS,RADIUS) <= RADIUS){
            pthread_mutex_lock( &mutex_1 );
            insideCounter++;
            pthread_mutex_unlock( &mutex_1 );
        }
    }
    pthread_exit(0);
}

int main(int argc,char* argv[]){

    pthread_t tid_1,tid_2,tid_3;
    pthread_create(&tid_1, NULL, runner, NULL);
    pthread_create(&tid_2, NULL, runner, NULL);
    pthread_create(&tid_3, NULL, runner, NULL);
    pthread_join(tid_1,NULL);
    pthread_join(tid_2,NULL);
    pthread_join(tid_3,NULL);
    double pi = CountPi(insideCounter);
    printf("Pi = %f\n",pi);
    return 0;
}