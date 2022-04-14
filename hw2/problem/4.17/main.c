#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define GENERATE_NUMS 100000
#define RADIUS 100.0

int insideCounter;
void *runner(void *param);

double Distance(double x1, double y1, double x2, double y2){
    double X = (x1 - x2);
    double Y = (y1 - y2);
    return sqrt(pow(X,2) + pow(Y,2));
}

//parent
double CountPi(int insideCounter){
    double temp = (double)(4 * insideCounter);
    return temp / GENERATE_NUMS;
}

void *runner(void *param){
    insideCounter = 0;
    srand(time(NULL));
    double min = 0.0;
    double max = 2 * RADIUS;
    for(int i = 0; i<GENERATE_NUMS; i++){
        double x = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        double y = (max - min) * rand() / (RAND_MAX + 1.0) + min;
        if (Distance(x,y,RADIUS,RADIUS) <= RADIUS){
            insideCounter++;
        }
    }
    pthread_exit(0);
}

int main(int argc,char* argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, "CountPi");
    pthread_join(tid,NULL);
    double pi = CountPi(insideCounter);
    printf("Pi = %f\n",pi);
    return 0;
}