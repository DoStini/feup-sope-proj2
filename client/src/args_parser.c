#include "../include/args_parser.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int parse_args(int argc, char* const argv[], args_data_t* const data) {
    if (argc != 4) {
        return ERROR;
    }

    for (size_t i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-t")) {
            if (i == argc - 1) return ERROR;

            int64_t time;
            if ((time = atoll(argv[i + 1])) <= 0) return ERROR;
            data->duration = time;

            i++;
            continue;
        }

        data->fifoname = argv[i];
    }

    return 0;
}
