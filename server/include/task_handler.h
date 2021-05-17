#ifndef SERVER_INCLUDE_TASK_HANDLER_H_
#define SERVER_INCLUDE_TASK_HANDLER_H_

#define TASK_CREATOR_ERROR -1
#define TASK_CREATOR_THREAD_ERROR -2

#include <stdbool.h>

#include "../include/args_parser.h"

/**
 * @brief Handles the threads.
 * 
 * @param [in] data Argv parsed
 * @return an error value.
 **/
int task_handler(args_data_t *args);
/**
 * @brief Indicates if the client has passed the timeout
 *
 * @return true if timed out, false otherwise
 */
bool is_timeout();

#endif  // SERVER_INCLUDE_TASK_HANDLER_H_
