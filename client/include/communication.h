#ifndef CLIENT_INCLUDE_COMMUNICATION_H_
#define CLIENT_INCLUDE_COMMUNICATION_H_

#include <pthread.h>
#include <sys/types.h>

typedef struct message {
    int i;
    pid_t pid;
    pthread_t tid;
    int t;
    int res;
} message_t;

int build_message(message_t* msg, int id, int res, int t);

int send_message(message_t* msg);

int recv_message(message_t* msg);

#endif  // CLIENT_INCLUDE_COMMUNICATION_H_
