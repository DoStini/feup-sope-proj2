#include "../include/fifo.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"

int get_fifo_name(char* res) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    return snprintf(res, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, tid);
}

int create_private_fifo() {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name(fifo);

    if (mkfifo(fifo, 0777) && errno != EEXIST) {
        perror("create fifo");
        return CANT_CREATE_FIFO;
    }

    return 0;
}

int remove_private_fifo() {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name(fifo);
    return unlink(fifo);
}

int open_private_fifo() {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name(fifo);

    int fd;
    while ((fd = open(fifo, O_RDONLY)) < 0) {
    }

    return fd;
}

int open_public_fifo() {
    int fd;
    while ((fd = open(get_fifoname(), O_WRONLY)) < 0) {
    }

    return fd;
}

int close_fifo(int fd) {
    return close(fd);
}