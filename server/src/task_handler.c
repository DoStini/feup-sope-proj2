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
#include "../lib/lib.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))

static unsigned int seedp;

static message_t queue[1000];
static size_t curr_idx = 0;

static pthread_mutex_t mutex;

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
    // Write here so that the main thread doesn't waste time

    err_log("received task");
    int res = task(msg.tskload);
    if (is_timeout()) {
        err_log("task timedout");
        msg.tskres = -1;
        return cleanup_thread();
    } else {
        msg.tskres = res;
        write_log(TSKEX, &msg);
    }

    err_log("mutex queue lock");
    pthread_mutex_lock(&mutex);

    queue[curr_idx++] = msg;

    pthread_mutex_unlock(&mutex);
    err_log("mutex queue unlock");

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

    pthread_mutexattr_t mattr;

    pthread_mutexattr_init(&mattr);
    pthread_mutex_init(&mutex, &mattr);

    while (!is_timeout()) {
        pthread_t consumer;
        message_t *msg = malloc(sizeof(message_t));
        if (recv_message(msg) == 0) {
            if (pthread_create(&consumer, NULL, producer_handler, msg)) {
                free(msg);
                return TASK_CREATOR_THREAD_ERROR;
            }
        } else {
            usleep(5);
            free(msg);
        }
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&mattr);

    for (size_t i = 0; i <= curr_idx; i++) {
        message_t msg = queue[i];
        printf("val: %d - %d\n", msg.tskload, msg.tskres);
    }

    return 0;
}
