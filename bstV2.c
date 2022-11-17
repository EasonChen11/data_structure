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
bstType * getData (int, FILE *);

int main(void)
{
	bstType * tree, * data;
	int phone;
	FILE *fp = fopen("test.txt", "r");

	tree = NULL;

	while ( fscanf(fp, "%d", &phone) != EOF ) {
		data = getData(phone, fp);
		insert (&tree, data);
	}

	printf("Please enter a phone number to search: ");
	scanf("%d", &phone);
	search (tree, phone);

	printf("Performing Inorder Traversal ... \n");
	inorder (tree);

	fclose(fp);
}

bstType * getData (int phone, FILE * fp)
{
	bstType * data = malloc(sizeof(bstType));
	data->left = data->right = NULL;

	data->phone = phone;
	fscanf(fp, "%s", data->room);
	fscanf(fp, "%s", data->fname);
	fscanf(fp, "%s", data->lname);

	return data;
}

void insert (bstType ** t, bstType * data)
{
	if (*t == NULL) 
		*t = data;
	else
		if ((*t)->phone > data->phone)
			insert (&((*t)->left), data);
		else insert(&((*t)->right), data);
}

void search (bstType * t, int key)
{
	if (t == NULL)
		printf("Empty!\n");
	else if (t->phone == key) {
		printf("Phone: %d\n", key);
		printf("Room: %s\n", t->room);
		printf("Name: %s %s\n", t->fname, t->lname);
		printf("Room: %s\n", t->room);
	}
	else 
		if (t->phone > key) 
			search (t->left, key);
		else search (t->right, key);
}

void inorder (bstType * t)
{
	if (t != NULL) {
		inorder(t->left);
		printf("Phone: %d\n", t->phone);
		printf("Room: %s\n", t->room);
		printf("Name: %s %s\n", t->fname, t->lname);
		inorder(t->right);
	}
}

