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

/**
 * @brief Frees up resources used by given block array.
 *
 * @param[in] block_array pointer to the block array being freed.
 **/
void block_array_delete(block_array_t* const block_array);

/**
 * @brief Creates a block array.
 *
 * @param type an enum specifying the type of elements stored in the array.
 * @param block_size size, in number of elements, of the blocks of memory added
 *to the array if more space is needed.
 *
 * @return the pointer of the created block array or NULL if an error ocurred.
 **/
block_array_t* block_array_create(const array_type_t type,
                                  const size_t block_size);

/**
 * @brief Sets a value to an element of the array given its index.
 *
 * @param[in] block_array pointer to the block array.
 * @param index index of the element in the array.
 * @param value value being set.
 *
 * @return an error value.
 **/
int block_array_set(block_array_t* const block_array, const size_t index,
                    const array_value_t value);

/**
 * @brief Gets the type of values stored in array.
 *
 * @param[in] block_array pointer to the block array.
 *
 * @return an enum specifying the type of values.
 **/
array_type_t block_array_get_type(const block_array_t* const block_array);

/**
 * @brief Gets the size allocated to the array.
 *
 * @param[in] block_array pointer to the block array.
 *
 * @return the size.
 **/
size_t block_array_get_size(const block_array_t* const block_array);

/**
 * @brief Gets the value of the element at a given index of the array.
 *
 * @param[in] block_array pointer to the block array.
 * @param index index of the element in the array.
 * @param[out] value the value at the given index in the array.
 *
 * @return an error value.
 **/
int block_array_at(const block_array_t* const block_array, const size_t index,
                   array_value_t* const value);

#endif  // CLIENT_INCLUDE_BLOCK_ARRAY_H_