#ifndef CLIENT_INCLUDE_FIFO_H_
#define CLIENT_INCLUDE_FIFO_H_

#include <stdio.h>

#define MAX_FIFO_NAME FILENAME_MAX

int create_private_fifo();

int remove_private_fifo();

int open_private_fifo();

int close_private_fifo(int fd);

#endif  // CLIENT_INCLUDE_FIFO_H_
