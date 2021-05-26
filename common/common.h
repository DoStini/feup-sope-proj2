#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <unistd.h>
#include <pthread.h>

typedef struct {
    int rid;        // request id
    pid_t pid;      // process id
    pthread_t tid;  // thread id
    int tskload;    // task load
    int tskres;     // task result
} Message;

#endif  // COMMON_COMMON_H_
