#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"
#include "../include/task_creator.h"
#include "../include/logger.h"
#include "../include/timer.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned)time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }

    if (start_timer(data.duration)) {
        return ERROR;
    }

    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);

    open_log();
    info_t info = {1, 1};
    write_log(IWANT, &info);

    task_creator();
}
