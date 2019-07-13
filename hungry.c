#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>     
#define N 5


struct msg{
	long mtype;
	int fork1;
	int fork2;
	int state[N];
} gmsg;



int main()
{

	pid_t pid[5];
	key_t key = 0;
	
	int i;
	int mqid;
 
	key=ftok("sample_run_3",0);
	mqid=msgget(key,IPC_CREAT);
 

	for(i=0;i<5<i++)
		{
		pid[i]=fork();
		if(pid[i]==0)
			{
				while(1)
				{
				printf("philosopher%d is hungry...",i);
				}
			}

		}

	
}