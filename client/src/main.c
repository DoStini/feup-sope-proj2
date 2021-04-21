#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../include/args_parser.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"
#include "../include/task_creator.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned)time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }

    open_log();
    int err;
    if ((err = task_creator(&data)) != 0)
        return err;

    return 0;
}
