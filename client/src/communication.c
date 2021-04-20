#include "../include/communication.h"

#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"

int build_message(message_t* msg, int id, int res, int t) {
    msg->i = id;
    msg->pid = getpid();
    msg->res = res;
    msg->t = t;
    msg->tid = pthread_self();
    return 0;
}

int send_private_message(message_t* msg) {
    int fd = open_private_fifo();
    return send_message(fd, msg);
}

int send_message(int fd, message_t* msg) {
    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    while (write(fd, msg, sizeof(message_t)) < 0) {
    }

    return close_private_fifo(fd);
}

int recv_private_message(message_t* msg) {
    int fd = open_private_fifo();
    return recv_message(fd, msg);
}

int recv_message(int fd, message_t* msg) {
    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    read(fd, msg, sizeof(message_t));
    return close_private_fifo(fd);
}
