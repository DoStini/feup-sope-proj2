#ifndef CLIENT_INCLUDE_BLOCK_ARRAY_H_
#define CLIENT_INCLUDE_BLOCK_ARRAY_H_

#define ALLOC_ERR -1

#include <pthread.h>
#include <stdint.h>

typedef struct block_array block_array_t;

typedef union array_value {
    pthread_t thread_value;
    int32_t int32_value;
    char char_value;
} array_value_t;

typedef enum array_type { THREAD_VAL = 0, INT32_VAL, CHAR_VAL} array_type_t;

void block_array_delete(block_array_t* const block_array);

block_array_t* block_array_create(const array_type_t type,
                                  const size_t block_size);

#endif  // CLIENT_INCLUDE_BLOCK_ARRAY_H_