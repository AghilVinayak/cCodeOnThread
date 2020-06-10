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
//#include <windows.h>
#include "pthread.h"

//  Sum computed by the background thread
	long long sum = 0;

//thread function to generate sum of 0 to N
void* sum_runner( void* arg)
{
	long long *limit_ptr = (long long*) arg;
	long long limit = *limit_ptr;


	for(long long i = 0; i <= limit; i++)
	{
		sum += i;
		printf("\nIn runner thread limit %lld i %lld sum %lld", limit, i, sum);
	}
	//sum is global variable, so other threads can access
	// do someting else
	
	pthread_exit(0);
}
int main( int argc, char **argv)
{
	if(argc <2)
	{
		printf("\nUsage: %s <num>\n", argv[0]);
		return 0;
	}

	int num_args = argc - 1;
	long long limit; 

	// Thread ID:
	pthread_t tid[num_args];
	for(int i = 0; i < num_args; i++)
	{
		limit = atoll(argv[i+1]);

		// Create attribute
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		printf("\nIn main thread limit %lld i %d sum %lld", limit, i, sum);
		pthread_create(&tid[i], &attr, sum_runner, &limit);
	}

	for(int i = 0; i < num_args; i++)
	{
		//Wait until thread is done its work
		pthread_join(tid[i],NULL);
	}

	printf("\nSum is %lld\n", sum);

}
