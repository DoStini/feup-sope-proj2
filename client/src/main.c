#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/args_parser.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/fifo.h"
#include "../include/logger.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;
    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }
    open_log();
    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);
    if (create_private_fifo()) {
        return CANT_CREATE_FIFO;
    }
    return remove_private_fifo();
}
