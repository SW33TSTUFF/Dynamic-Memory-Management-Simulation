#include <stdio.h>
#include "mymalloc.h"

#define ARRAYMAX 25000
#define METADATAMAX 2500	// metadata size wasnt specified in the question. Took 2500

char heap[ARRAYMAX] = {0};	// mentioned array of 25000 bytes

size_t heapSize = 0;

const size_t metaDataStart = 22500;
heapchunk *metadata = (heapchunk *)(heap+metaDataStart);	// type cast becuase heap was initially initalized as char
size_t metaDataEnd = 0;

void *MyMalloc(size_t size){

    for(size_t i=0; i<metaDataEnd; i++) {

        if ((metadata+i)->status == false) {	// not taken

            if ((metadata+i)->size == size) {	// requested size is the same size as the current block
                // Allocate memory using current block
                (metadata+i)->size = size;
                (metadata+i)->status = true;

                // printf("Memory allocated in a free slot which was the same size as the given size\n");
                return (metadata+i)->startAddress;

            } 
            else if ((metadata+i)->size > size){	// Requested size is smaller than the current block
                // Create new slot for next free space and insert
                for (size_t j = metaDataEnd; j > i+1; j--){
                    *(metadata+j) = *(metadata+j-1);	// shifting is done to fill the gaps
                }
                
                size_t updatedSize = (metadata+i)->size - size;	// new size by getting the metadata size - allocated block size
                void *updatedLocation = (metadata+i)->startAddress + size;
                (metadata+i)->size = size;
                (metadata+i)->status = true;
                
                heapchunk chunk; // create an instance of that chunk struct
                chunk.startAddress = updatedLocation;
                chunk.size = updatedSize;
                chunk.status = false;
                

                *(metadata+i+1) = chunk;
                metaDataEnd++;

                // printf("Memory allocated in a free slot\n");
                return (metadata+i)->startAddress;

            } 
            else {
                continue;
            }
        }
    }

    // Suppose the first 2 two options isnt available we simple allocate memory after the last allocated memry slot
    if(heapSize + size <= ARRAYMAX-METADATAMAX)
    {
        void *newAddress = heap + heapSize;
        heapSize = heapSize + size;

        heapchunk chunk;
        chunk.startAddress = newAddress;
        chunk.size = size;
        chunk.status = true;

        *(metadata+metaDataEnd) = chunk;	// simply enlisting that chunk
        metaDataEnd++;

        // printf("Memory allocated in next available space\n");
        return newAddress;
    }
    else {
        // printf("Memory not allocated\n");
        return NULL;
    }

}

void MyFree(void *ptr) {
    /*
    Make slots free
    */
    for (size_t i=0; i<metaDataEnd; i++){
        if ((metadata+i)->startAddress == ptr){
            (metadata+i)->status = false;	// No need to change the values to 0
            break;
        }
    }
    // merge next to next free blocks

    for (size_t i = 0; i < metaDataEnd-1; i++) {
        if ((metadata+i)->status == false) {

            heapchunk *preptr = metadata+i;
            heapchunk *ptr = (metadata+i) + 1;
            
            if ((ptr+1)->status == false) {
                
                preptr->size = preptr->size + (ptr)->size;
                // After merging the chunks, it shifts the remaining chunks in the metadata array to fill the gap left by the merged chunks
                for(size_t j=0;j < metaDataEnd-2; j++){	// shifting by 1 becuase we now only need 1 metadata for the merge
                    *(preptr+j)=*(preptr+(j+1));
                }
                metaDataEnd = metaDataEnd -1;
            }
        }
        
    }
    // printf("Memory freed\n");
}
