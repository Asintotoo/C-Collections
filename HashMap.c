#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* key;
    void* value;
    struct Node* next;
} Node;

typedef struct HashMap {
    Node** buckets;            
    size_t size;               
    size_t key_size;           
    size_t value_size;         
    unsigned long (*hash_function)(void*);   
    int (*compare_keys)(void*, void*);      
} HashMap;

HashMap create_hashmap(size_t size, size_t key_size, size_t value_size,
                       unsigned long (*hash_function)(void*),
                       int (*compare_keys)(void*, void*)) {
    HashMap map;
    map.size = size;
    map.key_size = key_size;
    map.value_size = value_size;
    map.hash_function = hash_function;
    map.compare_keys = compare_keys;
    map.buckets = (Node**)malloc(size * sizeof(Node*));
    if (!map.buckets) {
        perror("Unable to allocate memory for hashmap");
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        map.buckets[i] = NULL;
    }

    return map;
}

Node* create_node(void* key, void* value, size_t key_size, size_t value_size) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("Unable to allocate memory for node");
        exit(1);
    }
    new_node->key = malloc(key_size);
    new_node->value = malloc(value_size);
    if (!new_node->key || !new_node->value) {
        perror("Unable to allocate memory for node key or value");
        exit(1);
    }
    memcpy(new_node->key, key, key_size);
    memcpy(new_node->value, value, value_size);
    new_node->next = NULL;
    return new_node;
}

void hashmap_put(HashMap* map, void* key, void* value) {
    unsigned long hash_value = map->hash_function(key);
    size_t index = hash_value % map->size;

    Node* current = map->buckets[index];
    while (current != NULL) {
        if (map->compare_keys(current->key, key) == 0) {

            memcpy(current->value, value, map->value_size);
            return;
        }
        current = current->next;
    }

    Node* new_node = create_node(key, value, map->key_size, map->value_size);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

void* hashmap_get(HashMap* map, void* key) {
    unsigned long hash_value = map->hash_function(key);
    size_t index = hash_value % map->size;

    Node* current = map->buckets[index];
    while (current != NULL) {
        if (map->compare_keys(current->key, key) == 0) {
            return current->value;  
        }
        current = current->next;
    }

    return NULL;  
}

void hashmap_remove(HashMap* map, void* key) {
    unsigned long hash_value = map->hash_function(key);
    size_t index = hash_value % map->size;

    Node* current = map->buckets[index];
    Node* previous = NULL;

    while (current != NULL) {
        if (map->compare_keys(current->key, key) == 0) {

            if (previous == NULL) {
                map->buckets[index] = current->next;  
            } else {
                previous->next = current->next;  
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Key not found.\n");
}

int hashmap_contains_key(HashMap* map, void* key) {
    unsigned long hash_value = map->hash_function(key);
    size_t index = hash_value % map->size;

    Node* current = map->buckets[index];
    while (current != NULL) {
        if (map->compare_keys(current->key, key) == 0) {
            return 1;  
        }
        current = current->next;
    }

    return 0;  
}


void print_hashmap(HashMap* map, void (*print)(void*, void*)) {
    printf("{ ");
    int first = 1;
    for (size_t i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current != NULL) {
            if (!first) {
                printf(", ");
            }
            print(current->key, current->value);
            first = 0;
            current = current->next;
        }
    }
    printf(" }\n");
}

void free_hashmap(HashMap* map) {
    for (size_t i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(map->buckets);
}