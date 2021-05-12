#ifndef CLIENT_INCLUDE_TASK_CREATOR_H_
#define CLIENT_INCLUDE_TASK_CREATOR_H_

#define TASK_CREATOR_ERROR -1
#define TASK_CREATOR_THREAD_ERROR -2

#include <stdbool.h>

#include "../include/args_parser.h"

/**
 * @brief Handles the threads.
 *
 * @return an error value.
 **/
int task_handler(void);

/**
 * @brief Indicates if the client has passed the timeout
 *
 * @return true if timed out, false otherwise
 */
bool is_timeout();

#endif  // CLIENT_INCLUDE_TASK_CREATOR_H_
