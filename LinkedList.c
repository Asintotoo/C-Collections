#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    size_t data_size;
} LinkedList;

LinkedList create_list(size_t data_size) {
    LinkedList list;
    list.head = NULL;
    list.data_size = data_size;
    return list;
}

Node* create_node(void* data, size_t data_size) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Unable to allocate memory for node");
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

void list_insert_head(LinkedList* list, void* data) {
    Node* new_node = create_node(data, list->data_size);
    new_node->next = list->head;
    list->head = new_node;
}

void list_insert_end(LinkedList* list, void* data) {
    Node* new_node = create_node(data, list->data_size);
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void list_remove_head(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty. Cannot remove head.\n");
        return;
    }

    Node* temp = list->head;
    list->head = list->head->next;
    free(temp->data);
    free(temp);
}

void list_remove_value(LinkedList* list, void* data, int (*compare)(void*, void*)) {
    if (list->head == NULL) {
        printf("List is empty. Cannot remove value.\n");
        return;
    }

    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL && compare(current->data, data) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value not found in the list.\n");
        return;
    }

    if (previous == NULL) { 
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current->data);
    free(current);
}

void print_list(LinkedList* list, void (*print)(void*)) {
    Node* current = list->head;
    while (current != NULL) {
        print(current->data);
        printf(" -> ");
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}