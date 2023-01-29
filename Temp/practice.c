#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int item;
    struct node * next;
} ListNode;

int main() {
    ListNode *head, *firstNode, *secondNode;

    firstNode = malloc(sizeof(ListNode));
    secondNode = malloc(sizeof(ListNode));

    head = firstNode;

    firstNode -> next = secondNode;
    secondNode -> next = NULL;
    printf("firstnode next: %d\n", firstNode -> next);
    printf("secondnode next: %d\n", secondNode -> next);

}