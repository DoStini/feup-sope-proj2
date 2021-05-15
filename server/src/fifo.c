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
#include "../include/task_handler.h"
#include "../include/timer.h"

#define BUSY_WAIT_US 10

static int public_fifo;

int set_public_fifo(int fd) {
    public_fifo = fd;
    return 0;
}

int get_public_fifo() { return public_fifo; }

int get_fifo_name(char* res) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    return snprintf(res, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, tid);
}

int wait_public_fifo() {
    int fd;
    while ((fd = open(get_public_fifoname(), O_WRONLY | O_NONBLOCK)) < 0) {
        usleep(BUSY_WAIT_US);
        if (is_timeout()) {
            return ERROR;
        }
    }

    set_public_fifo(fd);
    return 0;
}

int create_public_fifo() {
    if (mkfifo(get_public_fifoname(), 0777) && errno != EEXIST) {
        perror("create fifo");
        return CANT_CREATE_FIFO;
    }

    return 0;
}

int remove_public_fifo() {
    return unlink(get_public_fifoname());
}

int open_read_public_fifo() {
    int fd = open(get_public_fifoname(), O_RDWR);
    if (fd < 0)
        return ERROR;
    set_public_fifo(fd);
    return 0;
}

int close_fifo(int fd) { return close(fd); }