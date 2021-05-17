#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"
#include "../include/task_handler.h"
#include "../include/timer.h"
#include "../include/queue.h"
#include "../include/communication.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned)time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }

    queue_t* queue = queue_(5);
    queue_print(queue);
    message_t* message = malloc(sizeof(message_t));
    printf("front return: %d\n", queue_front(queue, message));

    build_message(message, 0, -1, 2);

    queue_push(queue, message);
    printf("front return: %d\n", queue_front(queue, message));
    printf("message pointer: %p\n", message);

    queue_print(queue);

    queue_push(queue, message);
    printf("front return: %d\n", queue_front(queue, message));
    printf("message pointer: %p\n", message);

    queue_print(queue);

    queue_push(queue, message);
    queue_push(queue, message);
    printf("push return: %d\n", queue_push(queue, message));

    queue_print(queue);

    printf("push return: %d\n", queue_push(queue, message));
    queue_print(queue);
    printf("front return: %d\n", queue_front(queue, message));
    printf("message pointer: %p\n", message);

    queue_destroy(queue);

    return 0;

    if (timer_start(data.duration)) {
        return ERROR;
    }

    atexit(timer_cleanup);

    open_log();
    int err = task_handler();

    pthread_exit(&err);
}
