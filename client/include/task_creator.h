#ifndef CLIENT_INCLUDE_TASK_CREATOR_H_
#define CLIENT_INCLUDE_TASK_CREATOR_H_

#define TASK_CREATOR_ERROR -1
#define TASK_CREATOR_THREAD_ERROR -1

#include <stdbool.h>

#include "../include/args_parser.h"

/**
 * @brief Creates threads in random intervals of time that generate a task for
 *the server and wait for the server's response, before the time limit is
 *reached.
 *
 * @param[in] data the arguments given to the client.
 *
 * @return an error value.
 **/
int task_creator(const args_data_t* const data);

/**
 * @brief Indicates if the client has passed the timeout
 *
 * @return true if timed out, false otherwise
 */
bool is_timeout();

#endif  // CLIENT_INCLUDE_TASK_CREATOR_H_
