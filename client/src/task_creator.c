#include "../include/task_creator.h"

#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "../include/block_array.h"

#define MS_TO_NS 10e6
#define MAX_WAIT_MS 100
#define MIN_WAIT_MS 10

static unsigned int seedp;
static timer_t timer;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return (rand_r(&seedp) % (upper - lower) + lower) * MS_TO_NS;
}

int create_task() { return 0; }

void* __tmp__do_nothing() {
    sleep(rand_r(&seedp) % 2);
    printf("%ld says hi and goodbye.\n", pthread_self());

    create_task();

    return NULL;
}

int start_timer(uint64_t seconds) {
    struct sigevent sevp;
    struct itimerspec spec;
    struct timespec timer_interval;
    struct timespec timer_value;

    timer_value.tv_nsec = 0;
    timer_value.tv_sec = seconds;
    timer_interval.tv_sec = timer_interval.tv_nsec = 0;

    memset(&sevp, 0, sizeof(sevp));
    sevp.sigev_notify = SIGEV_NONE;

    spec.it_interval = timer_interval;
    spec.it_value = timer_value;

    if (timer_create(CLOCK_REALTIME, &sevp, &timer)) return -1;
    return timer_settime(timer, 0, &spec, NULL);
}

bool is_timeout() {
    struct itimerspec timer_value;
    timer_gettime(timer, &timer_value);

    return timer_value.it_value.tv_nsec == 0 &&
           timer_value.it_value.tv_sec == 0;
}

int task_creator(const args_data_t* const data) {
    struct timespec tspec;
    array_value_t thread;
    tspec.tv_sec = 0;
    size_t threads_size = 0;

    block_array_t* threads = block_array_create(THREAD_VAL, 10);
    if (threads == NULL) return TASK_CREATOR_ERROR;

    if (start_timer(data->duration)) return TASK_CREATOR_ERROR;

    while (true) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MS, MAX_WAIT_MS);
        nanosleep(&tspec, NULL);

        if (is_timeout()) break;

        if (pthread_create(&thread.thread_value, NULL, __tmp__do_nothing,
                           NULL)) {
            return TASK_CREATOR_THREAD_ERROR;
        }
        block_array_set(threads, threads_size, thread);

        threads_size++;
    }

    for (size_t i = 0; i < threads_size; i++) {
        if (block_array_at(threads, i, &thread)) return TASK_CREATOR_ERROR;
        pthread_join(thread.thread_value, NULL);
    }

    block_array_delete(threads);

    return 0;
}
