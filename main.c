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
    int pid;
    double fact, number;
    bool go_ahead;
    int numpipe[2], controlpipe[2];
    char ans[1];
    FILE *file;

    if (pipe(numpipe) == -1)
    {
        perror("Eror opening pipe");
        exit(-1);
    }

    if (pipe(controlpipe) == -1)
    {
        perror("Eror opening pipe");
        exit(-1);
    }

    if((pid = fork()) == -1)
    {
        perror("Error:");
        exit(-1);
    }

    switch(pid)
    {
        case 0:
            close(controlpipe[WRITE]);
            close(numpipe[WRITE]);

            while(true)
            {
                if(read(controlpipe[READ],&go_ahead,sizeof(go_ahead))==-1)
                {
                    perror("Error reading: ");
                    return (-1);
                }
                if(!go_ahead)
                {
                    exit(0);
                }

                if(read(numpipe[READ], &number, sizeof(number))==-1)
                {
                    perror("Error reading: ");
                    return(-1);
                }
                fact = number;
                while(number >= 2)
                {
                    fact *= (number - 1);
                    number--;
                }
                if(fprintf(file, "%f = %f\n",number,fact)==-1)
                {
                    perror("Error writing file");
                    return(-1);
                }
            }


        default:
            close(controlpipe[READ]);
            close(numpipe[READ]);

            printf("Do you want to calculate a factorial? [y/n]\n");
            scanf("%c", ans);

            if(strcmp(ans,"n") == 0)
            {
                go_ahead = false;
                if(write(controlpipe[WRITE],&go_ahead,sizeof(go_ahead))==-1)
                {
                    perror("Error:");
                    exit(-1);
                }
                printf("Bye");
                exit 0;
            }
            else if(strcmp(ans,"y") == 0)
            {
                go_ahead(true);
                if(write(controlpipe[WRITE],&go_ahead,sizeof(go_ahead))==-1)
                {
                    perror("Error:");
                    exit(-1);
                }

                printf("Type the number: \n");
                scanf("%lf", &number);

                if(write(numpipe[WRITE],&number,sizeof(number))==-1) {
                    perror("Error: ");
                    exit(-1);
                }
            }
            else
            {
                printf("What?\n");
            }
            while(getchar()!= "\n");
            wait(NULL);
    }
}