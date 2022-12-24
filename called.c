#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#define NAMEDPIPE "/tmp/dummy"
#define NUMBER_TRIES 5
#define SLEEP_TIME 5
#define MAX_TEXT 200


typedef struct {
    char text[MAX_TEXT];
    char private_pipe[MAX_TEXT];
} message;