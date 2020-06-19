#if 0
/*
 ============================================================================
 Name        : test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
#endif
//============================================================================
// Name        : test.cpp
// Author      : Aghil
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//  Sum computed by the background thread
struct sum_runner_struct {
	long long *limit;
	long long *answer;
};

//thread function to generate sum of 0 to N
void* sum_runner( void* arg)
{
	struct sum_runner_struct *arg_struct = (struct sum_runner_struct*) arg;	
	long long sum = 0;
	long long limit;
	long long *limitPtr = arg_struct->limit;
	long long *answerPtr = arg_struct->answer;
	limit = *limitPtr;
	answerPtr = malloc(sizeof( *answerPtr));
	free(limitPtr);

	for(long long i = 0; i <= limit; i++)
	{
		sum += i;
		//printf("\nIn runner thread limit %lld i %lld sum %lld", arg_struct->limit, i, sum);
	}
	//sum is global variable, so other threads can access
	// do someting else
	
	*answerPtr = sum;
	pthread_exit(answerPtr);
}
int main( int argc, char **argv)
{
	if(argc <2)
	{
		printf("\nUsage: %s <num>\n", argv[0]);
		return 0;
	}

	int num_args = argc - 1;

	struct sum_runner_struct args[num_args];

	// Thread ID:
	pthread_t tid[num_args];
	for(int i = 0; i < num_args; i++)
	{
		args[i].limit = malloc(sizeof(*args[i].limit ));
		*args[i].limit = atoll(argv[i+1]);
		// Create attribute
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		//printf("\nIn main thread limit %lld i %d  answer %lld", args[i].limit, i, args[i].answer);
		pthread_create(&tid[i], &attr, sum_runner, &args[i]);
	}

	for(int i = 0; i < num_args; i++)
	{
		long long *sum;
		sum = malloc(sizeof(*sum));
		//Wait until thread is done its work
		pthread_join(tid[i], (void**)&sum);
		printf("\ni %d tid %lu Sum is %lld\n", i, tid[i], *sum);
	}


}
