#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define CUSTOMER_NEED_MAX 100000
#define CUSTOMER_NEED_MIN 0
#define SHOP_CAPACITY_MAX 10000
#define SHOP_CAPACITY_MIN 1
#define WORKER_LOAD_MAX 5000
#define WORKER_LOAD_MIN 1
#define CUSTOMERS_COUNT 3
#define SHOPS_COUNT 5

pid_t gettid(void);

typedef struct customer_t{
	int need;
	int current_need;
	int idx;
	int active;
	pthread_t thread;
} customer_t;

typedef struct shop_t{
	pthread_mutex_t mutex;
	int capacity;
	int idx;
} shop_t;

int active_customers = 3;
int worker_active = 1;

customer_t customers[CUSTOMERS_COUNT] = {0};
shop_t shops[SHOPS_COUNT] = {0};
pthread_t worker_thread = {0};

void *client_thread(void *_cidx);
void *worker_job(void *a);
int customer_enter_shop(uint8_t cidx, uint8_t sidx);

/**
 * randoms - getting a random number in a range
 * @begin_num: start of range
 * @end_num: end of range
 * 
 * return random number
*/
int randoms(int begin_num, int end_num){
	int new_num;

	new_num = begin_num + (rand() % (end_num - begin_num + 1));

	return new_num;
}

void halt(char *msg){
	perror(msg);
	exit(1);
}

/**
 * randoms_init - initialization of customers and shops
*/
void randoms_init(){
	printf("> INIT RANDOMS <\n");

	/* Init customers */
	for (int i = 0; i < CUSTOMERS_COUNT; i++){
		customers[i].need = randoms(CUSTOMER_NEED_MIN, CUSTOMER_NEED_MAX);
		customers[i].active = 1;
		customers[i].idx = i;

		printf("Client[%d]: set need %d\n", i, customers[i].need);
	}

	/* Init shops */
	for (int i = 0; i < SHOPS_COUNT; i++){
		shops[i].capacity = randoms(SHOP_CAPACITY_MIN, SHOP_CAPACITY_MAX);
		shops[i].idx = i;

		printf("Shop[%d]: set capacity %d\n", i, shops[i].capacity);
	}
}

/**
 * mutex_init - initialization of mutex
*/
void mutex_init(){
	printf("> INIT MUTEXES <\n");

	for (int i = 0; i < SHOPS_COUNT; i++){
		if (pthread_mutex_init(&shops[i].mutex, NULL)){
			for (int j = i; i >= 0; i--)
				pthread_mutex_destroy(&shops[j].mutex);

			halt("Cann't init mutexes");
		}
	}
}

/**
 * mutex_deinit - delete mutex
*/
void mutex_deinit(){
	printf("> DEINIT MUTEXES <\n");

	for (int i = 0; i < SHOPS_COUNT; i++)
		pthread_mutex_destroy(&shops[i].mutex);
}

int args[] = {0, 1, 2};

/**
 * threads_init - Creating a customers thread and a worker thread
*/
void threads_init(){
	int res = 0;
	printf("> INIT THREADS <\n");

	for (int i = 0; i < CUSTOMERS_COUNT; i++){
		res = pthread_create(&(customers[i].thread), NULL, client_thread, (void*)(&args[i])); // function performed - client_thread

		if (res){
			halt("Threads for clients");
		}
		printf("Client[%d]: created thread\n", i);
	}

	res = pthread_create(&worker_thread, NULL, worker_job, NULL); // function performed - worker_job

	if (res)
		halt("Worker thread create");

	printf("Worker: created thread\n");
}

/**
 * client_thread - Until the customer's needs are met, he performs the function "customer_enter_shop"
 * @_cidx: pointer thread number
*/
void *client_thread(void *_cidx){
	int cidx = *((int*)_cidx);
	printf("Client[%d] {%d}: start thread\n", cidx, gettid());

	while (customers[cidx].current_need < customers[cidx].need){
		for (int i = 0; i < SHOPS_COUNT; i++){
			int res = customer_enter_shop(cidx, i);

			switch (res){
				case 0:
					break;
				case 1:
					printf("Client[%d] {%d}: entered to shop[%d]\n", cidx, gettid(), i);
					sleep(1);
					break;
				default:
					printf("Client[%d {%d}: entered to shop[%d] failed with %d\n", cidx, gettid(), i, res);
					break;
			}
		}
	}

	printf("Client[%d] {%d}: done\n", cidx, gettid());

	customers[cidx].active = 0;
	active_customers--;
	return NULL;
}

/**
 * worker_enter_shop - worker fills an empty shop with a random number
 * @sidx:shop number
*/
int worker_enter_shop(uint8_t sidx){
	if (pthread_mutex_trylock(&shops[sidx].mutex))
		return 0;

	if (!shops[sidx].capacity){
		shops[sidx].capacity = randoms(WORKER_LOAD_MIN, WORKER_LOAD_MAX);
		printf("Worker: added %d to shop[%d]\n", shops[sidx].capacity, sidx);
	}

	pthread_mutex_unlock(&shops[sidx].mutex);

	return 1;
}

/**
 * worker_job - worker go to shops
*/
void *worker_job(void *a){
	while (active_customers > 0){
		for (int i = 0; i < SHOPS_COUNT; i++){
			if(worker_enter_shop(i))
				sleep(1);
		}
	}

	worker_active = 0;
	printf("Worker done\n");

	return NULL;
}

/**
 * customer_enter_shop - customer go to shops
 * @cidx: numder customer
 * @sidx: number shop
 * 
 * return 0 - if shop close -> customer go next
 * return 1 - if customer go shop -> customer made purchase (shop is empty)
*/
int customer_enter_shop(uint8_t cidx, uint8_t sidx)
{
	if (cidx >= CUSTOMERS_COUNT || sidx >= SHOPS_COUNT)
		return -1;

	if (pthread_mutex_trylock(&shops[sidx].mutex))
		return 0;

	customers[cidx].current_need += shops[sidx].capacity;

	printf ("Client[%d] {%d}: got %d from shop[%d]. Now have %d/%d\n",
			cidx, gettid(), shops[sidx].capacity, sidx, customers[cidx].current_need, customers[cidx].need);

	shops[sidx].capacity = 0;

	pthread_mutex_unlock(&shops[sidx].mutex);
	return 1;
}

int main()
{
	randoms_init();
	mutex_init();
	threads_init();

	while (active_customers > 0 && worker_active){
		printf("0.5-minute statistics:\n"
			   "\tActive customers: %d\n",
				active_customers);

		sleep(30);
	}

	mutex_deinit();
	return 0;
}
