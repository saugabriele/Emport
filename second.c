//
// Created by Utente on 07/12/2022.
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(){
    char word[100];
    int i=0;

    while(i<100)
    {
        if(read(STDIN_FILENO,&word,sizeof(word))==-1)
        {
            perror("Error reading");
            exit(-1);
        }
        if(strcmp(word, "exit!") == 0)
        {
            perror("second exit");
            return 0;
        }

        fprintf(stdout, "%s ",word);
        i++;
    }
}