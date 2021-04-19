#ifndef CLIENT_INCLUDE_COMMUNICATION_H_
#define CLIENT_INCLUDE_COMMUNICATION_H_

#include <pthread.h>
#include <sys/types.h>

typedef struct message {
    int i;
    int t;
    pid_t pid;
    pthread_t tid;
    int res;
} message_t;

int build_message(message_t* msg);

int send_message(message_t* msg);

#endif  // CLIENT_INCLUDE_COMMUNICATION_H_
