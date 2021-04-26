#include "../include/communication.h"

#include <string.h>
#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"

int server_open = 0;

int is_server_open() {
    return server_open;
}

int set_server_open(int open) {
    server_open = open;
    return 0;
}

int build_message(message_t* msg, int id, int res, int t) {
    memset(msg, 0, sizeof(message_t));

    msg->i = id;
    msg->pid = getpid();
    msg->res = res;
    msg->t = t;
    msg->tid = pthread_self();
    return 0;
}

int send_public_message(message_t* msg) {
    // int fd = open_write_public_fifo();

    int fd = get_public_fifo();

    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    while (write(fd, msg, sizeof(message_t)) < 0) {
    }

    return 0;
}

int recv_private_message(message_t* msg) {
    //memset(msg, 0, sizeof(message_t));
    int fd = open_read_private_fifo();
    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    size_t data_size = read(fd, msg, sizeof(message_t));
    int err;
    if ((err = close_fifo(fd)) != 0)
        return err;

    return sizeof(message_t) == data_size ? 0 : ERROR;
}
