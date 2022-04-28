#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main()
{
    int id;
    pid_t pid;
    pid = fork(); // fork0
    id = getpid();
    printf("pid = %d    \tid = %d f0\n",pid,id); // 0
    if(pid == 0)
    {
        pid = fork(); // fork1
        id = getpid();
        printf("pid = %d    \tid = %d f1\n",pid,id); // 1
        if(pid > 0)
            wait(NULL);
        pid = fork(); // fork2
        id = getpid();
        printf("pid = %d    \tid = %d f2\n",pid,id); // 2
        if(pid > 0)
            wait(NULL);
    }
    else if(pid > 0)
    {
        wait(NULL);
        pid = fork(); // fork3
        id = getpid();
        printf("pid = %d    \tid = %d f3\n",pid,id); // 3
        if(pid > 0)
            wait(NULL);
    }
    else
    {
        printf("Error!");
    }
    pid = fork(); // fork4
    id = getpid();
    printf("pid = %d    \tid = %d f4\n",pid,id); // 4
    if(pid > 0)
        wait(NULL);
    return 0;
}