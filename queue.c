#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Kept this minimal because I'm lazy, obviously get better performance if we
 * hold a pointer to the last element, etc.
 */
struct queue_t
{
    void* front;          ///< Pointer to first element
    int num_elements;     ///< Num elements currently in queue
    size_t element_size;  ///< Size of a single element
    int max_num_elements; ///< Max number of elements before overflow occurs
};

/**
 * Initialization
 */
int queue_init(struct queue_t* queue, int max_num_elements, size_t element_size)
{
    queue->front = (void*) calloc(max_num_elements, element_size); // TODO: Return 1 if calloc fail
    queue->num_elements = 0;
    queue->element_size = element_size;
    queue->max_num_elements = max_num_elements;
    return 0;
}

/**
 * Cleanup
 */
int queue_term(struct queue_t* queue)
{
    free(queue->front);
    return 0;
}

/**
 * Inserts one element
 */
int queue_insert(struct queue_t* queue, void* element)
{
    // TODO: If we exceed max_num_elements, return 1
    void* curr_pos_in_queue = queue->front + (queue->num_elements * queue->element_size);
    memcpy(curr_pos_in_queue, element, queue->element_size);
    queue->num_elements++;
    return 0;
}

/**
 * Removes the last element from the queue and writes its value to the output
 * buffer
 */
int queue_pop(struct queue_t* queue, void* buffer)
{
    // TODO: If we have < 1 element then return 1
    void* back = queue->front + (queue->num_elements-1) * queue->element_size;
    memcpy(buffer, back, queue->element_size);
    queue->num_elements--;
    return 0;
}

/**
 * Pops the last n elements off the queue and writes their values to the output
 * buffer
 */
int queue_pop_bulk(struct queue_t* queue, void* buffer, int n)
{
    // TODO: If we don't have enough elements to pop, return 1 TODO: I'm
    // choosing to return elements in order; if we wanted to return in reverse
    // order the most readable way would be to leverage queue_pop()
    void* back = queue->front + (queue->num_elements - n) * queue->element_size;
    memcpy(buffer, back, queue->element_size * n);
    queue->num_elements -= n;
    return 0;
}

/**
 * This is purely for debugging. Queue has no idea what types it contains so
 * it'll just pretend they're integers for now.
 */
void queue_print(struct queue_t* queue)
{
    printf("Queue contents: [ ");
    void* curr = queue->front;
    for (unsigned int i=0; i<queue->num_elements; i++)
    {
        int* num = (int*) curr;
        printf("%d ", *num);
        curr += queue->element_size;
    }
    printf("]\n");
}
