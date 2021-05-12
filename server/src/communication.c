#include "../include/communication.h"

#include <string.h>
#include <unistd.h>

#include "../include/error/exit_codes.h"
#include "../include/fifo.h"

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
    size_t data_size = read(get_public_fifo(), msg, sizeof(message_t));

    return sizeof(message_t) == data_size ? 0 : ERROR;
}
