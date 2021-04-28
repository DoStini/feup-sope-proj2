#include "../include/args_parser.h"

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static char* fifoname;

int parse_args(int argc, char* const argv[], args_data_t* const data) {
    if (argc != 4) {
        return PARSE_ERROR;
    }
    bool fifo_set = false;
    bool time_set = false;
    memset(data, 0, sizeof(args_data_t));

    for (size_t i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (time_set || i == argc - 1) return PARSE_ERROR;

            int64_t time;
            if ((time = atoll(argv[i + 1])) <= 0) return PARSE_ERROR;
            data->duration = time;

            i++;
            time_set = true;
        } else if (!fifo_set) {
            data->fifoname = argv[i];
            fifo_set = true;
        } else {
            return PARSE_ERROR;
        }
    }

    fifoname = data->fifoname;

    return 0;
}

char* get_public_fifoname() {
    return fifoname;
}
