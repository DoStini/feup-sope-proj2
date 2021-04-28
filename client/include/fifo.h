#ifndef CLIENT_INCLUDE_FIFO_H_
#define CLIENT_INCLUDE_FIFO_H_

#include <pthread.h>
#include <stdio.h>

#define MAX_FIFO_NAME FILENAME_MAX
#define TIMEOUT 5

int create_private_fifo(void);

int remove_private_fifo(void);

int open_read_private_fifo(void);

int set_public_fifo(int fd);

int get_public_fifo();

int wait_public_fifo();

int close_fifo(int fd);

#endif  // CLIENT_INCLUDE_FIFO_H_
