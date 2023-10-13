#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
        char *args[]={"ls","-l","/home/enderkc",NULL};
        char *envp[]={0,NULL};
        execve("/bin/ls",args,envp);
}
