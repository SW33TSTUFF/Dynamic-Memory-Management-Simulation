#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdbool.h>
#include <stddef.h>

struct heapchunk{
    void *startAddress;
    size_t size;
    bool status;
};

typedef struct heapchunk heapchunk;

void *MyMalloc(size_t size);
void MyFree(void *ptr);

#endif
