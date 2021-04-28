#include "../include/task_creator.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../include/block_array.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"
#include "../include/timer.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))
#define MAX_WAIT_MSEC 50
#define MIN_WAIT_MSEC 10

static unsigned int seedp;
static int counter = 0;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return MSEC_TO_NSEC(rand_r(&seedp) % (upper - lower) + lower);
}

int get_random_task() {
    return rand_r(&seedp) % 9 + 1;
}

void* create_receive_task() {
    message_t msg;

    if (create_private_fifo() != 0) {
        build_message(&msg, -1, -1, -1);
        return NULL;
    }

    build_message(&msg, counter, -1, get_random_task());

    if (send_public_message(&msg) != 0) {
        remove_private_fifo();
        return NULL;
    }

    write_log(IWANT, &msg);

    if (recv_private_message(&msg) != 0) {
        write_log(GAVUP, &msg);
        remove_private_fifo();
        return NULL;
    }

    if (msg.res == -1) {
        write_log(CLOSD, &msg);
        set_server_open(false);
        remove_private_fifo();
        return NULL;
    }

    write_log(GOTRS, &msg);
    remove_private_fifo();

    return NULL;
}

int task_creator() {
    struct timespec tspec;
    pthread_t thread;
    tspec.tv_sec = 0;
    size_t threads_size = 0;

    block_array_t* threads = block_array_create(10);
    if (threads == NULL) return TASK_CREATOR_ERROR;

    if (wait_public_fifo() != 0) {
        return ERROR;
    }

    while (is_server_open()) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MSEC, MAX_WAIT_MSEC);
        nanosleep(&tspec, NULL);

        if (is_timeout()) break;

        if (pthread_create(&thread, NULL, create_receive_task, NULL)) {
            block_array_delete(threads);
            return TASK_CREATOR_THREAD_ERROR;
        }
        block_array_set(threads, threads_size, thread);

        threads_size++;
    }

    for (size_t i = 0; i < threads_size; i++) {
        if (block_array_at(threads, i, &thread)) {
            block_array_delete(threads);
            return TASK_CREATOR_ERROR;
        }

        pthread_join(thread, NULL);
    }

    close_fifo(get_public_fifo());

    block_array_delete(threads);

    return 0;
}
