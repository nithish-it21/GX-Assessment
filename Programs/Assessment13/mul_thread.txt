#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

#define SIZE 10000000
#define NUM_OF_THREADS 4

//[0    250000      500000       750000           1000000]

int* arr;
int* partial_sum;


void* add_sum(void* arg){

	pthread_t p_id = pthread_self();
	int thread_id  = *(int*)arg;
	int start = thread_id * (SIZE / NUM_OF_THREADS);
	int end = (thread_id + 1) * (SIZE / NUM_OF_THREADS);
	partial_sum[thread_id] = 0;
	for(int i=start; i<end; i++){
		partial_sum[thread_id] += arr[i];
	}
	printf("Process id of thread: %d\n",(int)p_id);
	return NULL;

}

int* sum_ord(int* temp){
	int* tot = (int*)malloc(sizeof(int));
	*tot = 0;
	for(int i=0; i<SIZE; i++){
		*tot+=temp[i];
	}
	return tot;
}

void main(){
	
	srand(time(NULL));

	arr = (int*)malloc(sizeof(int) * SIZE);
	partial_sum = (int*)malloc(sizeof(int) * NUM_OF_THREADS);
	
	int min = 1;
	int max = 100;


	for(int i=0; i<SIZE; i++){
		arr[i] = rand() % (max - min + 1) + min;
		//printf("%d\n",arr[i]);
	}

	pthread_t threads[NUM_OF_THREADS];

	time_t start, end;
	double total_time_t;
	start = clock();
	for(int i=0; i<NUM_OF_THREADS; i++){
		int* thread_id = (int*)malloc(sizeof(int));
		*thread_id = i;
		pthread_create(&threads[i],NULL,add_sum,thread_id);	
	}
	end = clock();
	total_time_t = ((double)(end-start)/CLOCKS_PER_SEC);
	printf("The time taken by the thread to complete the program: %f\n",total_time_t);
	
	for(int i=0; i<NUM_OF_THREADS; i++){
		pthread_join(threads[i],NULL);
	}

	int total_sum = 0;
	for(int i=0; i<NUM_OF_THREADS; i++){
		total_sum += partial_sum[i];
	}

	int p_id = getpid();
	printf("Process id of main function %d\n",p_id);
	printf("The total sum with multi thread is %d\n",total_sum);
	start = clock();
	printf("The total sum with process is %d\n",*sum_ord(arr));	
	end = clock();
	total_time_t = ((double)(end-start) / CLOCKS_PER_SEC);
	printf("The time taken by the normal function to complete the program: %f\n",total_time_t);

	free(arr);
	free(partial_sum);

}
