#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* print_hello(void* nothing) 
{
	if (nothing == NULL) 
		printf("hello world\n");
	return NULL;
}



int main() 
{
	pthread_t thread;

	pthread_create(&thread, NULL, &print_hello, NULL);

	pthread_join(thread, NULL);
	return 0;
}
