// 线程
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
//定义结构体 速度和距离
typedef struct run
{
    int speed;
    int distance;
}run;

void* turtle(void* args){
    run *runInfo;
    runInfo = (run*)args;
    for (int i = 0; i < runInfo->distance; i+=runInfo->speed)
    {
        printf("乌龟正在跑步，已经跑了%d,一共有%d\n",i,runInfo->distance);
        sleep(1);
    }
}

void* rabbit(void* args){
    run *runInfo;
    runInfo = (run*)args;
    for (int i = 0; i < runInfo->distance; i+=runInfo->speed)
    {
        printf("兔子正在跑步，已经跑了%d,一共有%d\n",i,runInfo->distance);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    run runTurtle = {5,30};
    run runRubbit = {10,50};
    pthread_t pthread[2];
    // 创建进程
    int pthread0 = pthread_create(&pthread[0],NULL,turtle,(void*)&runTurtle);
    int pthread1 = pthread_create(&pthread[1],NULL,rabbit,(void*)&runRubbit);
    // 检查进程是否创建成功
    if(!pthread0 && !pthread1){
        printf("线程号1:%ld,线程号2:%ld\n",pthread[0],pthread[1]);
    }else{
        printf("进程创建失败");
        return -1;
    }
    // 等待进程运行完成
    pthread_join(pthread[0],NULL);
    pthread_join(pthread[1],NULL);
    printf("总进程运行完成！\n");
    return 0;
}
