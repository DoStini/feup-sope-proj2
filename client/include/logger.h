#ifndef CLIENT_INCLUDE_LOGGER_H_
#define CLIENT_INCLUDE_LOGGER_H_

#include <stdbool.h>

#define LOG_PATH "client.log"

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
int open_log();

/**
 * @brief Writes into the log with the predefined format.
 *
 * @param event event enum specifying the event being logged.
 * @param[in] info string containing information about the event.
 *
 * @return an error value.
 **/
int write_log(enum Event event, info_t* info);

#endif  // CLIENT_INCLUDE_LOGGER_H_
