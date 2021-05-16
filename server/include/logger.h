#ifndef SERVER_INCLUDE_LOGGER_H_
#define SERVER_INCLUDE_LOGGER_H_

#include <stdbool.h>

#include "../include/communication.h"

#define LOG_PATH "client.log"

/**
 * @brief Contains all possible responses from either client and server for
 * proper communication identification
 * 
 */
enum Event { IWANT = 0,
             RECVD,
             TSKEX,
             TSKDN,
             GOTRS,
             TLATE,
             CLOSD,
             GAVUP,
             FAILD };

typedef struct info {
    int id;
    int t;
    int res;
} info_t;

/**
 * @brief Opens the log file, if one is given, and gets its file descriptor
 *number.
 **/
int open_log(void);

/**
 * @brief Writes into the log with the predefined format.
 *
 * @param event event enum specifying the event being logged.
 * @param[in] info string containing information about the event.
 *
 * @return an error value.
 **/
int write_log(enum Event event, message_t* info);

/**
 * Writes to stderr
 *
 * @param [in] msg String to write
 */
int err_log(const char* msg);

#endif  // SERVER_INCLUDE_LOGGER_H_
