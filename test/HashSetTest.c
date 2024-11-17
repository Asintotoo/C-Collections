#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashSet.c"

void print_int(void* data) {
    printf("%d", *(int*)data);
}

unsigned long hash_int(void* data) {
    return *(int*)data;
}

int compare_int(void* data1, void* data2) {
    return *(int*)data1 - *(int*)data2;
}

int main() {
    HashSet set = create_hashset(sizeof(int), hash_int, compare_int);

    int a = 5, b = 10, c = 15, d = 15;

    hashset_add(&set, &a);
    hashset_add(&set, &b);
    hashset_add(&set, &c);
	hashset_add(&set, &d);
	
	printf("Original Set\n");
	print_hashset(&set, print_int);

    printf("Contains 10: %d\n", hashset_contains(&set, &b));  
    printf("Contains 20: %d\n", hashset_contains(&set, &a));  

    hashset_remove(&set, &b);
	printf("Set after the removal of 10\n");
	print_hashset(&set, print_int);
    printf("Contains 10 after removal: %d\n", hashset_contains(&set, &b));  

    free_hashset(&set);

    return 0;
}