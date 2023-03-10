 ////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////


typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;

} BTNode;

////////////////////////////////////////////////////////////////////


void mirrorTree(BTNode *node);

void printSmallerValues(BTNode *node, int m);
int smallestValue(BTNode *node);
int hasGreatGrandchild(BTNode *node);

void printTree_InOrder(BTNode *node);

////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]){

	int i;
	BTNode *root, *root2;
	BTNode btn[15];

	// Create the tree in Q1
	// Using manual dynamic allocation of memory for BTNodes

	root = malloc(sizeof(BTNode));
	root->item = 4;

	root->left = malloc(sizeof(BTNode));
	root->left->item = 5;

	root->right = malloc(sizeof(BTNode));
	root->right->item = 2;

	root->left->left = NULL;

	root->left->right = malloc(sizeof(BTNode));
	root->left->right->item = 6;

	root->left->right->left = NULL;
	root->left->right->right = NULL;

	root->right->left = malloc(sizeof(BTNode));
	root->right->left->item = 3;

	root->right->right = malloc(sizeof(BTNode));
	root->right->right->item = 1;

	root->right->left->left = NULL;

	root->right->left->right = NULL;

	root->right->right->left = NULL;

	root->right->right->right = NULL;

	printTree_InOrder(root);
	printf("\n");
	mirrorTree(root);
	printTree_InOrder(root);
	printf("\n\n");

	//question 2
	printf("input m for question 2: ");
	scanf("%d", &i);
	printf("the values smaller than %d are: ", i);
	printSmallerValues(root, i);
	printf("\n\n");

	//question 3
	printf("The smallest value in the tree is: %d", smallestValue(root));
	printf("\n\n");

	//question 4
	// Create a tree for Q4: Tall enough so some nodes have great-grandchildren
	// Use array of BTNodes, create tree by linking nodes together
	for (i = 0; i <= 6; i++){
		btn[i].item = i;
		btn[i].left = &(btn[i * 2 + 1]);
		btn[i].right = &(btn[i * 2 + 2]);
	}

	for (i = 7; i <= 14; i++){
		btn[i].item = i;
		btn[i].left = NULL;
		btn[i].right = NULL;
	}
	root2 = &btn[0];

	printf("The tree for question 4 visited by in-order is \n");
	printTree_InOrder(root2);
	printf("\nthe values stored in all nodes of the tree that have at least one great-grandchild are: ");

	hasGreatGrandchild(root2);

	return 0;
}

void mirrorTree(BTNode *node){

	// write your code here
	if (node == NULL) {
		return;
	}

	BTNode *t = node -> left;
	node -> left = node -> right;
	node -> right = t;

	if (node -> left) {
		mirrorTree(node -> left);
	}

	if (node -> right) {
		mirrorTree(node -> right);
	}

	return;
}

int hasGreatGrandchild(BTNode *node){

	// write your code here
	if (node == NULL) {
		return 0;
	}

	int l = hasGreatGrandchild(node -> left);
	int R = hasGreatGrandchild(node -> right);

	if (l >= 3 || R >= 3) {
		printf("%d ", node -> item);
	}

	if (l > R) {
		return l + 1;
	} else {
		return R + 1;
	}

}

void printSmallerValues(BTNode *node, int m){

	// write your code here
	if (node == NULL) {
		return;
	}

	if ((node -> item) < m) {
		printf("%d ", node -> item);
	}

	if (node -> left) {
		printSmallerValues(node -> left, m);
	}

	if (node -> right) {
		printSmallerValues(node -> right, m);
	}

	return;
}

int smallestValue(BTNode *node) {
	int l, r;
	int smallest = node -> item;
	// write your code here
	if (node -> left) {
		l = smallestValue(node -> left);
	}

	if (node -> right) {
		r = smallestValue(node -> right);
	}

	if (smallest > l) smallest = l;
	if (smallest > r) smallest = r;

	return smallest;
}


//////////////////////////////////////////////////////////////////

void printTree_InOrder(BTNode *node){

	if (node == NULL) return;
	printTree_InOrder(node->left);
	printf("%d ", node->item);
	printTree_InOrder(node->right);
	return;
}
