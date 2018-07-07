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
    } else if (rc == 0) { // child
        printf("I am child (pid:%d)\n", (int) getpid());
        int wc = waitpid(-1, NULL, 0);
        printf("Child: waitpid(-1) returns %d\n", wc);
    } else { // parent
        int wc = waitpid(rc, NULL, 0);
        printf("Parent: waitpid(%d) returns %d\n", rc, wc);
    }
    return 0;
}
