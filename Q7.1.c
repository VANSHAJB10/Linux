/*Implement the producer consumer problem using pthreads and mutex operations. 
Test Cases:
(a) A producer only produces if buffer is empty and consumer only consumes if some 
content is in the buffer.
(b) A producer produces(writes) an item in the buffer and consumer 
consumes(deletes) the last produces item in the buffer.
(c) A producer produces(writes) on the last consumed(deleted) index of the buffer*/


#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<stdlib.h>


pthread_mutex_t lock;
int arr[10] = {-1,3};
int empty= 9;
int full = 1;


void *produce(){
	if(empty == 11){
	pthread_mutex_lock(&lock);
	int temp = rand()%100;
	printf("Writing %d in to buffer\n",temp);
	arr[++full] = temp;
	empty--;
	pthread_mutex_unlock(&lock);
	}
	else{
		printf("Sorry the buffer is not empty\n");
	}
}

void *consumer(){
	if(empty != 11){
	pthread_mutex_lock(&lock);
	printf("Reading %d from the buffer\n",arr[full--]);
	empty++;
	pthread_mutex_unlock(&lock);
	}
	else{
		printf("Sorry the buffer is empty\n");
	}
}

int main(){
	pthread_t p1,p2,p3,p4;
	pthread_create(&p1,NULL,consumer,NULL);
	pthread_create(&p2,NULL,consumer,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_create(&p1,NULL,produce,NULL);
	pthread_create(&p2,NULL,produce,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_create(&p1,NULL,consumer,NULL);
	pthread_join(p1,NULL);
	return 0;
}
