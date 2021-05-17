#ifndef SERVER_INCLUDE_QUEUE_H_
#define SERVER_INCLUDE_QUEUE_H_

#include <stdlib.h>

#include "../../common/common.h"

#define QUEUE_NO_SPACE 1
#define QUEUE_EMPTY 2

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

/**
 * @brief Inserts a message at the end of the queue.
 *
 * @param[in, out] queue the pointer to the queue.
 * @param[in] message the message to insert.
 *
 * @return an error value.
 **/
int queue_push(queue_t* queue, Message* message);

/**
 * @brief Removes the first element of the queue.
 *
 * @param[in, out] queue the pointer to the queue.
 *
 * @return an error value.
 **/
int queue_pop(queue_t* queue);

/**
 * @brief Gets the first element in the queue.
 *
 * @param[in] queue the pointer to the queue.
 * @param[out] message the message returned.
 *
 * @return an error value.
 **/
int queue_front(queue_t* queue, Message* message);

void queue_print(queue_t* queue);

#endif  // SERVER_INCLUDE_QUEUE_H_
