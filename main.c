#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char *argv[])
{
    int fd_namedpipe, num;
    int fact;
    FILE *output_file;

    if(unlink("/named_pipe") == -1)
    {
        perror("Error unlinking the pipe\n");
        return -1;
    }

    if(mkfifo("/named_pipe",0777) == -1)
    {
        perror("Error creating named pipe");
        return -1;
    }

    if((fd_namedpipe = open("/named_pipe",O_RDWR)) == -1)
    {
        perror("Error opening the named pipe");
        if(close(fd_namedpipe)==-1)
        {
            perror("Error cosing th pipe\n");
        }
        exit(-1);
    }

    while(true) {
        if ((num = read(fd_namedpipe, &num, sizeof(int))) == -1) {
            perror("Error reading the named pipe");
            exit(-1);
        }

        switch (fork()) {
            case -1:
                perror("Error creating a child process");
                exit(-1);

            case 0:
                for (int i = num; i > 2; i--) {
                    num *= num - 1;
                }

                output_file = fopen("output.txt", "a"); // opening the output file

                if ((fprintf(output_file, "%f! = %f\n", num, fact)) == -1){ // writing on the file
                    perror("error during writing in the file\n");
                    return -1;
                }

                fclose(output_file);
                break;
        }
    }

    if(close(fd_namedpipe) == -1)
    {
        perror("Cannot close the pipe");
        exit(-1);
    }
}