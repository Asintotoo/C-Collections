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
    size_t count;    
    size_t data_size; 
    unsigned long (*hash_function)(void*);  
    int (*compare)(void*, void*);  
} HashSet;

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

void resize_hashset(HashSet* set) {
    size_t new_size = set->size * 2;  
    Node** new_buckets = (Node**)malloc(new_size * sizeof(Node*));
    if (!new_buckets) {
        perror("Unable to allocate memory for resized hashset");
        exit(1);
    }

    for (size_t i = 0; i < new_size; i++) {
        new_buckets[i] = NULL;
    }

    for (size_t i = 0; i < set->size; i++) {
        Node* current = set->buckets[i];
        while (current != NULL) {
            unsigned long hash_value = set->hash_function(current->data);
            size_t index = hash_value % new_size;

            Node* new_node = create_node(current->data, set->data_size);
            new_node->next = new_buckets[index];
            new_buckets[index] = new_node;

            current = current->next;
        }
    }

    free(set->buckets);
    set->buckets = new_buckets;
    set->size = new_size;  
}

HashSet create_hashset(size_t data_size, unsigned long (*hash_function)(void*), int (*compare)(void*, void*)) {
    HashSet set;
    set.size = 4;  
    set.count = 0; 
    set.data_size = data_size;
    set.hash_function = hash_function;
    set.compare = compare;

    set.buckets = (Node**)malloc(set.size * sizeof(Node*));
    if (!set.buckets) {
        perror("Unable to allocate memory for hashset");
        exit(1);
    }

    for (size_t i = 0; i < set.size; i++) {
        set.buckets[i] = NULL;
    }

    return set;
}

void hashset_add(HashSet* set, void* data) {

    if (set->count >= set->size / 2) {
        resize_hashset(set);
    }

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

    set->count++;  
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
            set->count--;
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