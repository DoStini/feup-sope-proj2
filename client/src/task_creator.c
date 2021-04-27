#include "../include/task_creator.h"

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/block_array.h"
#include "../include/timer.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))
#define MAX_WAIT_MSEC 250
#define MIN_WAIT_MSEC 50

static unsigned int seedp;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return MSEC_TO_NSEC(rand_r(&seedp) % (upper - lower) + lower);
}

void* create_receive_task() {
    sleep(rand_r(&seedp) % 2);
    printf("%ld says hi and goodbye.\n", pthread_self());

    // create random task, private fifos, send message through public fifo,
    // receive msg, be happy.

    return NULL;
}

int task_creator() {
    struct timespec tspec;
    pthread_t thread;
    tspec.tv_sec = 0;
    size_t threads_size = 0;

    block_array_t* threads = block_array_create(10);
    if (threads == NULL) return TASK_CREATOR_ERROR;

    while (true) {
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

    block_array_delete(threads);

    return 0;
}
