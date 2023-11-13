#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
void producer(int write_fd) {
    char data[10];
    for (int i = 1; i <= 5; i++) {
        snprintf(data, sizeof(data), "数据 %d\n", i);  
        write(write_fd, data, strlen(data) + 1);
        sleep(1); 
    }
    close(write_fd);
}

void consumer(int read_fd) {
    char data[10];
    while (read(read_fd, data, sizeof(data)) > 0) {  
        printf("接收: %s\n", data);  
    }
    close(read_fd);
}
int main() {
    int pipe_fd[2];
    pid_t pid = fork();  
    if (pid > 0) { 
        close(pipe_fd[0]);  
        producer(pipe_fd[1]);  
        close(pipe_fd[1]); 
        wait(NULL);  
    } else if (pid == 0) {  
        close(pipe_fd[1]); 
        consumer(pipe_fd[0]); 
        close(pipe_fd[0]);
    }
    return 0;
}
