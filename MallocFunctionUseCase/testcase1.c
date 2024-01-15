#include <stdio.h>
#include "mymalloc.h"

int main() {
    int *ptr = (int*) MyMalloc(sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
    } else {
        *ptr = 10;
        printf("Value: %d\n", *ptr);
        MyFree(ptr);
    }
    
    return 0;
}

