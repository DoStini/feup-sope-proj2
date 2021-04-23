#include "../include/communication.h"

#include <string.h>
#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"

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
    int fd = open_write_public_fifo();
    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    while (write(fd, msg, sizeof(message_t)) < 0) {
    }

    return close_fifo(fd);
}

int recv_private_message(message_t* msg) {
    printf("trying to receive\n");
    int fd = open_read_private_fifo();
    if (fd < 0) {
        return CANT_OPEN_FIFO;
    }

    read(fd, msg, sizeof(message_t));
    return close_fifo(fd);
}
