#include "../include/queue.h"

typedef struct queue_node {
    Message* value;
    size_t next;
} queue_node_t;

struct queue {
    queue_node_t* array;
    size_t size;
    size_t first;
    size_t first_empty;
};

queue_t* queue_(size_t size) {
    queue_t* new_queue = malloc(sizeof(queue_t));
    if (new_queue == NULL) return new_queue;

    new_queue->array = malloc(size * sizeof(queue_node_t));
    if (new_queue->array == NULL) return NULL;

    for (size_t i = 0; i < size; i++) {
        new_queue->array[i].next = i + 1;
        new_queue->array[i].value = NULL;
    }

    new_queue->size = size;
    new_queue->first = size + 1;
    new_queue->first_empty = 0;

    return new_queue;
}

#include <stdio.h>

void queue_print(queue_t* queue) {
    printf("{\n\tsize->%zu,\n\tfirst->%zu,\n\tfirst_empty->%zu,", queue->size,
           queue->first, queue->first_empty);

    for (size_t i = 0; i < queue->size; i++) {
        printf("\n\t{\n\t\tvalue->%p,\n\t\tnext->%zu\n\t},",
               queue->array[i].value, queue->array[i].next);
    }

    printf("\n}\n");
}
