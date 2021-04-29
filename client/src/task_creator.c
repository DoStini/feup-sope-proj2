#include "../include/task_creator.h"

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
    remove_private_fifo();
    pthread_exit(NULL);
}

void* create_receive_task(void* thread_id) {
    int id = *(int*)thread_id;
    free(thread_id);

    message_t msg;

    if (create_private_fifo() != 0) {
        build_message(&msg, -1, -1, -1);
        cleanup_thread();
    }

    build_message(&msg, id, -1, get_random_task());

    if (send_public_message(&msg) != 0) {
        cleanup_thread();
    }

    write_log(IWANT, &msg);

    if (recv_private_message(&msg) != 0) {
        write_log(GAVUP, &msg);
        cleanup_thread();
    }

    if (msg.tskres == -1) {
        write_log(CLOSD, &msg);
        set_server_open(false);
        cleanup_thread();
    }

    write_log(GOTRS, &msg);
    cleanup_thread();
    return NULL;
}

void cleanup(void) {
    close_fifo(get_public_fifo());
}

int task_creator() {
    struct timespec tspec;
    pthread_t thread;
    tspec.tv_sec = 0;
    size_t threads_size = 0;

    if (wait_public_fifo() != 0) {
        return ERROR;
    }
    atexit(cleanup);

    int id = 1;

    while (is_server_open()) {
        tspec.tv_nsec = get_random_ms(MIN_WAIT_MSEC, MAX_WAIT_MSEC);
        nanosleep(&tspec, NULL);

        if (is_timeout()) break;

        int* thread_id = malloc(sizeof(int));
        if (thread_id == NULL) return TASK_CREATOR_ERROR;

        *thread_id = id++;

        if (pthread_create(&thread, NULL, create_receive_task,
                           (void*)thread_id)) {
            return TASK_CREATOR_THREAD_ERROR;
        }
        pthread_detach(thread);

        threads_size++;
    }

    return 0;
}
