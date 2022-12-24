#include "./server.h"


int main(int argc, char **argv) {

    int fd_pipe,fd_ppipe;
    char buffer[PIPE_BUF];
    int num_bytes;
    message m;
    char reply[]="My warmest greetings\0";
    int reply_len;


    if(mkfifo(NAMEDPIPE,0666)==-1) {
        perror("named pipe not created");
        exit(-1);
    }

    //the server opens the pipe in READ & WRITE mode
    //when clients are not running, the server can wait on READ
    //because it is still opened for writing
    //to stop the server, you must define a "command" that, when received by the server
    //will force the server to close the pipe
    if((fd_pipe=open(NAMEDPIPE,O_RDWR))==-1) {
        perror("named pipe not opened");
        exit(-1);
    }

    //in this example the server runs only once.
    //To wait for multiple clients, you must use a while loop
    while(true) {
        printf("Waiting for request...");

        if ((num_bytes = read(fd_pipe, &m, sizeof(m))) == -1) {
            perror("not possible to read from the pipe");
            exit(-1);
        }

        printf("Request received ...");

        printf("%s\n", m.text);

        if ((fd_ppipe = open(m.private_pipe, O_WRONLY)) == -1) {
            perror("private pipe not opened");
            exit(-1);
        }

        reply_len = strlen(reply);

        if (write(fd_ppipe, reply, reply_len + 1) == -1) {
            perror("cannot write to the private pipe");
            exit(-1);
        }

        //the client will stop wating for other messages on the pipe
        if(close(fd_ppipe)==-1) {
            perror("cannot close the pipe");
            exit(-1);
        }
    }

    if(close(fd_pipe)==-1) {
        perror("cannot close the pipe");
        exit(-1);
    }

    if(unlink(NAMEDPIPE)==-1) {
        perror("cannot delete the pipe");
        exit(-1);
    }
}