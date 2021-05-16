#ifndef SERVER_INCLUDE_QUEUE_H_
#define SERVER_INCLUDE_QUEUE_H_

#include <stdlib.h>

#include "../../common/common.h"

typedef struct queue queue_t;

/**
 * @brief Creates a queue structure and returns it as a pointer.
 *
 * @param size the size used to allocate the inner data structure (array).
 *
 * @return the pointer to the created queue.
 **/
queue_t* queue_(size_t size);

/**
 * @brief Frees resources used by queue given by parameter.
 *
 * @param[in] queue the pointer to the queue.
 **/
void queue_destroy(queue_t* queue);

void queue_print(queue_t* queue);


#endif  // SERVER_INCLUDE_QUEUE_H_
