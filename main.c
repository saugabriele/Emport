#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    int fd;
    char string_1[100], string_2[100];

    printf("Inserisci la prima stringa:\n");
    scanf("%['\n']",string_1);
    printf("Inserisci la seconda stringa(file name):\n");
    scanf("%c",string_2);
    strcat(string_2,".txt");

    fd = open(string_2, O_WRONLY|O_CREAT|O_APPEND,0644);

    if(fd==-1)
    {
        perror("Error:");
        exit(-1);
    }
    if(fd==0)
    {
        dup2(fd,1);
        if((execl("./called","called",string_1,(char *) NULL))==-1)
        {
            perror("Error:");
            exit(-1);
        }
    }



    return 0;
}