#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"
#include "../include/task_creator.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned) time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }
    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);

    task_creator(&data);
}
