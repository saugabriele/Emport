#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(){

    char string_1[100], string_2[100];

    printf("Inserisci la prima stringa:\n");
    scanf("%['\n']",string_1);
    printf("Inserisci la seconda stringa(file name):\n");
    scanf("%c",string_2);
    strcat(string_2,".txt");

    if((execl("./called","called",string_1,string_2,(char *) NULL))==-1)
    {
        perror("Error:");
        exit(-1);
    }

    return 0;
}