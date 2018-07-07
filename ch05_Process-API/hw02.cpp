#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int fd = open("./hw02.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child
        write(fd, "I am child");
    } else { // parent goes down this path (main)
        write(fd, "I am parent");
    }
    return 0;
}