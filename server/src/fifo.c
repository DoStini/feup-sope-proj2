#include "include/fifo.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#include "include/args_parser.h"
#include "include/error/exit_codes.h"

#define BUSY_WAIT_US 10

static int public_fifo;

int set_public_fifo(int fd) {
    public_fifo = fd;
    return 0;
}

int get_public_fifo() { return public_fifo; }

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
