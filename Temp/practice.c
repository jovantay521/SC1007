#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int item;
    struct node * next;
} ListNode;

void printlist(ListNode *head) {
    if (head == NULL) {
        return;
    }

    else {
        while (head != NULL) {
            printf("%d", head -> item);
            head = head -> next;
            printf("\n");
        }
        // printf("\n");
    }
}

ListNode *FindNode(ListNode *head, int index) {
    // finds node with given index and returns it
    if (head == NULL || index < 0) {
        return NULL;
    }

    while (index > 0) {
        head = head -> next;
        if (head == NULL) {
            return NULL;
        }
        index--;
    }

    return head;
}

int main() {
    ListNode *head = NULL, *temp;
    // head points to first node, temp points to last node
    int i = 0;
    
    printf("insert value: ");
    scanf("%d", &i);

    while (i != 0) {
        if (head == NULL) {
            head = malloc(sizeof(ListNode));
            temp = head;
        }

        else {
            temp -> next = malloc(sizeof(ListNode));
            temp = temp -> next; // what is this for?
        }

        temp -> item = i;
        
        printf("insert value: ");
        scanf("%d", &i);
    }
    
    temp -> next = NULL;

    // printlist(head);
    
    // PRINT NODE AT INDEX 2 (3RD NODE)
    // ListNode *index_node = FindNode(head, 2);
    // if (index_node != NULL) {
    //     printf("%d", index_node -> item);
    // } else {
    //     printf("Node does not exist");
    // }
}