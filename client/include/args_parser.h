#ifndef CLIENT_INCLUDE_ARGS_PARSER_H_
#define CLIENT_INCLUDE_ARGS_PARSER_H_

#include <stdint.h>

#define USAGE "USAGE: c <-t nsecs> <fifoname>"

#define PARSE_ERROR -1

typedef struct args_data {
    uint64_t duration;
    char* fifoname;
} args_data_t;

int parse_args(int argc, char* const argv[], args_data_t* const data);

char* get_public_fifoname(void);

#endif  // CLIENT_INCLUDE_ARGS_PARSER_H_
