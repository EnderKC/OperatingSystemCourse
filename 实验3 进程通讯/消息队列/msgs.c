#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

struct message {
    long type;
    char text[256];
};

void producer(int msqid) {
    struct message msg;
    for (int i = 1; i <= 5; i++) {
        msg.type = 1;
        snprintf(msg.text, sizeof(msg.text), "Data %d", i);
        sleep(1);
    }
}
void consumer(int msqid) {
    struct message msg;
    while (msgrcv(msqid, &msg, sizeof(struct message) - sizeof(long), 1, 0) != -1) {
        printf("Received: %s\n", msg.text);
    }
}
int main() {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    pid_t pid = fork();
    if (pid > 0) {
        producer(msqid);
        exit(0);
    } else if (pid == 0) {
        consumer(msqid);
    }
    return 0;
}
