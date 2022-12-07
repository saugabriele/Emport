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
    int my_pipe[2];
    char stringa[100]:

    if(pipe(my_pipe) == -1)
    {
        perror("Error opening the pipe:");
        exit(-1);
    }

    printf("Insert your string:\n");
    scanf("%[^\n]", stringa);

    switch(fork())
    {
        case -1:
            perror("Error createing a child process\n");
            exit(-1);

        case 0:
            close(my_pipe[READ]);

            if(dup2(my_pipe[WRITE],1)==-1)
            {
                perror("Error dup");
                exit(-1);
            }

            if(execl("./called","called",stringa,(char *) NULL)==-1)
            {
                perror("Error executing");
                exit(-1);
            }
            break;

        default:
            close(my_pipe[WRITE]);

            if(read(my_pipe[READ], &stringa, sizeof(stringa))== -1)
            {
                perror("Error reading");
                exit(-1);
            }

            printf("La stringa è: %s",stringa);
            wait(NULL);
            break;
    }
}