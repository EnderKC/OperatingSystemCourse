#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
        __pid_t fpid = fork();
        if (fpid ==0)
        {
            printf("我是子进程,我的父进程pid = %d\n",getppid());
            char *args[]={"ls","-a","/home/enderkc",NULL};
            char *envp[]={0,NULL};
            execve("/bin/ls",args,envp);
        }else{
            printf("==========================\n");
            printf("我是父进程的pid为 %d\n",getpid());
            printf("==========================\n");
        }
}