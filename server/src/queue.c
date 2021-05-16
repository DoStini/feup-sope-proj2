#include "../include/queue.h"

typedef struct queue_node {
    Message* value;
    size_t next;
} queue_node_t;

struct queue {
    queue_node_t* array;
    size_t size;
    size_t first;
    size_t last;
    size_t first_empty;
    size_t last_empty;
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
    new_queue->first = size;
    new_queue->last = size;
    new_queue->first_empty = 0;
    new_queue->last_empty = size - 1;

    return new_queue;
}

void queue_destroy(queue_t* queue) {
    free(queue->array);
    free(queue);
}

int queue_push(queue_t* queue, Message* message) {
    if (queue->first_empty == queue->size) return QUEUE_NO_SPACE;

    size_t first_empty = queue->first_empty;
    queue->first_empty = queue->array[queue->first_empty].next;

    queue->array[first_empty].value = message;
    queue->array[first_empty].next = queue->size;

    if (queue->first == queue->size) {
        queue->first = 0;
    } else {
        queue->array[queue->last].next = first_empty;
    }

    queue->last = first_empty;

    return 0;
}

#include <stdio.h>

void queue_print(queue_t* queue) {
    printf(
        "{\n\tsize->%zu,\n\tfirst->%zu,\n\tlast->%zu,\n\tfirst_empty->%zu,"
        "\n\tlast_empty->%zu,",
        queue->size, queue->first, queue->last, queue->first_empty,
        queue->last_empty);

    for (size_t i = 0; i < queue->size; i++) {
        printf("\n\t{\n\t\tvalue_p->%p,", queue->array[i].value);

        if (queue->array[i].value != NULL) {
            printf(
                "\n\t\t{\n\t\t\tid->%d,\n\t\t\tres->%d,"
                "\n\t\t\tt->%d\n\t\t},",
                queue->array[i].value->rid, queue->array[i].value->tskres,
                queue->array[i].value->tskload);
        }

        printf("\n\t\tnext->%zu,\n\t},", queue->array[i].next);
    }

    printf("\n}\n");
}
