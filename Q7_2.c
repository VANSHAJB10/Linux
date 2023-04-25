#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t rdr;
pthread_mutex_t wrt;
int shared = 9982,rdrCount = 0;
int stop = 0;

void *writ(){
	pthread_mutex_lock(&wrt);
	shared = 90;
	printf("func A Writing...\n");
	sleep(5);
	printf("Value changed to %d\n",shared);
	pthread_mutex_unlock(&wrt);
}

void *read1(){
	rdrCount++;
	if(rdrCount == 1){
		sem_wait(&rdr);
		pthread_mutex_lock(&wrt);
		sem_post(&rdr);	
	}
	sem_wait(&rdr);
	printf("Value read of the shared is %d\n",shared);
	rdrCount--;
	if(rdrCount == 0)
		pthread_mutex_unlock(&wrt); // After the final reader wrt mutex will be released
		sleep(1);
	sem_post(&rdr);
}

int main(){
	sem_init(&rdr,0,1);
	pthread_t p1,p2,p3,p4,p5;
	pthread_create(&p1,NULL,read1,NULL);
	pthread_create(&p2,NULL,writ,NULL);
	pthread_create(&p3,NULL,read1,NULL);
	//pthread_create(&p4,NULL,writ1,NULL);
	pthread_create(&p5,NULL,read1,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);	
	pthread_join(p3,NULL);
	//pthread_join(p4,NULL);
	pthread_join(p5,NULL);
	return 0;
}
