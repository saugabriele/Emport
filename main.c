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
Each time the server recieves a number, it generates a child.
The child calculates the factorial of that number and it writes the result in a text file.
*/

int remove_pipe(int pipedes);

int main()
{

    double number, fact;
    int named_pipe;
    FILE *output_file;


    if (unlink(PIPE_NAME) == -1){  // necessary if the pipe already exists
        perror("Error unlinking the pipe");
        return -1;
    }


    // creation of a named pipe with RW permssions
    if (mkfifo(PIPE_NAME, 0666) == -1)
    {
        perror("Error creating the named pipe.");
        return -1;
    }


    /* the pipe is opened in read and write mode because if you open it in read-only mode, the function read won't be
        blocking as soon as the client will be closed */
    if ((named_pipe = open(PIPE_NAME, O_RDWR)) == -1)
    {
        perror("Error opening the pipe.");
        if (remove_pipe(named_pipe) == -1)
            perror("Error closing/removing the pipe.");
        return -1;
    }




    printf("Server is running.\n\n");

    while (true){

        if (read(named_pipe, &number, sizeof(number)) == -1){	 // reading from the named pipe
            perror("Error reading from pipe.");
            return -1;
        }

        switch (fork())
        {

            case -1:
                perror("Server - fork error");
                exit(-1);

            case 0:
                //--- CHILD ------------------------------------------------------

                fact = 1;
                for (int i = 1; i <= number; i++){      	// calculating the fatorial
                    fact *= i;
                }


                output_file = fopen("output.txt", "a"); // opening the output file

                if ((fprintf(output_file, "%f! = %f\n", number, fact)) == -1){ // writing on the file
                    perror("error during writing in the file\n");
                    return -1;
                }

                fclose(output_file);
                break;
        }
    }
}

int remove_pipe(int pipedes)
{
    if (close(pipedes) == -1)
        return -1;
    if (unlink(PIPE_NAME) == -1)
        return -1;
    return 0;
}