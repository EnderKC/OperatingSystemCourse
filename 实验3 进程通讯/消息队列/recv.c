#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
    long mtype;
    int start;
    int end;
} Msg;

int main(int argc, char **argv) {
    key_t key = ftok("a.txt", 'A');
    printf("key:%d\n", key);
    int msq_id = msgget(key, IPC_CREAT | 0666);
    printf("msq_id:%d\n", msq_id);
    Msg buff;

    for (int i = 0; i < 10; i++) {
        msgrcv(msq_id, &buff, sizeof(buff) - sizeof(long), i, 0);
        printf("接收来自消息队列的消息：%ld, %d, %d\n", buff.mtype, buff.start, buff.end);
    }

    return 0;
}
