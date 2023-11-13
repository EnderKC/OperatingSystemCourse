#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct{
        long mtype;
        int start;
        int end;
}Msg;

int main(int argc, char **argv)
{
    key_t key = ftok("a.txt",'A');
    printf("key:%d\n",key);
                                                                        
    Msg* msgs[10];
    for (int i = 0; i < 10; i++)
    {
        msgs[i] = (Msg*)malloc(sizeof(Msg));
        msgs[i]->mtype = i;
        msgs[i]->start = i*100;
        msgs[i]->end = i*200;
    }
    
	int msq_id = msgget(key,IPC_CREAT|0666); 
    printf("msq_id:%d\n",msq_id);
	for (int i = 0; i < 10; i++)
    {
        printf("发送的数据 %ld ,%d ,%d\n",msgs[i]->mtype,msgs[i]->start,msgs[i]->end);
        msgsnd(msq_id,&msgs[i],sizeof(msgs[i]) - sizeof(long),IPC_NOWAIT) ;
        sleep(1);
    }
}

