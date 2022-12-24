//
// Created by Utente on 07/12/2022.
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int i = 5;
    int fd_namedpipe;
    int num;
    char ans[1];

    while(access("/named_pipe", F_OK) && i>0)
    {
        printf("Trying (%d)\n",i);
        spleep(5);
        i--;
    }

    if(i==0)
    {
        printf("server not running\n");
        exit(0);
    }

    if((fd_namedpipe = open("/named_pipe",O_WRONLY)) == -1)
    {
        perror("Error opening the named pipe\n");
        return(-1);
    }

    while(true) {
        printf("Do you want to calculate a factorial? [y/n]\n");
        scanf("%c",ans);

        if (strcmp(ans, "n") == 0){
            printf("\nBye\n");
            exit(0);
        }

        else if(ans == 'y') {
            printf("Select a number to calculate the fact:\n");
            scanf("%d", &num);

            if (write(fd_namedpipe, &num, sizeof(num)) == -1) {
                perror("Error writing on the pipe\n");
                exit(-1);
            }
        }
        else
            {
                printf("What?\n");
            }

        while (getchar() != '\n'); // A trick to empty the standard input
    }
}