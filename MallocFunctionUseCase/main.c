#include <stdio.h>
#include "mymalloc.h"

int main() {
    // Allocate memory using MyMalloc
    int *ptr1 = (int*)MyMalloc(sizeof(int));
    if (ptr1 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Use allocated memory
    *ptr1 = 10;
    printf("Allocated memory content: %d\n", *ptr1);

    // Allocate more memory
    int *ptr2 = (int*)MyMalloc(2 * sizeof(int));
    if (ptr2 == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Use allocated memory
    ptr2[0] = 20;
    ptr2[1] = 30;
    printf("Allocated memory content: %d, %d\n", ptr2[0], ptr2[1]);

    // Free allocated memory
    MyFree(ptr1);
    MyFree(ptr2);

    printf("Memory freed successfully.\n");

    return 0;
}

