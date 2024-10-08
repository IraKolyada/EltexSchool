#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_PTHR 5

long incr;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *calc_pthr(){

	for(int i = 0; i < 10000000; i++){
		pthread_mutex_lock(&m1);
		incr++;
		pthread_mutex_unlock(&m1);
	}

	return NULL;
}

int main(void){
	pthread_t tid[NUM_PTHR] = {0};
	int *s = NULL;

	for (int i = 0; i < NUM_PTHR; i++)
		pthread_create(&tid[i], NULL, calc_pthr, NULL);

	for (int i1 = 0; i1 < NUM_PTHR; i1++)
		pthread_join(tid[i1], (void**) &s);

	printf("incr = %ld\n",incr);

	return 0;
}