#include <stdio.h>
#include <stdlib.h>

struct person {
    struct details {
        int age;
    } *detailsPtr;
} *personPtr;

int main() {
    printf("Enter age: ");
    scanf("%d", &personPtr->detailsPtr->age);
    printf("age: %d", personPtr->detailsPtr->age);
}

// go declare some variables or allocate memory