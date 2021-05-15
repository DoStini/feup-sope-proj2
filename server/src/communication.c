#include "../include/communication.h"

#include <string.h>
#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/timer.h"

int build_message(message_t* msg, int id, int res, int t) {
    memset(msg, 0, sizeof(message_t));

    msg->rid = id;
    msg->pid = getpid();
    msg->tskres = res;
    msg->tskload = t;
    msg->tid = pthread_self();
    return 0;
}

int recv_message(message_t* msg) {
    int fd = get_public_fifo();
    fd_set fds;
    struct timeval timer;
    timer_get_remaining_timeval(&timer);

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    int err;
    err = select(fd + 1, &fds, NULL, NULL, &timer);

    if (err == -1) {
        close(fd);
        return ERROR;
        perror("select()");
    } else if (err) {
        size_t data_size = read(fd, msg, sizeof(message_t));

        return sizeof(message_t) == data_size ? 0 : ERROR;
    }
    return ERROR;
}
