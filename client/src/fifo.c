#include "../include/fifo.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"
#include "../include/task_creator.h"

int get_fifo_name(char* res) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();

    return snprintf(res, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, tid);
}

int wait_public_fifo() {
    int fd;
    while ((fd = open(get_public_fifoname(), O_RDWR)) < 0) {
        if (is_timeout()) {
            return ERROR;
        }
    }
    close(fd);
    return 0;
}

int get_fifo_name_by_thread(char* res, pthread_t thrd) {
    pid_t pid = getpid();

    return snprintf(res, MAX_FIFO_NAME, "/tmp/%d.%lu", pid, thrd);
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

int cleanup_private_fifo(pthread_t thread) {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name_by_thread(fifo, thread);
    return unlink(fifo);
}

int remove_private_fifo() {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name(fifo);
    return unlink(fifo);
}

int open_read_private_fifo() {
    char fifo[MAX_FIFO_NAME] = "";
    get_fifo_name(fifo);
    int fd;

    while ((fd = open(get_public_fifoname(), O_RDONLY | O_NONBLOCK)) < 0 &&
           errno == ENXIO) {
        if (is_timeout()) {
            return ERROR;
        }
    }

    return fd;
}

int open_write_public_fifo() {
    int fd;

    while ((fd = open(get_public_fifoname(), O_WRONLY | O_NONBLOCK)) < 0 &&
           errno == ENXIO) {
        if (is_timeout()) {
            return ERROR;
        }
    }
    return fd;
}

int close_fifo(int fd) {
    return close(fd);
}