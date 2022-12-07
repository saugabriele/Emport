//
// Created by Utente on 05/12/2022.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int args,char  **kargs)
{
    char stringa[100];
    while(true) {
        printf("Inserisci la stringa: \n");
        scanf("%s",stringa);
        write(1, stringa, sizeof(stringa));
        if(strcmp(stringa,"exit!") == 0) {
            perror("first exit");
            return 0;
        }
    }
}