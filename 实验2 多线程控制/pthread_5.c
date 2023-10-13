/*
    给予互斥量数组的访问
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

// 共享资源
int a[10] = {0,1,2,3,4,5,6,7,8,9};
// 信号量
pthread_mutex_t mutex;

// 线程函数操作

/*
    根据参数下标，读取数组中对应的数据
*/
void* myRead(void* arg){
    //自己分离自己，不用主线程回收它的资源
    pthread_detach(pthread_self());
    int n = *(int*)arg;
    if (n <=10 && n >= 0){
        int t = a[n];
        printf("共享资源中第%d个值为%d\n",n,t);
    }else{
        perror("读取的数据超出数组范围\n");
    }
    
}
/*
    读取数组中的所有数据
*/
void* readAll(void* arg){
    //自己分离自己，不用主线程回收它的资源
    pthread_detach(pthread_self());
    for (int i = 0; i < 10; i++)
    {
        printf("%d  ",a[i]);
    }
    printf("  数组输出完毕\n");
}
/*
    删除数组中某一个元素
*/
void* delete(void* arg){
    //自己分离自己，不用主线程回收它的资源
    pthread_detach(pthread_self());
    int n = *(int*)arg;
    if(n > 9){
        perror("删除数据超出范围\n");
        return (void*)-1;
    }
    pthread_mutex_lock(&mutex); // 加锁
    a[n] = 0;
    // 数组后面的元素向前移动一位
    for (int i = n; i < 9; i++)
    {
        int tmp = a[i];
        a[i] = a[i+1];
        a[i+1] = tmp;
    }
    pthread_mutex_unlock(&mutex); // 解锁
    // 展示删除完之后的样子
    pthread_t t;
    printf("删除完成:");
    readAll(NULL);
}
/*
    项数组中插入
    接收两个参数：
        第一个参数：插入的位置
        第二个参数：插入的参数
*/
void* insert(void* args){
    //自己分离自己，不用主线程回收它的资源
    pthread_detach(pthread_self());
    int *arr = (int*)args;
    if(arr[0] > 9){
        perror("插入数据超出范围\n");
        return (void*)-1;
    }
    pthread_mutex_lock(&mutex); // 加锁
    for (int i = 9; i > arr[0]; i--)
    {
        a[i] = a[i-1];
    }
    a[arr[0]] = arr[1];
    pthread_mutex_unlock(&mutex); // 解锁
    // 展示删除完之后的样子
    pthread_t t;
    printf("插入完成:");
    readAll(NULL);
}

/*
    pthread_join用于等待一个线程的结束，
    也就是主线程中要是加了这段代码，
    就会在加代码的位置卡主，直到这个线程执行完毕才往下走。
*/

int main(int argc, char const *argv[])
{
    printf("========BEGIN==========\n");
    // 线程号
    pthread_t tid[4];
    // 初始化信号量
    pthread_mutex_init(&mutex,NULL);
    // 创建线程(读取)
    int readData = 5;
    int deleteData = 3;
    int insertData[] = {4,7};
    int ret1 = pthread_create(&tid[0],NULL,myRead,(void*)&readData);
    int ret2 = pthread_create(&tid[1],NULL,delete,(void*)&deleteData);
    int ret3 = pthread_create(&tid[2],NULL,insert,(void*)&insertData);
    int ret4 = pthread_create(&tid[3],NULL,readAll,NULL);
    pthread_mutex_destroy(&mutex);  // 销毁互斥锁
    if(ret1 && ret2 && ret3 && ret4){
        perror("创建进程失败\n");   // 用于打印错误信息
        return -1;
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(tid[i],NULL);
    }
    printf("\n========E=N=D==========\n");
    return 0;
}
