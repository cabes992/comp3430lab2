#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 42;
int main()
{

    printf("Starting with %d, and my parent is %d\n",getpid(), getppid());
    // child process because return value zero
    // We can still fetch the parent pid (From where?)
    int newPid = fork();
    // child is here, too
    if (newPid == 0)
    {
        printf("I'm a baby!\n");
        printf("Baby is %d, and my parent is %d\n",getpid(), getppid());
        sleep(1);
        printf("baby %d\n", global);
        global = 0;
        // we still have everything from the parent here
        // but it's ours.
    }
    else
    {
        // parents get the child's pid
        printf("Hello from Parent! I am a parent of %d\n", newPid);

        printf("parent %d\n", global);
        global++;
        printf("parent %d\n", global);
        // we can wait for the child
        // (but don't have to)
        // man wait
        // man waitpid
        wait(&newPid);
        printf("parent %d\n", global);
    }
    printf("Done %d \n", getpid());
}
