#include <stdio.h>
#include <stdlib.h>
#include "../Stack.c"

void print_int(void* data) {
    printf("%d ", *(int*)data);
}

void print_string(void* data) {
    printf("%s ", (char*)data);
}

int main() {

    Stack stack_int = create_stack();

    int a = 10, b = 20, c = 30;
    stack_push(&stack_int, &a);
    stack_push(&stack_int, &b);
    stack_push(&stack_int, &c);

    print_stack(&stack_int, print_int);

    int* popped_int = (int*)stack_pop(&stack_int);
    printf("Popped value: %d\n", *popped_int);

    print_stack(&stack_int, print_int);
    free_stack(&stack_int);

    Stack stack_str = create_stack();

    char* str1 = "This", *str2 = "is", *str3 = "a", *str4 = "sentence";
    stack_push(&stack_str, str1);
    stack_push(&stack_str, str2);
    stack_push(&stack_str, str3);
    stack_push(&stack_str, str4);

    print_stack(&stack_str, print_string);

    char* popped_str = (char*)stack_pop(&stack_str);
    printf("Popped value: %s\n", popped_str);

    print_stack(&stack_str, print_string);
    free_stack(&stack_str);

    return 0;
}