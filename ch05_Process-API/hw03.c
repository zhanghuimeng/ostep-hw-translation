#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        printf("I am child\n");
    } else { // parent goes down this path (main)
        while ((kill(rc, 0) != ESRCH)) {
            sleep(0);
        }
        printf("I am parent\n");
    }
    return 0;
}