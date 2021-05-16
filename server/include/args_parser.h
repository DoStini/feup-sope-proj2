#ifndef SERVER_INCLUDE_ARGS_PARSER_H_
#define SERVER_INCLUDE_ARGS_PARSER_H_

#include <stdint.h>
#include <sys/types.h>

#define USAGE "Usage: ./bin/s <-t nsecs> [-l bufsize] fifoname"

#define PARSE_ERROR -1

/**
 * @brief Command line arguments information
 * 
 */
typedef struct args_data {
    uint64_t duration;
    size_t buffer_size;
    char* fifoname;
} args_data_t;

/**
 * @brief Parses the command line arguments into the respective struct
 * 
 * @param argc the number of command line arguments
 * @param[in] argv the command line arguments array
 * @param[out] data the args struct to save the information on
 * @return int 0 upon success, other upon error
 */
int parse_args(int argc, char* const argv[], args_data_t* const data);

/**
 * @brief Get the public fifo name
 * 
 * @return char* the public fifo name
 */
char* get_public_fifoname(void);

#endif  // SERVER_INCLUDE_ARGS_PARSER_H_
