#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* data;  
    struct Node* next;  
} Node;

typedef struct HashSet {
    Node** buckets;  
    size_t size;     
    size_t data_size; 
    unsigned long (*hash_function)(void*);  
    int (*compare)(void*, void*);  
} HashSet;

HashSet create_hashset(size_t size, size_t data_size, unsigned long (*hash_function)(void*), int (*compare)(void*, void*)) {
    HashSet set;
    set.size = size;
    set.data_size = data_size;
    set.hash_function = hash_function;
    set.compare = compare;

    set.buckets = (Node**)malloc(size * sizeof(Node*));
    if (!set.buckets) {
        perror("Unable to allocate memory for hashset");
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        set.buckets[i] = NULL; 
    }

    return set;
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

void hashset_add(HashSet* set, void* data) {
    unsigned long hash_value = set->hash_function(data);
    size_t index = hash_value % set->size;

    Node* current = set->buckets[index];
    while (current != NULL) {
        if (set->compare(current->data, data) == 0) {

            return;
        }
        current = current->next;
    }

    Node* new_node = create_node(data, set->data_size);
    new_node->next = set->buckets[index];
    set->buckets[index] = new_node;
}

void hashset_remove(HashSet* set, void* data) {
    unsigned long hash_value = set->hash_function(data);
    size_t index = hash_value % set->size;

    Node* current = set->buckets[index];
    Node* previous = NULL;

    while (current != NULL) {
        if (set->compare(current->data, data) == 0) {

            if (previous == NULL) {
                set->buckets[index] = current->next;  
            } else {
                previous->next = current->next;  
            }
            free(current->data);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Element not found.\n");
}

void print_hashset(HashSet* set, void (*print)(void*)) {
    int first = 1;
    printf("{");
    
    for (size_t i = 0; i < set->size; i++) {
        Node* current = set->buckets[i];
        while (current != NULL) {
            if (!first) {
                printf(", ");
            }
            print(current->data);
            first = 0;
            current = current->next;
        }
    }
    
    printf("}\n");
}

int hashset_contains(HashSet* set, void* data) {
    unsigned long hash_value = set->hash_function(data);
    size_t index = hash_value % set->size;

    Node* current = set->buckets[index];
    while (current != NULL) {
        if (set->compare(current->data, data) == 0) {
            return 1;  
        }
        current = current->next;
    }

    return 0;  
}

void free_hashset(HashSet* set) {
    for (size_t i = 0; i < set->size; i++) {
        Node* current = set->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
    }
    free(set->buckets);
}