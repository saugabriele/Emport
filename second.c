#include "./server.h"

int main(int argc, char **argv) {

    int fd_pipe, fd_ppipe;
    char buffer[PIPE_BUF];
    int num_bytes;
    char welcome[]="This is a message for the server";
    int w_len;
    int i = NUMBER_TRIES;
    message m;

    //the client checks that the server is running by
    //verifying that the "public" named pipe exists
    //if not, the client is put in "sleep mode" for SLEEP_TIME seconds
    //the tries again NUMBER_TRIES times
    while(access(NAMEDPIPE,F_OK)&&i>0) {
        printf("Trying (%d)\n",i);
        sleep(SLEEP_TIME);
        i--;
    }

    if(i==0) {
        printf("server not running\n");
        exit(0);
    }

    if((fd_pipe=open(NAMEDPIPE,O_WRONLY))==-1) {
        perror("named pipe not opened");
        exit(-1);
    }

    //creating a filename binded to the client
    //this filename will be used for the "private" pipe
    //that the server will use to send messages to the client
    sprintf(m.private_pipe,"/tmp/ppipe%d",getpid());

    if(mkfifo(m.private_pipe,0666)==-1) {
        perror("private pipe not created");
        exit(-1);
    }

    strcpy(m.text,welcome);

    if((num_bytes=write(fd_pipe,&m,sizeof(m)))==-1) {
        perror("unable to write to the pipe");
        exit(-1);
    }

    //the private pipe is opened in READ ONLY mode to sync the client
    //with the server. When the server will close the WRITE end,
    //the client will stop waiting for messages
    //NOTE: the private pipe must be opened after sending the name to the server
    //opening in READ ONLY mode is blocked until the server opens in WRITE mode

    if((fd_ppipe=open(m.private_pipe,O_RDONLY))==-1) {
        perror("private pipe not opened");
        exit(-1);
    }

    memset(buffer,'\0',PIPE_BUF);
    while((num_bytes=read(fd_ppipe,buffer,PIPE_BUF))>0) {
        printf("%s\n",buffer);
        memset(buffer,'\0',PIPE_BUF);
    }

    if(close(fd_ppipe)==-1)
        perror("unable to close the private pipe");
    if(unlink(m.private_pipe)==-1)
        perror("unable to unlik the private pipe");
}