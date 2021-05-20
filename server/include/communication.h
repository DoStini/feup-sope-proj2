#ifndef SERVER_INCLUDE_COMMUNICATION_H_
#define SERVER_INCLUDE_COMMUNICATION_H_

#include <pthread.h>
#include <sys/types.h>

#include "../../common/common.h"

/**
 * @brief Message information (either sent or received)
 *
 */
typedef Message message_t;

/**
 * @brief Builds a message object
 *
 * @param[out] msg the built message
 * @param[in] id the id of the message
 * @param[in] res the result of the message
 * @param[in] t the time of the message
 * @return int 0 upon sucess, other upon error
 */
int build_message(message_t* msg, int id, int res, int t);

/**
 * @brief Receives a message from the public fifo
 *
 * @param[out] msg the message to receive
 * @return int 0 when closed, other when open
 */
int recv_message(message_t* msg);

/**
 * @brief Receives a message of the thread private fifo
 *
 * @param[in] msg the message to send
 * @return int 0 when closed, other when open
 */
int send_private_message(message_t* msg, pid_t pid, pthread_t tid);

#endif  // SERVER_INCLUDE_COMMUNICATION_H_
