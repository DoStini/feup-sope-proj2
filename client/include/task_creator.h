#ifndef CLIENT_INCLUDE_TASK_CREATOR_H_
#define CLIENT_INCLUDE_TASK_CREATOR_H_

#define TASK_CREATOR_ERROR -1
#define TASK_CREATOR_THREAD_ERROR -1

#include "../include/args_parser.h"

int task_creator(const args_data_t* const data);

#endif  // CLIENT_INCLUDE_TASK_CREATOR_H_