#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(){
    int pid;
    char string_1[100], string_2[100];

    printf("Inserisci la prima stringa:\n");
    scanf("%['\n']",string_1);
    printf("Inserisci la seconda stringa(file name):\n");
    scanf("%c",string_2);
    strcat(string_2,".txt");

    if((pid=fork()) == -1)
    {
        perror("Error:");
        exit(-1);
    }

    switch (pid) {
        case 0:
            printf("First child PID: %d\n",getpid(),getppid());
            if((pid=fork()) == -1)
            {
                perror("Error:");
                exit(-1);
            }
            switch(pid){
                case 0:
                    printf("Second child PID: %d  %d\n",getpid(),getppid());
                    exit(0);
            }
            exit(0);

        default:
            printf("Parent PID: %d\n",getpid());
    }

    return 0;
}