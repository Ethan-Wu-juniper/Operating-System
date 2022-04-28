#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
using namespace std;

void print(int f)
{
    cout << "Fork " << f << ". I'm the child " \
    << getpid() << ", my parent is " << getppid() << "." << endl;
}

int main()
{
    pid_t pid;
    cout << "Main Process ID : " << getpid() << endl << endl;
    pid = fork(); // f1
    if(pid == 0) print(1);
    if(pid == 0)
    {
        pid = fork(); // f4
        if(pid == 0) print(4);
        if(pid > 0) wait(NULL);
        if(pid == 0) pid = fork(); // f5
        if(pid == 0) print(5);
        if(pid > 0) wait(NULL);
    }
    else if(pid > 0)
    {
        wait(NULL);
        pid = fork(); // f2
        if(pid == 0) print(2);
        if(pid > 0) wait(NULL);
        pid = fork(); // f3
        if(pid == 0) print(3);
        if(pid > 0) wait(NULL);
    }
    else if(pid < 0)
    {
        printf("Error!");
    }
    return 0;
}