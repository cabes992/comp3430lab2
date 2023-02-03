
#include <stdio.h>   // for printf, reading a file
#include <pthread.h> // pthread
#include <unistd.h>  // for sleep

struct threadInfo
{
    int aNumber;
};

// global variable
int datGlobal = 0;

void *work(void *ignored)
{
    printf("Thread has started\n");
    printf("In thread %d\n", datGlobal);

    //sleep(2);
    printf("In thread %d\n", datGlobal);
    datGlobal = 42;
    printf("Done!\n");
    pthread_exit(NULL);
}

int main()
{

    pthread_t thread;
    struct threadInfo threaddata;

    printf("I am %d\n", getpid());

    threaddata.aNumber = 42;

    printf("Starting\n");
    
    pthread_create(&thread, NULL, &work, NULL);
    // wait 1 second, set
    sleep(1);
    datGlobal = 420;

    printf("waiting\n");
    printf("%d", datGlobal);

    pthread_join(thread, NULL);
    printf("Joining %d\n", datGlobal);


    return 0;
}
