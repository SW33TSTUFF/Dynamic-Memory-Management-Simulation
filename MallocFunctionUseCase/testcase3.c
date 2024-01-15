#include <stdio.h>
#include "mymalloc.h"

typedef struct {
    int id;
    char name[20];
} Person;

int main() {
    Person *person = (Person*) MyMalloc(sizeof(Person));
    
    if (person == NULL) {
        printf("Memory allocation failed!\n");
    } else {
        person->id = 1;
        strcpy(person->name, "John Doe");
        printf("ID: %d, Name: %s\n", person->id, person->name);
        MyFree(person);
    }
    
    return 0;
}

