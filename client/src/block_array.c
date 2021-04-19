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

    block_array->array = calloc(block_size, type_to_size[type]);
    if (block_array->array == NULL) return NULL;

    block_array->type = type;
    block_array->size = block_size;
    block_array->block_size = block_size;

    return block_array;
}

int block_array_at(const block_array_t* const block_array, const size_t index,
                   array_value_t* const value) {
    if (block_array->size <= index) return BLOCK_ARRAY_OUT_OF_BOUNDS;

    *value = block_array->array[index];
    return 0;
}

array_type_t block_array_get_type(const block_array_t* const block_array) {
    return block_array->type;
}

int block_array_set(block_array_t* const block_array, const size_t index,
                    const array_value_t value) {
    if (block_array->size <= index) {
        size_t blocks = index / block_array->block_size + 1;
        size_t new_size = blocks * block_array->block_size;

        array_value_t* new_array = reallocarray(
            block_array->array, new_size, type_to_size[block_array->type]);

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

void test() {
    array_value_t value;

    block_array_t* threads = block_array_create(THREAD_VAL, 10);
    if (threads == NULL) return;

    value.thread_value = 1;
    block_array_set(threads, 0, value);
    value.thread_value = 3;
    block_array_set(threads, 1, value);
    value.thread_value = 9;
    block_array_set(threads, 50, value);

    // int err;
    // err = block_array_at(threads, 0, &value);
    // printf("index 0: %ld, ret val: %d\n", value.thread_value, err);
    // err = block_array_at(threads, 1, &value);
    // printf("index 1: %ld, ret val: %d\n", value.thread_value, err);
    // err = block_array_at(threads, 2, &value);
    // printf("index 2: %ld, ret val: %d\n", value.thread_value, err);
    // err = block_array_at(threads, 50, &value);
    // printf("index 10: %ld, ret val: %d\n", value.thread_value, err);
    // printf("size:: %ld\n", block_array_get_size(threads));
}