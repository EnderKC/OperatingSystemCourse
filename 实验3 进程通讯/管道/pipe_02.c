/*
    生产者消费者
*/
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/types.h>
int main(int argc, char const *argv[])
{
    printf("===程序开始运行===\n");
    __pid_t pid[2]; 
    int fd[2];
    if (pipe(fd) < 0)
    {
        printf("创建管道失败\n");
        return -1;
    }
    char fd_0[2];
    sprintf(fd_0,"%d",fd[0]);
    char fd_1[2];
    sprintf(fd_1,"%d",fd[1]);
    // 创建生产者进程
    pid[0] = fork();
    if (pid[0] == 0)
    {
        printf("====生产者开始运行====\n");
        close(fd[0]);
        // 向管道中写入数据
        for (int i = 0; i < 10; i++)
        {
            int num = i;
            write(fd[1],&num,sizeof(int));
            printf("生产者刚刚向管道中写入数据：%d\n",num);
            sleep(2);
        }
        printf("====生产者结束运行====\n");
        return 0;
    }
    pid[1] = fork();
    if (pid[1] == 0)
    {
        printf("====消费者开始运行====\n");
        // 向管道中读取数据
        close(fd[1]);
        for (int i = 0; i < 10; i++)
        {
            int num;
            read(fd[0],&num,sizeof(int));
            printf("消费者刚刚向管道中读取数据：%d\n",num);
            sleep(2);
        }
        printf("====消费者结束运行====\n");
        return 0;
    }
    printf("===程序结束运行===\n");

    return 0;
}
