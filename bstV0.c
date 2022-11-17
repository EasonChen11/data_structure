/*** constructing a BST
     integers from keyboard
***/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int phone;
	struct node *left;//storage left node located
	struct node *right;//storage right node located
} bstType;

void insert (bstType **, bstType *);
void search (bstType *, int);
void inorder (bstType *);
bstType * createNode (int);

int main(void)
{
	bstType * tree, * data;
	int phone;
	tree = NULL;//the BST is empty

	printf("Please enter a phone number: ");
	scanf("%d", &phone);
	while (phone != 0) {//if user input phone number is 0, quit the record
		data = createNode(phone);
		insert (&tree, data);//put the data into the BST
		printf("Please enter a phone number: ");
		scanf("%d", &phone);
	}

	printf("Please enter a phone number to search: ");
	scanf("%d", &phone);
	search (tree, phone);//to find the keyword

	printf("Performing Inorder Traversal ... \n");
	inorder (tree);//print the data with inorder traversal
}

bstType * createNode (int phone)//initialize node data
{
	bstType * data = malloc(sizeof(bstType));//ask memory
	data->left = data->right = NULL;//left and right are empty
	data->phone = phone;//storage phone number

	return data;
}

void insert (bstType ** t, bstType * data)//put the data into the BST
{
	if (*t == NULL) //if node is empty(can put node there), new data become to the root
		*t = data;
	else
		if ((*t)->phone > data->phone)//new data smaller than root's data
			insert (&((*t)->left), data);//go to left to find the save legal place
		else insert(&((*t)->right), data);//go to right to find the save legal place
}

void search (bstType * t, int key)//check the key in the BST
{
	if (t == NULL)//not found the key
		printf("Empty!\n");
	else if (t->phone == key) //find the key
		printf("Phone: %d\n", key);
	else 
		if (t->phone > key) //left data smaller than root's data
			search (t->left, key);//go to left node
		else search (t->right, key);//go to right node
}

void inorder (bstType * t)//left->root->right
{
	if (t != NULL) {//not at the end of leaf
		inorder(t->left);//go to left node
		printf("Phone: %d\n", t->phone);//if at the end of left leaf, print the phone number
		inorder(t->right);//go to right node
	}
}

