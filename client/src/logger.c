#include "../include/logger.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct log_info {
    int file_descriptor;
} log_info_t;

static log_info_t log_info = {0};

static const char* const event_to_string[] = {"IWANT", "RECVD", "TSKEX",
                                              "TSKDN", "GOTRS", "2LATE",
                                              "CLOSD", "GAVUP", "FAILD"};

int write_log(enum Event event, message_t* info) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    time_t instant = time(NULL);

    char out[128] = "";
    snprintf(out, sizeof(out), "%lu ; %d ; %d ; %d ; %lu ; %d ; %s\n", instant,
             info->rid, info->tskload, pid, tid, info->tskres,
             event_to_string[event]);

    int err;
    while ((err = write(log_info.file_descriptor, out, strlen(out))) == -1 &&
           errno == EINTR) {
    }

    if (err < 0) {
        return errno;
    }

    return 0;
}

int open_log() {
    log_info.file_descriptor = STDOUT_FILENO;

    return 0;
}
