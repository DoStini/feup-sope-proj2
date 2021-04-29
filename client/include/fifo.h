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
int create_private_fifo(void);

/**
 * @brief Deletes the thread private fifo
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int remove_private_fifo(void);

/**
 * @brief Opens the private fifo for reading
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int open_read_private_fifo(void);

/**
 * @brief Set the public fifo file descriptor
 * 
 * @param[in] fd the public fifo fd
 * @return int 0 when closed, other when open (file descriptor)
 */
int set_public_fifo(int fd);

/**
 * @brief Gets the public fifo fd
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int get_public_fifo();

/**
 * @brief Waits until the public fifo is open and available to read. 
 * Initializes other important variables.
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int wait_public_fifo();

/**
 * @brief Closes a fifo given its file descriptor
 * 
 * @param[in] fd the given file descriptor
 * @return int 0 when closed, other when open (file descriptor)
 */
int close_fifo(int fd);

#endif  // CLIENT_INCLUDE_FIFO_H_
