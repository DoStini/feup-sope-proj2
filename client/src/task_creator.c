#include "../include/task_creator.h"

#include <sys/types.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include "../include/block_array.h"

#define MS_TO_NS 10e6
#define MAX_WAIT_MS 100
#define MIN_WAIT_MS 10

static unsigned int seedp;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return (rand_r(&seedp) % (upper - lower) + lower) * MS_TO_NS;
}

int __tmp__do_nothing() {
    sleep(rand_r(&seedp) % 2);
    return 0;
}

int create_task() { return 0; }

int task_creator(const args_data_t* const data) {
    struct timespec tspec;
    tspec.tv_sec = 0;

    int __tmp__tries = 0;

    block_array_t* threads = block_array_create(THREAD_VAL, 10);

    while (__tmp__tries < 10) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MS, MAX_WAIT_MS);
        nanosleep(&tspec, NULL);

        // if(pthread_create())

        __tmp__tries++;
    }

    block_array_delete(threads);

    return 0;
}