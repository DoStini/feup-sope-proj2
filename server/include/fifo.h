#ifndef CLIENT_INCLUDE_FIFO_H_
#define CLIENT_INCLUDE_FIFO_H_

#include <pthread.h>
#include <stdio.h>

#define MAX_FIFO_NAME FILENAME_MAX
#define TIMEOUT 5

/**
 * @brief Create the thread private fifo
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int create_public_fifo(void);

/**
 * @brief Deletes the thread private fifo
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int remove_public_fifo(void);

/**
 * @brief Opens the private fifo for writing
 * 
 * @param [in] pid identifies the process id
 * @param [in] tid identifies the thread id
 * @return int 0 when closed, other when open (file descriptor)
 */
int open_write_private_fifo(pid_t pid, pthread_t tid);

/**
 * @brief Opens the public fifo for reading
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int open_read_public_fifo();

/**
 * @brief Gets the public fifo fd
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int get_public_fifo();

/**
 * @brief Closes a fifo given its file descriptor
 * 
 * @param[in] fd the given file descriptor
 * @return int 0 when closed, other when open (file descriptor)
 */
int close_fifo(int fd);

#endif  // CLIENT_INCLUDE_FIFO_H_
