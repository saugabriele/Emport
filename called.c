//
// Created by Utente on 05/12/2022.
//
#include <stdio.h>
#include <unistd.h>

int main(int args,char  **kargs)
{
    write(1, kargs[1],sizeof(kargs[1]));
}