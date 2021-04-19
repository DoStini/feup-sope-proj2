#include "../include/communication.h"

#include <unistd.h>

#include "../include/fifo.h"

int build_message(message_t* msg) {
    return 0;
}

int send_message(message_t* msg) {
    int fd = open_private_fifo();
    if (fd < 0) {
        return 2;
    }

    while (write(fd, "Hello", 6) < 0) {
    }

    return close_private_fifo(fd);
}
