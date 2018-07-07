#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            printf("Parent: ready for execl(const char *path, const char *arg, ... /* (char  *) NULL */)\n");
            break;
        case 1:
            printf("Parent: ready for execlp(const char *file, const char *arg, ... /* (char  *) NULL */)\n");
            break;
        case 2:
            printf("Parent: ready for execle(const char *path, const char *arg, ... /*, (char *) NULL, char * const envp[] */)\n");
            break;
        case 3:
            printf("Parent: ready for execv(const char *path, char *const argv[])\n");
            break;
        case 4:
            printf("Parent: ready for execvp(const char *file, char *const argv[])\n");
            break;
        case 5:
            printf("Parent: ready for execvpe(const char *file, char *const argv[], char *const envp[])\n");
            break;
        default:
            printf("Should not come here\n");
            exit(1);
            break;
        }
        int rc = fork();
        if (rc < 0) { // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) { // child
            char *argv[] = {"ls", "/", NULL};
            switch (i) {
            case 0:
                execl("/bin/ls", "ls", "/", NULL);
                exit(1);
                break;
            case 1:
                execlp("ls", "ls", "/", NULL);
                exit(1);
                break;
            case 2:
                execle("/bin/ls", "ls", "/", NULL, NULL);
                exit(1);
                break;
            case 3:
                execv("/bin/ls", argv);
                exit(1);
                break;
            case 4:
                execvp("ls", argv);
                exit(1);
                break;
            case 5:
                execvpe("ls", argv, NULL);
                exit(1);
                break;
            default:
                printf("Should not come here\n");
                exit(1);
            }
        } else { // parent goes down this path (main)
            wait(NULL);
        }
    }
    return 0;
}
