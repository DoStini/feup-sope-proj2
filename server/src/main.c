#include <stdio.h>
#include <stdlib.h>

#include "include/args_parser.h"
#include "include/error/exit_codes.h"
#include "include/logger.h"
#include "include/task_handler.h"
#include "include/timer.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned)time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }

    if (timer_start(data.duration)) {
        return ERROR;
    }

    atexit(timer_cleanup);

    open_log();
    int err = task_handler(&data);

    pthread_exit(&err);
}
