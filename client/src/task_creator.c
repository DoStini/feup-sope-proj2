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

void* __tmp__do_nothing() {
    sleep(rand_r(&seedp) % 2);
    printf("%ld says hi and goodbye.\n", pthread_self());

    return NULL;
}

int create_task() { return 0; }

int task_creator(const args_data_t* const data) {
    struct timespec tspec;
    array_value_t thread;
    tspec.tv_sec = 0;
    int __tmp__tries = 0;
    size_t threads_size = 0;

    block_array_t* threads = block_array_create(THREAD_VAL, 10);
    if (threads == NULL) return TASK_CREATOR_ERROR;

    while (__tmp__tries < 10) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MS, MAX_WAIT_MS);
        nanosleep(&tspec, NULL);

        if (pthread_create(&thread.thread_value, NULL, __tmp__do_nothing,
                           NULL)) {
            return TASK_CREATOR_THREAD_ERROR;
        }
        block_array_set(threads, threads_size, thread);

        threads_size++;
        __tmp__tries++;
    }

    for (size_t i = 0; i < threads_size; i++) {
        if (block_array_at(threads, i, &thread)) return TASK_CREATOR_ERROR;
        pthread_join(thread.thread_value, NULL);
    }

    block_array_delete(threads);

    return 0;
}