#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DequeNode {
    void* data;               
    struct DequeNode* next;   
    struct DequeNode* prev;   
} DequeNode;

typedef struct Deque {
    DequeNode* front;         
    DequeNode* rear;          
    size_t size;              
    size_t data_size;         
} Deque;

Deque create_deque(size_t data_size) {
    Deque deque;
    deque.front = NULL;
    deque.rear = NULL;
    deque.size = 0;
    deque.data_size = data_size;
    return deque;
}

DequeNode* create_deque_node(void* data, size_t data_size) {
    DequeNode* new_node = (DequeNode*)malloc(sizeof(DequeNode));
    if (!new_node) {
        perror("Unable to allocate memory for deque node");
        exit(1);
    }
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        perror("Unable to allocate memory for node data");
        exit(1);
    }
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void deque_push_front(Deque* deque, void* data) {
    DequeNode* new_node = create_deque_node(data, deque->data_size);

    if (deque->front == NULL) {

        deque->front = deque->rear = new_node;
    } else {

        new_node->next = deque->front;
        deque->front->prev = new_node;
        deque->front = new_node;
    }

    deque->size++; 
}

void deque_push_rear(Deque* deque, void* data) {
    DequeNode* new_node = create_deque_node(data, deque->data_size);

    if (deque->rear == NULL) {

        deque->front = deque->rear = new_node;
    } else {

        new_node->prev = deque->rear;
        deque->rear->next = new_node;
        deque->rear = new_node;
    }

    deque->size++; 
}

void* deque_pop_front(Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque underflow! Unable to pop front.\n");
        return NULL; 
    }

    DequeNode* temp = deque->front;
    void* data = temp->data;

    deque->front = deque->front->next;

    if (deque->front == NULL) {
        deque->rear = NULL;
    } else {
        deque->front->prev = NULL;
    }

    free(temp); 
    deque->size--; 

    return data;
}

void* deque_pop_rear(Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque underflow! Unable to pop rear.\n");
        return NULL; 
    }

    DequeNode* temp = deque->rear;
    void* data = temp->data;

    deque->rear = deque->rear->prev;

    if (deque->rear == NULL) {
        deque->front = NULL;
    } else {
        deque->rear->next = NULL;
    }

    free(temp); 
    deque->size--; 

    return data;
}

void* deque_peek_front(Deque* deque) {
    if (deque->front == NULL) {
        printf("Deque is empty! Unable to peek front.\n");
        return NULL; 
    }
    return deque->front->data;
}

void* deque_peek_rear(Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque is empty! Unable to peek rear.\n");
        return NULL; 
    }
    return deque->rear->data;
}

int deque_is_empty(Deque* deque) {
    return deque->size == 0;
}

void print_deque(Deque* deque, void (*print)(void*)) {
    if (deque_is_empty(deque)) {
        printf("Deque is empty!\n");
        return;
    }

    printf("Deque (front to rear): ");
    DequeNode* current = deque->front;
    while (current != NULL) {
        print(current->data);
        printf(" ");
        current = current->next;
    }
    printf("\n");
}

void free_deque(Deque* deque) {
    while (!deque_is_empty(deque)) {
        deque_pop_front(deque); 
    }
}