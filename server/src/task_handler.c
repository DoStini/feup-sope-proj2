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

void *cleanup_thread() {
    pthread_exit(NULL);
    return NULL;
}

void cleanup(void) {
    close_fifo(get_public_fifo());
    remove_public_fifo();
}

void *producer_handler(void *ptr) {
    message_t msg = *((message_t *)ptr);
    free(ptr);
    write_log(RECVD, &msg);
    return cleanup_thread();
}

void *consumer_handler() {
    return cleanup_thread();
}

int task_handler() {
    if (create_public_fifo() != 0)
        return CANT_CREATE_FIFO;
    atexit(cleanup);

    int fd = open_read_public_fifo();

    if (fd < 0)
        return ERROR;

    pthread_t consumer_thread;

    if (pthread_create(&consumer_thread, NULL, consumer_handler, NULL)) {
        return TASK_CREATOR_THREAD_ERROR;
    }

    while (!is_timeout()) {
        pthread_t consumer;
        message_t *msg = (message_t *)malloc(sizeof(sizeof(message_t)));
        if (recv_message(msg) == 0) {
            if (pthread_create(&consumer, NULL, producer_handler, (void *)msg)) {
                free(msg);
                return TASK_CREATOR_THREAD_ERROR;
            }
        } else {
            usleep(5);
            free(msg);
        }
    }

    return 0;
}