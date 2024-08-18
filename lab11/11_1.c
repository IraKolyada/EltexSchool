#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_PTHR 5

void *print_pthr(){
	printf("thread %ld\n", pthread_self());

	return NULL;
}

int main(void){
	pthread_t tid[NUM_PTHR];

	for (int i = 0; i < NUM_PTHR; i++)
		pthread_create(&tid[i], NULL, print_pthr, NULL);
	for (int i = 0; i < NUM_PTHR; i++)
		pthread_join(tid[i], NULL);

	return 0;
}