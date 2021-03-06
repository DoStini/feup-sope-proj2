#ifndef SERVER_INCLUDE_FIFO_H_
#define SERVER_INCLUDE_FIFO_H_

#define MAX_FIFO_NAME FILENAME_MAX
#define TIMEOUT 5

/**
 * @brief Create the public fifo.
 *
 * @return int 0 when creation is successful
 */
int create_public_fifo(void);

/**
 * @brief Deletes the public fifo.
 *
 * @return int 0 when closed, other when open (file descriptor)
 */
int remove_public_fifo(void);

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
 * @param fd the given file descriptor
 * @return int 0 when closed, other when open (file descriptor)
 */
int close_fifo(int fd);

#endif  // SERVER_INCLUDE_FIFO_H_
