#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int shmid;
    key_t key = ftok(".", 'A');
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    pid_t pid = fork();
    if (pid > 0) {
        char *data = shmat(shmid, NULL, 0);
        strcpy(data, "Hello from parent");
        wait(NULL);
        printf("收到子进程的消息: %s\n", data);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    } else if (pid == 0) {
        sleep(1);
        char *data = shmat(shmid, NULL, 0);
        printf("收到父进程来的消息: %s\n", data);
        strcpy(data, "Hello from child");
        shmdt(data);
    }
    return 0;
}
