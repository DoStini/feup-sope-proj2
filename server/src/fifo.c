#include "../include/fifo.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/logger.h"
#include "../include/task_handler.h"
#include "../include/timer.h"

#define BUSY_WAIT_US 10

static int public_fifo;

int set_public_fifo(int fd) {
    public_fifo = fd;
    return 0;
}

int get_public_fifo() { return public_fifo; }

int open_write_private_fifo(pid_t pid, pthread_t tid) {
    char fifo[MAX_FIFO_NAME] = "";
    snprintf(fifo, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, tid);
    fprintf(stderr, "[server] opened %s\n", fifo);
    int fd = open(fifo, O_RDWR);
    return fd;
    if (fd < 0) {
        perror("private fifo");
        return ERROR;
    }
    fprintf(stderr, "open fd: %d\n", fd);
    fd_set fds;
    struct timeval timer;
    timer_get_remaining_timeval(&timer);

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    int err;
    err = select(fd + 1, NULL, &fds, NULL, &timer);

    if (err == -1) {
        close(fd);
        perror("select()");
        return ERROR;
    } else if (err) {
        return fd;
    }
    close(fd);
    return ERROR;
}

int create_public_fifo() {
    if (mkfifo(get_public_fifoname(), 0777) && errno != EEXIST) {
        perror("create fifo");
        return CANT_CREATE_FIFO;
    }

    return 0;
}

int remove_public_fifo() { return unlink(get_public_fifoname()); }

int open_read_public_fifo() {
    int fd = open(get_public_fifoname(), O_RDWR);
    if (fd < 0) return ERROR;
    set_public_fifo(fd);
    return 0;
}

int close_fifo(int fd) { return close(fd); }
