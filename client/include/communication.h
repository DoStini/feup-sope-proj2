#ifndef CLIENT_INCLUDE_COMMUNICATION_H_
#define CLIENT_INCLUDE_COMMUNICATION_H_

#include <pthread.h>
#include <sys/types.h>

/**
 * @brief Message information (either sent or received)
 * 
 */
typedef struct message {
    int i;
    pid_t pid;
    pthread_t tid;
    int t;
    int res;
} message_t;

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
 * @brief Returns if the server is open already
 * 
 * @return int 0 when closed, other when open (file descriptor)
 */
int is_server_open();

/**
 * @brief Set the server file descriptor
 * 
 * @param[in] open the server file descriptor
 * @return int 0 when closed, other when open (file descriptor)
 */
int set_server_open(int open);

/**
 * @brief Sends a message to the public fifo
 * 
 * @param[in] msg the message to send
 * @return int 0 when closed, other when open
 */
int send_public_message(message_t* msg);

/**
 * @brief Receives a message of the thread private fifo
 * 
 * @param[out] msg the received message
 * @return int 0 when closed, other when open
 */
int recv_private_message(message_t* msg);

#endif  // CLIENT_INCLUDE_COMMUNICATION_H_
