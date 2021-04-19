#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/args_parser.h"
#include "../include/error/exit_codes.h"
#include "../include/logger.h"

int main(int argc, char* argv[], char* envp[]) {
    args_data_t data;
    if (parse_args(argc, argv, &data)) {
        fprintf(stderr, "%s\n", USAGE);
        exit(BAD_ARGS);
    }
    open_log();
    info_t info = {1, 1};
    write_log(IWANT, &info);
}
