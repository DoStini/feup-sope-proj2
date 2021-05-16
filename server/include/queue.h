#ifndef SERVER_INCLUDE_QUEUE_H_
#define SERVER_INCLUDE_QUEUE_H_

#include <stdlib.h>

#include "../../common/common.h"

typedef struct queue queue_t;

queue_t* queue_(size_t size);

void queue_print(queue_t* queue);

#endif  // SERVER_INCLUDE_QUEUE_H_
