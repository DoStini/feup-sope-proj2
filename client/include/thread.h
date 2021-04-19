#ifndef CLIENT_INCLUDE_THREAD_H_
#define CLIENT_INCLUDE_THREAD_H_

#include <pthread.h>
#include <sys/types.h>

typedef struct tinfo {
    pthread_t tid;
    int fifo_fd[2];
} tinfo_t;

#endif  // CLIENT_INCLUDE_THREAD_H_
