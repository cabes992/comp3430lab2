#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int newPid = fork();

	if (newPid == 0) 
	{
		printf("Child process: %d", getpid());
		printf("hello world\n");
	}
	else 
	{
		wait(&newPid);
	}

}
