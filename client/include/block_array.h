#ifndef CLIENT_INCLUDE_BLOCK_ARRAY_H_
#define CLIENT_INCLUDE_BLOCK_ARRAY_H_

#define BLOCK_ARRAY_ALLOC_ERR -1
#define BLOCK_ARRAY_OUT_OF_BOUNDS -2

#include <pthread.h>
#include <stdint.h>

typedef struct block_array block_array_t;

typedef union array_value {
    pthread_t thread_value;
    int32_t int32_value;
    char char_value;
} array_value_t;

typedef enum array_type { THREAD_VAL = 0, INT32_VAL, CHAR_VAL } array_type_t;

void block_array_delete(block_array_t* const block_array);

block_array_t* block_array_create(const array_type_t type,
                                  const size_t block_size);

int block_array_set(block_array_t* const block_array, const size_t index,
                    const array_value_t value);

array_type_t block_array_get_type(const block_array_t* const block_array);

size_t block_array_get_size(const block_array_t* const block_array);

int block_array_at(const block_array_t* const block_array, const size_t index,
                   array_value_t* const value);

#endif  // CLIENT_INCLUDE_BLOCK_ARRAY_H_