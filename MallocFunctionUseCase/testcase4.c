#include <stdio.h>
#include "mymalloc.h"
#include <string.h>

int main() {
    char *str = (char*) MyMalloc(10 * sizeof(char));
    
    if (str == NULL) {
        printf("Memory allocation failed!\n");
    } else {
        strcpy(str, "Hello");
        printf("String: %s\n", str);
        MyFree(str);
    }
    
    return 0;
}

