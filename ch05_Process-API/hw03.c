#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        printf("Hello, I am child\n");
    } else { // parent goes down this path (main)
        waitpid(rc);
        printf("Goodbye, I am parent\n");
    }
    return 0;
}
