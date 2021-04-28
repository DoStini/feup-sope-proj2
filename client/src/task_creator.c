#include "../include/task_creator.h"

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "../include/block_array.h"
#include "../include/timer.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))
#define MAX_WAIT_MSEC 25
#define MIN_WAIT_MSEC 5

static unsigned int seedp;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return MSEC_TO_NSEC(rand_r(&seedp) % (upper - lower) + lower);
}

void* create_receive_task() {
    sleep(rand_r(&seedp) % 8);
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

    while (true) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MSEC, MAX_WAIT_MSEC);
        nanosleep(&tspec, NULL);

        if (is_timeout()) break;

        if (pthread_create(&thread, NULL, create_receive_task, NULL)) {
            return TASK_CREATOR_THREAD_ERROR;
        }
        pthread_detach(thread);

        threads_size++;
    }

    return 0;
}
