#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    void** data;       
    size_t capacity;   
    size_t size;       
} Stack;

Stack create_stack() {
    Stack stack;
    stack.capacity = 2;  
    stack.size = 0;
    stack.data = (void**)malloc(stack.capacity * sizeof(void*));  
    if (!stack.data) {
        perror("Memory allocation failed!");
        exit(1);
    }
    return stack;
}

int stack_is_empty(Stack* stack) {
    return stack->size == 0;
}

void resize_stack(Stack* stack) {
    size_t new_capacity = stack->capacity * 2;  
    void** new_data = (void**)realloc(stack->data, new_capacity * sizeof(void*));  
    if (!new_data) {
        perror("Memory allocation failed during resize!");
        exit(1);
    }
    stack->data = new_data;
    stack->capacity = new_capacity;
}

void stack_push(Stack* stack, void* value) {
    if (stack->size == stack->capacity) {
        resize_stack(stack);  
    }
    stack->data[stack->size] = value;
    stack->size++;
}

void* stack_pop(Stack* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack underflow! Unable to pop.\n");
        return NULL;
    }
    stack->size--;
    return stack->data[stack->size];
}

void* stack_peek(Stack* stack) {
    if (stack_is_empty(stack)) {
        printf("Stack is empty! Unable to peek.\n");
        return NULL;
    }
    return stack->data[stack->size - 1];
}

void print_stack(Stack* stack, void (*print)(void*)) {
    if (stack_is_empty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top to bottom): ");
    for (size_t i = stack->size; i > 0; i--) {
        print(stack->data[i - 1]);
    }
    printf("\n");
}

void free_stack(Stack* stack) {
    free(stack->data);
}