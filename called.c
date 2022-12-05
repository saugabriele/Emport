//
// Created by Utente on 05/12/2022.
//
#include <stdio.h>

int main(int args,char  **kargs)
{
    FILE *file;
    file = fopen(kargs[2],"w");

    if(file!=NULL)
    {
        fprintf(file,"%s\n",kargs[1]);
    }
    else
    {
        printf("Error opening the file!");
    }
    return 0;
}