#include <unistd.h>  
#include <stdio.h>  
  
int main()  
{  
    int pipefd[2];  
    char buf[80];  
    pid_t pid;  
      
    pipe(filedes);
    
    int rc[2];
    rc[0] = fork();
    
    if (rc[0] < 0)  // fork failed
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc[0] == 0)  // child 1
    {  
        printf("Child 1 (pid=%d), writing to pipe.\n", (int) getpid());
        char s[] = "Hello world , this is write by pipe.\n";
        write(pipefd[1], s, sizeof(s));
        close(pipefd[0]);
        close(pipefd[1]);
    }  
    else  // parent
    {
        wait(NULL);
        rc[1] = fork();
        if (rc[1] < 0) {  // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc[1] == 0) {  // child 2
            printf("Child 2 (pid=%d), reading from pipe.\n", (int) getpid());
            read(pipefd[0], buf, sizeof(buf));  
            printf("%s\n", buf);
            close(pipefd[0]);  
            close(pipefd[1]);  
        }
        else {  // parent
            wait(NULL);
        }
    }
    return 0;  
}  