#include <stdio.h>
#include <stdlib.h>
#include "../Deque.c"

void print_int(void* data) {
    printf("%d", *(int*)data);
}

int main() {

    Deque deque = create_deque(sizeof(int));

    int a = 10, b = 20, c = 30;

    deque_push_front(&deque, &a);
    deque_push_rear(&deque, &b);
    deque_push_front(&deque, &c);

    print_deque(&deque, print_int);  

    int* value = (int*)deque_pop_front(&deque);
    printf("Popped front: %d\n", *value);  

    value = (int*)deque_pop_rear(&deque);
    printf("Popped rear: %d\n", *value);  

    print_deque(&deque, print_int);  

    free_deque(&deque);

    return 0;
}