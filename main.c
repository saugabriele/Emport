#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#define READ 0
#define WRITE 1


int main() {
    int fd, my_pipe[2];

    fd = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);

    if(fd == -1)
    {
        perror("Error opening the file\n");
        exit(-1);
    }

    switch(fork())
    {
        case -1:
            perror("Error fork");
            exit(-1);

        case 0:
            close(my_pipe[READ]);

            if(dup2(my_pipe[WRITE],STDOUT_FILENO)==-1)
            {
                perror("Error dup2");
                exit(-1);
            }

            if(execl("./first","first",(char *) NULL)==-1)
            {
                perror("Error exec");
                exit(-1);
            }
        break;
    }

    close(my_pipe[WRITE]);

    if(dup2(my_pipe[READ],STDIN_FILENO)==-1)
    {
        perror("Error dup");
        exit(-1);
    }

    printf("Write <exit!>  to exit\n");

    if(dup2(fd,STDOUT_FILENO)==-1)
    {
        perror("Error dup");
        exit(-1);
    }

    if(execl("./second","second",(char *) NULL)==-1)
    {
        perror("Error exec");
        exit(-1);
    }
}