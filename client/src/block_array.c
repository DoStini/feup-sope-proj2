#include "../include/block_array.h"

#include <stdlib.h>

struct block_array {
    array_value_t* array;
    array_type_t type;
    size_t size;
    size_t block_size;
};

static const size_t type_to_size[] = {sizeof(pthread_t), sizeof(int32_t),
                                      sizeof(char)};

block_array_t* block_array_create(const array_type_t type,
                                  const size_t block_size) {
    block_array_t* block_array = malloc(sizeof(block_array_t));
    if (block_array == NULL) return NULL;

    block_array->array = malloc(block_size * type_to_size[type]);
    if (block_array->array == NULL) return NULL;

    block_array->type = type;
    block_array->size = block_size;
    block_array->block_size = block_size;

    return block_array;
}

int block_array_at(const block_array_t* const block_array,
                   array_value_t* const value);

array_type_t block_array_get_type(const block_array_t* const block_array);

int block_array_set(block_array_t* const block_array, const size_t index,
                    const array_value_t value);

void block_array_delete(block_array_t* const block_array) {
    free(block_array->array);
    free(block_array);
}