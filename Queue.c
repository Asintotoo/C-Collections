#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueNode {
    void* data;               
    struct QueueNode* next;   
} QueueNode;

typedef struct Queue {
    QueueNode* front;         
    QueueNode* rear;          
    size_t size;              
    size_t data_size;         
} Queue;

Queue create_queue(size_t data_size) {
    Queue queue;
    queue.front = NULL;
    queue.rear = NULL;
    queue.size = 0;
    queue.data_size = data_size;
    return queue;
}

QueueNode* create_queue_node(void* data, size_t data_size) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (!new_node) {
        perror("Unable to allocate memory for queue node");
        exit(1);
    }
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        perror("Unable to allocate memory for node data");
        exit(1);
    }
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

void queue_enqueue(Queue* queue, void* data) {
    QueueNode* new_node = create_queue_node(data, queue->data_size);

    if (queue->rear == NULL) {

        queue->front = queue->rear = new_node;
    } else {

        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++; 
}

void* queue_dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue underflow! Unable to dequeue.\n");
        return NULL; 
    }

    QueueNode* temp = queue->front;
    void* data = temp->data;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp); 
    queue->size--; 

    return data;
}

void* queue_peek(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty! Unable to peek.\n");
        return NULL; 
    }
    return queue->front->data;
}

int queue_is_empty(Queue* queue) {
    return queue->size == 0;
}

void print_queue(Queue* queue, void (*print)(void*)) {
    if (queue_is_empty(queue)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue (front to rear): ");
    QueueNode* current = queue->front;
    while (current != NULL) {
        print(current->data);
        printf(" ");
        current = current->next;
    }
    printf("\n");
}

void free_queue(Queue* queue) {
    while (!queue_is_empty(queue)) {
        queue_dequeue(queue); 
    }
}