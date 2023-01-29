#include <stdio.h>
#include <stdlib.h>

struct person {
        char firstname[15];
        char lastname[15];
        struct {
            int age;
            float height;
            float weight;
            char firstname[15];
        }Info, *InfoPtr;

        // struct person * next;
    } student1;

int main() {
    struct person *studentPtr = &student1;
    scanf("%d", &studentPtr->InfoPtr->age);
    printf("%d", studentPtr->InfoPtr->age);

    return 0;
}