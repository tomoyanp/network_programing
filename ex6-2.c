/* pthreads-inc.c */
#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <math.h>

#define NUM_THREADS 20 
#define NUM_MAX 1000

void *do_calc(void *mutex); 
pthread_t tid[NUM_THREADS]; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int param; 
int sum;
int main(){ 
	int i;
	void *thread_return;
	sum = 0; 
	param = 0; 
	for(i=0;i<NUM_THREADS;i++){
		pthread_create(&tid[i],NULL,do_calc, &mutex);
	} for(i=0; i<NUM_THREADS; i++){
		pthread_join(tid[i], &thread_return);
	} 
	printf("Sum %d\n",sum); 
	return 0;
}
void *do_calc(void *mutex){ int i;
	pthread_mutex_t* mt = (pthread_mutex_t*) mutex;
	pthread_mutex_lock(mutex);
	for(i=1;i<=NUM_MAX;i++){ 
		sum = sum + i;
	} 
	pthread_mutex_unlock(mutex);
	pthread_exit(NULL);
}
