#include "../include/task_handler.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"
#include "../include/timer.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))
#define MAX_WAIT_MSEC 50
#define MIN_WAIT_MSEC 10

static unsigned int seedp;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return MSEC_TO_NSEC(rand_r(&seedp) % (upper - lower) + lower);
}

int get_random_task() { return rand_r(&seedp) % 9 + 1; }

void cleanup_thread() {
    pthread_exit(NULL);
}

void cleanup(void) {
    close_fifo(get_public_fifo());
    remove_public_fifo();
}

int task_handler() {
    if (create_public_fifo() != 0)
        return CANT_CREATE_FIFO;
    atexit(cleanup);

    int fd = open_read_public_fifo();

    if (fd < 0)
        return ERROR;

    while (!is_timeout()) {
        message_t msg;
        recv_message(&msg);
        write_log(RECVD, &msg);
    }

    return 0;
}
