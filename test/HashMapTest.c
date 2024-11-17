#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashMap.c"

unsigned long hash_int(void* key) {
    return *(int*)key;
}

int compare_int(void* key1, void* key2) {
    return *(int*)key1 - *(int*)key2;
}

void print_pair(void* key, void* value) {
    printf("(%d, %d)", *(int*)key, *(int*)value);
}

int main() {

    HashMap map = create_hashmap(10, sizeof(int), sizeof(int), hash_int, compare_int);

    int key1 = 1, key2 = 5, key3 = 10, key4 = 43;
    int value1 = 100, value2 = 200, value3 = 300, value4 = 400;

    hashmap_put(&map, &key1, &value1);
    hashmap_put(&map, &key2, &value2);
    hashmap_put(&map, &key3, &value3);
    hashmap_put(&map, &key4, &value4);

    printf("Original Map: ");
    print_hashmap(&map, print_pair);
	
	hashmap_put(&map, &key1, &value2);
	printf("Map after new value: ");
    print_hashmap(&map, print_pair);

    int* value = hashmap_get(&map, &key2);
    if (value) {
        printf("Value of key 5: %d\n", *value);
    } else {
        printf("Key 5 not found.\n");
    }

    hashmap_remove(&map, &key3);
    printf("Map after the removal of the key 10: ");
    print_hashmap(&map, print_pair);

    if (hashmap_contains_key(&map, &key1)) {
        printf("Key 1 exists in the Map.\n");
    }

    free_hashmap(&map);

    return 0;
}