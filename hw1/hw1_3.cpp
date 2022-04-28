#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/wait.h>
using namespace std;
#define MAX_LINE 80

int main(void)
{
	char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	int pid,i;
	string cmd;
	char* a;
	while(should_run){
		printf("osh>");
		fflush(stdout);
		getline(cin,cmd);
		if(strcmp(cmd.c_str(),"exit") == 0) break;
		pid = fork();
		if(pid < 0)
		{
			cout << "Error!" << endl;
			return 0;
		}
		else if(pid > 0)
			wait(NULL);
		else if(pid == 0)
		{
			a = strtok(strdup(cmd.c_str())," ");
			for(i=0;a;i++)
			{
				arg[i] = a;
				a = strtok(NULL," ");
			}
			arg[i] = NULL;
			execvp(arg[0],arg);
		}
	}

	return 0;
}


