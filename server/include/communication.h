#ifndef SERVER_INCLUDE_COMMUNICATION_H_
#define SERVER_INCLUDE_COMMUNICATION_H_

#include <pthread.h>

#include "common/common.h"

/**
 * @brief Message information (either sent or received)
 *
 */
typedef Message message_t;

/**
 * @brief Receives a message from the public fifo
 *
 * @param[out] msg the message to receive
 * @return int 0 when closed, other when open
 */
int recv_message(message_t* msg);

/**
 * @brief Sends a message to the thread private fifo
 *
 * @param[in] msg the message to send.
 * @param pid the client's process id.
 * @param tid the id of the client's thread that made the request.
 * @return int 0 when message was sent correctly, otherwise an error is returned.
 */
int send_private_message(message_t* msg, pid_t pid, pthread_t tid);

#endif  // SERVER_INCLUDE_COMMUNICATION_H_
