#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int x;
    x = 100;
    printf("x = %d (pid:%d)\n", &x, (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("child: x = %d (pid:%d)\n", &x, (int) getpid());
        x = 99;
        printf("child: x = %d (pid:%d)\n", &x, (int) getpid());
    } else { // parent goes down this path (main)
        printf("parent: x = %d (pid:%d)\n", &x, (int) getpid());
        x = 101;
        printf("parent: x = %d (pid:%d)\n", &x, (int) getpid());
    }
    return 0;
}