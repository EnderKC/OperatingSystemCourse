// 自行设计一个有意思的fork()创建子进程的实例
#include <unistd.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("开始。。。\n");
    for (int i = 0; i < 3; i++)
    {
        __pid_t fpid = fork();
        if (fpid == 0)
        {
            printf("我是父进程%d的子进程%d\n",getppid(),getpid());
            break;
        }else{
            printf("我是父进程pid = %d,我创建了子进程fpid = %d\n",getpid(),fpid);
        }
        
    }
    printf("结束。。。\n");
    return 0;
}
