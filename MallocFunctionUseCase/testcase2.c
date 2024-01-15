#include <stdio.h>
#include "mymalloc.h"

int main() {
    int size = 5;
    int *arr = (int*) MyMalloc(size * sizeof(int));
    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
    } else {
        for (int i = 0; i < size; i++) {
            arr[i] = i + 1;
            printf("%d ", arr[i]);
        }
        printf("\n");
        MyFree(arr);
    }
    
    return 0;
}

