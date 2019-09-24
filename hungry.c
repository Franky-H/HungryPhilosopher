#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>     

#define NUM_THREAD   5

sem_t sem[NUM_THREAD];

void eating(int index)
{
	if(index==0)
	{
		printf("Philosopher %d is hungry\n",index+1);
		sem_wait(&sem[index]);
		sem_wait(&sem[NUM_THREAD-(index+1)]);
		printf("Philosopher %d takes fork %d and %d\n",index+1,NUM_THREAD-index,index+1 );
		printf("Philosopher %d is eating...\n");
		sleep(1);
		printf("Philosopher %d is putting for %d and %d\n",index+1,NUM_THREAD-index,index+1 );
		sem_post(&sem[index]);
		sem_post(&sem[NUM_THREAD-(index+1)]);
		printf("Philosopher %d is Thinking...\n",index+1);
		sleep(2);
	}
	else
	{
		printf("Philosopher %d is hungry\n",index+1);
		sem_wait(&sem[index-1]);
		sem_wait(&sem[index]);
		printf("Philosopher %d takes fork %d and %d\n",index+1,index,index+1);
		printf("Philosopher %d is eating...\n");
		sleep(1);
		printf("Philosopher %d is putting for %d and %d\n",index+1,index, index+1);
		sem_post(&sem[index-1]);
		sem_post(&sem[index]);
		printf("Philosopher %d is Thinking...\n",index+1);
		sleep(2);
	}
}

void *hello_thread(void *arg)
{
	int index = (int *)arg;
	while(1)
	{
		eating(index);
	}
}

int main(void)
{
	pthread_t tid[NUM_THREAD];
	int status, i;


	for(i=0;i<NUM_THREAD;i++)
		sem_init(&sem[i],0,1);

	for(i=0; i<NUM_THREAD; i++) {
		status = pthread_create(&tid[i], NULL, hello_thread, (void *)i);
		if(status != 0) {
			perror("thread create");
			exit(1);
		}
		
	}

	pthread_exit(NULL);	
    return 0;
}
