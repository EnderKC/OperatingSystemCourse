#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
/*
    C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，
    并返回一个指向错误消息字符串的指针。
    strerror 生成的错误字符串取决于开发平台和编译器。
*/
#include <errno.h>
#include <string.h>

/*
    C 库函数 int fprintf(FILE *stream, const char *format, ...) 发送格式化输出到流 stream 中。

    https://blog.csdn.net/tbssysfsx/article/details/104876329
        exit（0）：正常运行程序并退出程序；
        exit（1）：非正常运行导致退出程序；
        return（）：返回函数，若在主函数中，则会退出函数并返回一值。
        
    https://blog.csdn.net/qq_44308180/article/details/115440076
*/

int main(int argc, char const *argv[])
{
    printf("===程序开始===\n");
    pid_t pid;
    int fd[2];
    if(pipe(fd) < 0){
        fprintf(stderr,"pipe:%s\n",strerror(errno));
        return -1;
    }
    if((pid = fork()) < 0){
        printf("创建进程失败");
        return -1;
    }else if (pid > 0)
    {
        close(fd[0]);
        int start = 100 , end = 200;
        write(fd[1],&start,sizeof(int));
        write(fd[1],&end,sizeof(int));
        printf("父进程写入完毕\n");
    }else{
        close(fd[1]);
        int start , end;
        read(fd[0],&start,sizeof(int));
        read(fd[0],&end,sizeof(int));
        printf("start is %d,end is %d\n",start,end);
    }
    printf("===程序结束===\n");
    return 0;
}
