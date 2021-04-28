#include "../include/block_array.h"

#include <pthread.h>
#include <stdlib.h>

struct block_array {
    pthread_t* array;
    size_t size;
    size_t block_size;
};

block_array_t* block_array_create(const size_t block_size) {
    block_array_t* block_array = malloc(sizeof(block_array_t));
    if (block_array == NULL) return NULL;

    block_array->array = calloc(block_size, sizeof(pthread_t));
    if (block_array->array == NULL) return NULL;

    block_array->size = block_size;
    block_array->block_size = block_size;

    return block_array;
}

int block_array_at(const block_array_t* const block_array, const size_t index,
                   pthread_t* const value) {
    if (block_array->size <= index) return BLOCK_ARRAY_OUT_OF_BOUNDS;

    *value = block_array->array[index];
    return 0;
}

int block_array_set(block_array_t* const block_array, const size_t index,
                    const pthread_t value) {
    if (block_array->size <= index) {
        size_t blocks = index / block_array->block_size + 1;
        size_t new_size = blocks * block_array->block_size;

        pthread_t* new_array =
            reallocarray(block_array->array, new_size, sizeof(pthread_t));

        if (new_array == NULL) return BLOCK_ARRAY_ALLOC_ERR;

        block_array->array = new_array;
        block_array->size = new_size;
    }

    block_array->array[index] = value;

    return 0;
}

size_t block_array_get_size(const block_array_t* const block_array) {
    return block_array->size;
}

void block_array_delete(block_array_t* const block_array) {
    free(block_array->array);
    free(block_array);
}
