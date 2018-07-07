#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("I am parent\n");
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child: redirect standard output to a file
        printf("I am child (before closing standard output)");
        close(STDOUT_FILENO);
        printf("I am child (after closing standard output)");
    } else { // parent goes down this path (main)
        int wc = wait(NULL);
    }
    return 0;
}
