// 线程 信号量
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

int NUMBER = 2;
int g_val = 100;
// 定义信号量
pthread_mutex_t mutex;

void* ThreadWork(void* args){
    int *p = (int*)args;
    //自己分离自己，不用主线程回收它的资源
    pthread_detach(pthread_self());
    while (1)
    {
        pthread_mutex_lock(&mutex); // 加锁
        if (g_val > 0)
        {
            // pthread_self() 获取到自己的线程号，syscall(SYS_gettid) 获取到进程的pid
            printf("i am pid : %d ,i get g_val :%d\n",(int)syscall(SYS_gettid),g_val);
            // 把程序挂起微秒（千分之一毫秒）
            sleep(1);
        }else{
            // 再所有可能退出的地方，进行解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);   // 解锁
    }
    pthread_exit(NULL); // 终止线程
}

int main(int argc, char const *argv[])
{
    pthread_t tid[NUMBER];  // 假设有两个线程
    pthread_mutex_init(&mutex,NULL); // 初始化信号量
    for (int i = 0; i < NUMBER; i++)    // 一共创建了NUMBER个线程
    {
        // 一般来说不要用局部变量
        int ret = pthread_create(&tid[i],NULL,ThreadWork,(void*)&g_val);
        if(ret != 0){
            perror("pthread_create");   // 用于打印错误信息
            return -1;
        }
    }
    // pthread_join(tid,NULL); 进程等待
    // pthread_detach(tid); 进程分离
    pthread_mutex_destroy(&mutex);  // 销毁互斥锁
    while (1)
    {
        printf("我是主程序");
        sleep(2);
    }
    
    return 0;
}

