#ifndef CLIENT_INCLUDE_FIFO_H_
#define CLIENT_INCLUDE_FIFO_H_

#include <stdio.h>

#define MAX_FIFO_NAME FILENAME_MAX
#define TIMEOUT 5

int create_private_fifo(void);

int remove_private_fifo(void);

int open_read_private_fifo(void);

int open_write_public_fifo(void);

int close_fifo(int fd);

#endif  // CLIENT_INCLUDE_FIFO_H_
