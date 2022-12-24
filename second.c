//
// Created by Utente on 07/12/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define PIPE_NAME "/tmp/named_pipe"
#define READ 0
#define WRITE 1

/*
In a loop, the client prompts the user to type a number.
The number is then passed to the server process using a named pipe.
*/

int main() {

    double number;
    char ans[1];
    int named_pipe;

    /* the named pipe is opened in write-only mode */
    if ((named_pipe = open(PIPE_NAME, O_WRONLY)) == -1) {
        perror("Error opening the pipe.");
        return -1;
    }

    while (true) {

        printf("\nDo you want to calculate a factorial? [y|n]\n");
        scanf("%c", ans);

        if (strcmp(ans, "n") == 0){
            printf("\nBye\n");
            exit(0);
        }

        else if (strcmp(ans, "y") == 0){

            printf("Type the number.\n");
            scanf("%lf", &number);

            if(write(named_pipe, &number, sizeof(number))==-1){  //writing on the named pipe
                perror("error during writing in the named pipe");
                return -1;
            }
        }

        else{
            printf("What?\n");
        }

        while (getchar() != '\n'); // A trick to empty the standard input
    }
}