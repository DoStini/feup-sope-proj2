#include "../include/task_handler.h"

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"
#include "../include/queue.h"
#include "../include/timer.h"
#include "../lib/lib.h"

#define MSEC_TO_NSEC(x) ((x) * (1e6))

static unsigned int seedp;

static queue_t* data_queue = NULL;

static pthread_mutex_t mutex;
static pthread_mutexattr_t mattr;

static sem_t recv_sem;
static sem_t send_sem;

uint64_t get_random_ms(uint64_t lower, uint64_t upper) {
    return MSEC_TO_NSEC(rand_r(&seedp) % (upper - lower) + lower);
}

int get_random_task() { return rand_r(&seedp) % 9 + 1; }

int init_sync(int sem_size) {
    if (pthread_mutexattr_init(&mattr))
        return ERROR;
    if (pthread_mutex_init(&mutex, &mattr))
        return ERROR;
    if (sem_init(&recv_sem, 0, sem_size))
        return ERROR;
    if (sem_init(&send_sem, 0, sem_size))
        return ERROR;
    return 0;
}

int free_sync() {
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&mattr);
    sem_destroy(&recv_sem);
    sem_destroy(&send_sem);
    return 0;
}

void* cleanup_thread() {
    pthread_exit(NULL);
    return NULL;
}

void cleanup(void) {
    close_fifo(get_public_fifo());
    int err = remove_public_fifo();
    fprintf(stderr, "UNLINK: %d\n", err);
    free_sync();
    if (data_queue != NULL) queue_destroy(data_queue);
}

void* producer_handler(void* ptr) {
    message_t msg = *((message_t*)ptr);
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

    sem_wait(&recv_sem);

    pthread_mutex_lock(&mutex);

    if (data_queue != NULL)
        queue_push(data_queue, &msg);

    pthread_mutex_unlock(&mutex);

    return cleanup_thread();
}

void* consumer_handler() {
    while (1) {
        if (is_timeout() && queue_empty(data_queue))
            break;

        message_t msg;

        if (queue_empty(data_queue))
            continue;

        pthread_mutex_lock(&mutex);
        queue_front(data_queue, &msg);
        queue_pop(data_queue);
        pthread_mutex_unlock(&mutex);
        sem_post(&recv_sem);

        write_log(IWANT, &msg);
        if (send_private_message(&msg, msg.pid, msg.tid)) {
            write_log(FAILD, &msg);
        } else if (msg.tskres == -1) {
            write_log(TLATE, &msg);
        } else {
            write_log(TSKDN, &msg);
        }
    }

    err_log("terminate consumer");

    return cleanup_thread();
}

int task_handler(args_data_t* args) {
    if (create_public_fifo() != 0) return CANT_CREATE_FIFO;
    atexit(cleanup);

    int fd = open_read_public_fifo();

    if (fd < 0) return ERROR;

    pthread_t consumer_thread;

    if (pthread_create(&consumer_thread, NULL, consumer_handler, NULL)) {
        return TASK_CREATOR_THREAD_ERROR;
    }

    if (init_sync(args->buffer_size)) {
        return ERROR;
    }

    data_queue = queue_(args->buffer_size);

    while (!is_timeout()) {
        pthread_t producer_thread;
        message_t* msg = malloc(sizeof(message_t));
        if (recv_message(msg) == 0) {
            if (pthread_create(&producer_thread, NULL, producer_handler, msg)) {
                free(msg);
                queue_destroy(data_queue);
                return TASK_CREATOR_THREAD_ERROR;
            }
        } else {
            usleep(5);
            free(msg);
        }
    }

    pthread_join(consumer_thread, NULL);

    return 0;
}
