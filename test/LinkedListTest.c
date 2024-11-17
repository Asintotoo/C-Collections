#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../LinkedList.c"


void print_int(void* data) {
    printf("%d", *(int*)data);
}

int compare_int(void* data1, void* data2) {
    return *(int*)data1 - *(int*)data2;
}

int main() {

    LinkedList list = create_list(sizeof(int));

    int a = 5, b = 10, c = 15;

    list_insert_head(&list, &a);
    list_insert_head(&list, &b);
    list_insert_end(&list, &c);

    printf("Original List:\n");
    print_list(&list, print_int);

    list_remove_value(&list, &b, compare_int);

    printf("List after the removal of 10:\n");
    print_list(&list, print_int);

    list_remove_head(&list);

    printf("List after the removal of the head:\n");
    print_list(&list, print_int);

    free_list(&list);

    return 0;
}