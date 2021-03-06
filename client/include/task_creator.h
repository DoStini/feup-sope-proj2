#ifndef CLIENT_INCLUDE_TASK_CREATOR_H_
#define CLIENT_INCLUDE_TASK_CREATOR_H_

#define TASK_CREATOR_ERROR -1
#define TASK_CREATOR_THREAD_ERROR -2

#include <stdbool.h>

#include "../include/args_parser.h"

/**
 * @brief Creates threads in random intervals of time that generate a task for
 *the server and wait for the server's response, before the time limit is
 *reached.
 *
 * @return an error value.
 **/
int task_creator(void);

/**
 * @brief Indicates if the client has passed the timeout
 *
 * @return true if timed out, false otherwise
 */
bool is_timeout();

#endif  // CLIENT_INCLUDE_TASK_CREATOR_H_
