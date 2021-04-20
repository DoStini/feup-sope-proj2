#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);
    open_log();
    printf("Duration: %lu\nFifoname: %s\n", data.duration, data.fifoname);

    if (create_private_fifo()) {
        return CANT_CREATE_FIFO;
    }

    message_t rcv;

    build_message(&rcv, 1, 2, 5);

    send_message(&rcv);

    printf("id = %d, pid = %d, res = %d, t = %d, tid = %ld\n",
           rcv.i, rcv.pid, rcv.res, rcv.t, rcv.tid);

    sleep(1);

    recv_message(&rcv);

    printf("id = %d, pid = %d, res = %d, t = %d, tid = %ld\n",
           rcv.i, rcv.pid, rcv.res, rcv.t, rcv.tid);

    return remove_private_fifo();
}
