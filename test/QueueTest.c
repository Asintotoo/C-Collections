#include <stdio.h>
#include <stdlib.h>
#include "../Queue.c"

void print_int(void* data) {
    printf("%d", *(int*)data);
}

int main() {
    Queue queue = create_queue(sizeof(int));

    int a = 10, b = 20, c = 30;

    queue_enqueue(&queue, &a);
    queue_enqueue(&queue, &b);
    queue_enqueue(&queue, &c);

    print_queue(&queue, print_int);

    int* value = (int*)queue_dequeue(&queue);
    printf("Dequeued: %d\n", *value);

    print_queue(&queue, print_int);

    free_queue(&queue);

    return 0;
}
