#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/args_parser.h"
#include "../include/communication.h"
#include "../include/error/exit_codes.h"
#include "../include/task_creator.h"
#include "../include/fifo.h"
#include "../include/logger.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;

    srand((unsigned) time(NULL));

    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }

    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);

    open_log();
    info_t info = {1, 1};
    write_log(IWANT, &info);

    
    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);
    if (create_private_fifo()) {
        return CANT_CREATE_FIFO;
    }
  
    task_creator(&data);
  
    return remove_private_fifo();
}
