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
#include "../include/fifo.h"
#include "../include/logger.h"

#define MS_TO_NS 10e6
#define MAX_WAIT_MS 100
#define MIN_WAIT_MS 10

static unsigned int seedp;
static timer_t timer;
static int counter = 0;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return (rand_r(&seedp) % (upper - lower) + lower) * MS_TO_NS;
}

int get_random_task() {
    return rand_r(&seedp) % 9 + 1;
}

void* create_receive_task() {
    sleep(rand_r(&seedp) % 2);
    message_t msg;

    if (create_private_fifo() != 0) {
        build_message(&msg, -1, -1, -1);
        write_log(FAILD, &msg);
    }

    build_message(&msg, counter, -1, get_random_task());

    if (send_public_message(&msg) != 0)
        return NULL;

    write_log(IWANT, &msg);

    if (recv_private_message(&msg) != 0) {
        write_log(GAVUP, &msg);
        return NULL;
    }

    write_log(RECVD, &msg);

    // create random task, private fifos, send message through public fifo,
    // receive msg, be happy.

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

    if (start_timer(data->duration)) {
        block_array_delete(threads);
        return TASK_CREATOR_ERROR;
    }

    while (true) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MS, MAX_WAIT_MS);
        nanosleep(&tspec, NULL);

        if (is_timeout()) break;

        if (pthread_create(&thread.thread_value, NULL, create_receive_task,
                           NULL)) {
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
        printf("Cleanup result: %d\n", cleanup_private_fifo(thread.thread_value));
        pthread_join(thread.thread_value, NULL);
    }

    block_array_delete(threads);

    return 0;
}
