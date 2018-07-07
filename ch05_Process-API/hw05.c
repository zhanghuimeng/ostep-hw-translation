#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("I am parent (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("I am child (pid:%d)\n", (int) getpid());
        int wc = wait(NULL);
        printf("wait() returns %d\n", wc);
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
        printf("wait() returns %d\n", wc);
    }
    return 0;
}