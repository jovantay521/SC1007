////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _listnode{
	int num;
	struct _listnode *next;
} ListNode;
typedef struct _linkedlist{
	ListNode *head;
	int size;
} LinkedList;
typedef struct _dbllistnode{
	int num;
	struct _dbllistnode *pre;
	struct _dbllistnode *next;
} DblListNode;

////////////////////////////////////////////////////////////////////
////////////
int removeNode(ListNode **ptrHead, int index);
int removeNode2(LinkedList *ll, int index);
int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList);
int duplicateReverse(ListNode *head, ListNode **ptrNewHead);

void printList(ListNode *head);
ListNode * findNode(ListNode *head, int index);
int insertNode(ListNode **ptrHead, int index, int value);


// these are for the practice questions
int moveMaxToFront(ListNode **ptrHead);
int concatenate(ListNode **ptrHead1, ListNode *head2);
int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2);
int insertDbl(DblListNode **ptrHead, int index, int value);
void printDblList(DblListNode *head);

////////////////////////////////////////////////////////////////////
////////////

int main()
{
	int i;
	ListNode *head = NULL;
	ListNode *dupRevHead = NULL;
	ListNode *oddHead = NULL;
	ListNode *evenHead = NULL;
	ListNode *list1Head = NULL, *list2Head = NULL;
	ListNode *combAltHead = NULL;
	DblListNode *dblHead = NULL;
	LinkedList llist;
	int size = 0;

	//build a linked list
	if (insertNode(&head, 0, 6) == 0) size++;
	if (insertNode(&head, 0, 4) == 0) size++;
	if (insertNode(&head, 0, 2) == 0) size++;
	printf("After inserting 3 values.");
	printList(head);


	//removeNode(): question 1
	if (removeNode(&head, 3) == 0) size--;//this one can't be removed.
	if (removeNode(&head, 1) == 0) size--;
	if (removeNode(&head, 0) == 0) size--;

	printf("\nafter remove using removeNode(), ");
	printList(head);

	//insert some nodes
	if (insertNode(&head, 2, 3) == 0) size++; // this one can't be inserted.
	if (insertNode(&head, 1, 1) == 0) size++;
	if (insertNode(&head, 0, 0) == 0) size++;

	printf("\nafter insert, ");
	printList(head);

	// //removeNode2(): question 2
	llist.head = head;
	llist.size = size;
	removeNode2(&llist, 2);
	removeNode2(&llist, 0);
	removeNode2(&llist, 0);
	head = llist.head;


	printf("\nafter remove using removeNode2(), ");
	printList(llist.head);
	// empty linked list now

	//split(): question 3
	for (i = 1; i <10; i++)//build a new linked list
		insertNode(&head, 0, i);
	printf("\n\ninsert 1-9 to the linked list,");
	printList(head);
	printf("split the current list, results:\n");
	split(head, &evenHead, &oddHead);
	printf("the even list");
	printList(evenHead);
	printf("the odd list");
	printList(oddHead);

	//duplicateReverse(): question 4
	printf("\n");
	printList(head);
	duplicateReverse(head, &dupRevHead);
	printf("After duplicateReverse(),");
	printList(dupRevHead);

	////////////////////////////////////////////////////////////////////////
	//the following are for the PRACTICE QUESTIONS

	printf("\n\nNow for the practice questions");

	//1.moveMaxToFront()
	printf("\n************** moveMaxToFront *******************\n");
	printList(dupRevHead);
	moveMaxToFront(&dupRevHead);
	printf("after moveMaxToFront()");
	printList(dupRevHead);

	//2. concatenate()
	printf("\n************** concatenate() *******************\n");
	concatenate(&head, dupRevHead);
	printf("concatenate(current list, duplicate reverse list)\n  ");
	printList(head);

	//3.combineAlternating()
	printf("\n************** combineAlternating() *******************\n");
	for (i = 3; i > 0; i--)				//build linked list 1
		insertNode(&list1Head, 0, i);
	for (i = 13; i > 10; i--)			//build linked list 2
		insertNode(&list2Head, 0, i);
	printf("List 1:");
	printList(list1Head);
	printf("List 2: ");
	printList(list2Head);
	combineAlternating(&combAltHead, list1Head, list2Head);
	printf("After combineAlternating(): ");
	printList(combAltHead);

	//4. insertDbl()
	printf("\n************** insertDbl() *******************\n");
	printf("insertDbl()\nDoubly-linked list: ");
	insertDbl(&dblHead, 0, 10);
	insertDbl(&dblHead, 0, 20);
	insertDbl(&dblHead, 1, 30);
	insertDbl(&dblHead, 2, 40);
	printDblList(dblHead);
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

void printList(ListNode *head){
	ListNode *cur = head;

	if (cur == NULL)
		return;

	printf("the current linked list is:\n");
	while (cur != NULL){
		printf("%d ", cur->num);
		cur = cur->next;
	}
	printf("\n");
}

void printDblList(DblListNode *head){
	if (head == NULL) return;
	while (head != NULL){
		printf("%d ", head->num);
		head = head->next;
	}
	printf("\n");
}

ListNode * findNode(ListNode *head, int index){
	if (head == NULL || index < 0) return NULL;
	while (index > 0){
		head = head->next;
		if (head == NULL)
			return NULL;
		index--;
	}
	return head;
}


int insertNode(ListNode **ptrHead, int index, int value){
	ListNode *pre, *cur;
	// If empty list or inserting first node, need to update head pointer
	if (*ptrHead == NULL || index == 0){
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(ListNode));
		(*ptrHead)->num = value;
		(*ptrHead)->next = cur;
		return 0;
	}
	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ptrHead, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->num = value;
		pre->next->next = cur;
		return 0;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////
////////////

int removeNode(ListNode **ptrHead, int index){

	// write your code here
	ListNode *pre = findNode(*ptrHead, index - 1), *cur = *ptrHead;

	// sanity check
	if (!*ptrHead) return -1;

	// if head node
	if (index == 0) {
		*ptrHead = cur -> next;
		free(cur);
		return 0;
	}

	// link pre node to next node and free cur node
	if (pre && (cur = pre -> next)) {
		pre -> next = cur -> next;
		free(cur);
		return 0;
	}

}

////////////////////////////////////////////////////////////////////////////////
////////////

int removeNode2(LinkedList *ll, int index) {

	// write your code here

	// sanity check
	if (ll->head == NULL) return -1;

	ListNode *pre, *cur;

	// if first node
	if (index == 0) {
		cur = ll -> head;
		ll -> head = cur -> next;
		ll->size--;
		return 0;
	}
	
	// link previous node and next node
	// free current node and update LL size 
	if ((pre = findNode(ll -> head, index - 1)) && (cur = pre -> next)) {
		pre -> next = cur -> next;
		free(cur);
		ll -> size--;
		return 0;
	}

	return -1;
}





int split(ListNode *head, ListNode **ptrEvenList, ListNode **ptrOddList)
{

	// write your code here
	if (!head) return -1;

	ListNode *cur = head;
	int evensize = 0, oddsize = 0;

	while (cur) {
		if (cur -> num % 2 == 0) {
			insertNode(ptrEvenList, evensize, cur -> num);
			evensize++;
		} else {
			insertNode(ptrOddList, oddsize, cur -> num);
			oddsize++;
		}

		cur = cur -> next;
	}

	return 0;
}

int duplicateReverse(ListNode *head, ListNode **ptrNewHead){

	ListNode *cur=head; 
	// write your code here
	if (cur == NULL) return -1;
	// Simply traverse the list and insert each visited node into the new list at index 0 each time
	while (cur != NULL){

		if (insertNode(ptrNewHead, 0, cur->num) == -1)
			return -1;
		cur = cur ->next;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////
////////////

int moveMaxToFront(ListNode **ptrHead){


	// write your code here
	if (!*ptrHead) return -1;

	ListNode *pre, *cur = *ptrHead, *preMax;
	int max = cur -> num;

	while (cur) {
		if (max < cur -> num) {
			max = cur -> num;
			preMax = pre;
		}

		pre = cur;
		cur = cur -> next;
	}

	if (!preMax) return -1;

	cur = preMax -> next;
	preMax -> next = preMax -> next -> next;
	cur -> next = *ptrHead;
	*ptrHead = cur;

	return 0;
}


int concatenate(ListNode **ptrHead1, ListNode *head2){

	// write your code here
	// sanity check
	if (!*ptrHead1 || !head2) return -1;
	if (!*ptrHead1) *ptrHead1 = head2;
	if (!head2) return 0;

	ListNode *cur1 = *ptrHead1;
	// int index = 0;

	// calculate size of list1
	while (cur1 -> next) {
		cur1 = cur1 -> next;
	}

	cur1 -> next = head2;

	return 0;
}


int combineAlternating(ListNode **ptrHead, ListNode *head1, ListNode *head2){

	// write your code here

	// sanity check
	if (!head1 || !head2) {
		if (!head1) {*ptrHead = head1; return 0;}
		else if (!head2) {*ptrHead = head2; return 0;}
		else return -1;
	}

	ListNode *cur1 = head1, *cur2 = head2;
	int index = 0;
	
	// list1 and list2 not empty
	while (cur1 || cur2) {
		if (cur1) {
			insertNode(ptrHead, index, cur1 -> num);
			index++;
			cur1 = cur1 -> next;
			}
		
		if (cur2) {
			insertNode(ptrHead, index, cur2 -> num);
			index++;
			cur2 = cur2 -> next;
			}
		}

	return 0;
}


int insertDbl(DblListNode **ptrHead, int index, int value){

	// write your code here
	DblListNode *pre, *cur;

	// if empty LL or first node
	if (!*ptrHead || index == 0) {
		cur = *ptrHead;
		*ptrHead = malloc(sizeof(DblListNode));
		(*ptrHead) -> pre = NULL;
		(*ptrHead) -> next = cur;
		(*ptrHead) -> num = value;

		return 0;
	}

	// findnode but DBLL
	pre = *ptrHead;
	while (index > 1) {
		pre = pre -> next;
		index--;
	}

	// insert new node
	if (!pre) {
		cur = pre -> next;
		pre -> next = malloc(sizeof(DblListNode));
		pre -> next -> pre = pre;
		pre -> next -> next = cur;
		pre -> next -> num = value;
		// update cur pre value
		if (cur) cur -> pre = pre -> next;

		return 0;
	}

	// unsuccessful insertion
	return -1;
}


////////////////////////////////////////////////////////////////////
