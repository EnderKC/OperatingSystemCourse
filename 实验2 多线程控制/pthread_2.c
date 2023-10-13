#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print1(void* arg){
    printf("1.......");
    int i,t;
    t = (int)arg;
    for ( i = 0; i < t; i++)
    {
        printf("1......%d\n",i);
        sleep(1);
    }
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}


void* print2(void* arg){
    printf("2.......");
    int i,t;
    t = (int)arg;
    for ( i = 0; i < t; i++)
    {
        printf("2......%d\n",i);
        sleep(1);
    } 
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}


void* print3(void* arg){
    printf("3.......");
    int i,t;
    t = (int)arg;
    for ( i = 0; i < t; i++)
    {
        printf("3......%d\n",i);
        sleep(1);
    }
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}

int main(int argc, char const *argv[])
{
    printf("hello....\n");
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
    pthread_t t,t1,t2,t3;
    int i1 = 10,i2 = 20,i3 = 30;
    pthread_create(&t1,NULL,print1,(void*)i1);
    pthread_create(&t1,NULL,print2,(void*)i2);
    pthread_create(&t1,NULL,print3,(void*)i3);
    // sleep(2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("main........over......");
    return 0;
}
