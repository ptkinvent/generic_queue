#include <stdio.h>
#include "queue.c"

void test1()
{
    // Create a queue of ints
    struct queue_t my_queue;
    const int MAX_NUM_ELEMENTS = 10;
    queue_init(&my_queue, MAX_NUM_ELEMENTS, sizeof(int));

    // Add some datums
    int data1 = 10;
    int data2 = 20;
    int data3 = 30;
    int data4 = 40;
    queue_insert(&my_queue, &data1);
    queue_insert(&my_queue, &data2);
    queue_insert(&my_queue, &data3);
    queue_insert(&my_queue, &data4);
    queue_print(&my_queue);

    const int NUM_ELEMENTS_TO_BULK_POP = 3;
    int output_buffer[NUM_ELEMENTS_TO_BULK_POP];
    queue_pop_bulk(&my_queue, output_buffer, NUM_ELEMENTS_TO_BULK_POP);
    printf("Bulk popped last %d elements: ", NUM_ELEMENTS_TO_BULK_POP);
    for (unsigned int i=0; i<NUM_ELEMENTS_TO_BULK_POP; i++)
    {
        printf(" { %d } ", output_buffer[i]);
    }
    printf("\n");
    queue_print(&my_queue);
    queue_term(&my_queue);
}

void test2()
{
    // Create a queue of custom_data_t
    struct custom_data_t
    {
        int num;
        char name[32];
    };

    struct queue_t my_queue;
    const int MAX_NUM_ELEMENTS = 10;
    queue_init(&my_queue, MAX_NUM_ELEMENTS, sizeof(struct custom_data_t));
    struct custom_data_t data1 = { 50, "FIFTY" };
    struct custom_data_t data2 = { 60, "SIXTY" };
    struct custom_data_t data3 = { 70, "SEVENTY" };
    struct custom_data_t data4 = { 80, "EIGHTY" };
    struct custom_data_t data5 = { 90, "NINETY" };
    struct custom_data_t data6 = { 100, "HUNDRED" };
    queue_insert(&my_queue, &data1);
    queue_insert(&my_queue, &data2);
    queue_insert(&my_queue, &data3);
    queue_insert(&my_queue, &data4);
    queue_insert(&my_queue, &data5);
    queue_insert(&my_queue, &data6);
    queue_print(&my_queue);

    const int NUM_ELEMENTS_TO_BULK_POP = 4;
    struct custom_data_t output_buffer[NUM_ELEMENTS_TO_BULK_POP];
    queue_pop_bulk(&my_queue, output_buffer, NUM_ELEMENTS_TO_BULK_POP);
    printf("Bulk popped last %d elements: ", NUM_ELEMENTS_TO_BULK_POP);
    for (unsigned int i=0; i<NUM_ELEMENTS_TO_BULK_POP; i++)
    {
        printf(" { %d %s } ", output_buffer[i].num, output_buffer[i].name);
    }
    printf("\n");
    queue_print(&my_queue);
    queue_term(&my_queue);
}

int main()
{
    printf("\n============= Test 1 =============\n\n");

    test1();

    printf("\n============= Test 2 =============\n\n");

    test2();

    return 0;
}
