#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print1(void* arg){
    printf("1.......");
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}


void* print2(void* arg){
    printf("2.......");
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}


void* print3(void* arg){
    printf("3.......");
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
}

int main(int argc, char const *argv[])
{
    printf("hello....\n");
    printf("PID = %d,TID = %lx\n",getpid(),pthread_self());
    pthread_t t,t1,t2,t3;
    pthread_create(&t1,NULL,print1,NULL);
    printf("t1=%lx\n",t1);
    pthread_create(&t1,NULL,print2,NULL);
    printf("t2=%lx\n",t2);
    pthread_create(&t1,NULL,print3,NULL);
    printf("t3=%lx\n",t3);
    sleep(2);
    return 0;
}
