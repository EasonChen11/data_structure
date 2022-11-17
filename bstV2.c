/*** constructing a BST
     data from file: test.txt
     each line: phone, room, first name, last name
***/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int phone;
	char room[10];
	char fname[10];
	char lname[10];
	struct node *left;
	struct node *right;
} bstType;

void insert (bstType **, bstType *);
void search (bstType *, int);
void inorder (bstType *);
void preorder (bstType *);
bstType * getData (int, FILE *);

int main(void)
{
	bstType * tree, * data;
	int phone;
	FILE *fp = fopen("./Lab06/test.txt", "r");//open file

	tree = NULL;

	while ( fscanf(fp, "%d", &phone) != EOF ) {//read file until EOF
		data = getData(phone, fp);
		insert (&tree, data);//add data into tree
	}

	printf("Please enter a phone number to search: ");
	scanf("%d", &phone);//ask user phone number to search
	search (tree, phone);

	printf("Performing Inorder Traversal ... \n");
	inorder (tree);//print inorder traversal
    printf("Performing Preorder Traversal ... \n");
    preorder(tree);
	fclose(fp);//closed file
}

bstType * getData (int phone, FILE * fp)//create new data node and storage phone number, room name and first and least name.
{
	bstType * data = malloc(sizeof(bstType));
	data->left = data->right = NULL;

	data->phone = phone;
	fscanf(fp, "%s", data->room);
	fscanf(fp, "%s", data->fname);
	fscanf(fp, "%s", data->lname);

	return data;
}

void insert (bstType ** t, bstType * data)//put the data node into BST
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
	else if (t->phone == key) {//find the key and print the information in the data
		printf("Phone: %d\n", key);
		printf("Room: %s\n", t->room);
		printf("Name: %s %s\n", t->fname, t->lname);
		printf("Room: %s\n", t->room);
	}
	else 
		if (t->phone > key) //left data smaller than root's data
			search (t->left, key);//go to left node
		else search (t->right, key);//go to right node
}

void inorder (bstType * t)//left->root->right
{
	if (t != NULL) {//not at the end of leaf
		inorder(t->left);//go to left node
		printf("Phone: %d\n", t->phone);//if at the end of left leaf, print the data
		printf("Room: %s\n", t->room);
		printf("Name: %s %s\n", t->fname, t->lname);
		inorder(t->right);//go to right node
	}
}

void preorder (bstType * t)//left->root->right
{
    if (t != NULL) {//not at the end of leaf
        printf("Phone: %d\n", t->phone);//print root's data
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
        preorder(t->left);//go to left node
        preorder(t->right);//go to right node
    }
}