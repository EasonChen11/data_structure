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

typedef struct storage {
    bstType * data;           // to handle a structure
    struct storage * next;
} stType;  // storage type
typedef struct Q {
    stType * front;
    stType * rear;
    int Count;        // number of items in Q
} QType;

void insert (bstType **, bstType *);
void search (bstType *, int);
void inorder (bstType *);
void preorder (bstType *);
void postorder (bstType *);
bstType * getData (int, FILE *);

void BFS(bstType *);
QType * newQ (void);
void enQ (QType *, bstType *);
void deQ (QType *);
int emptyQ (QType *);
void setData(stType *, bstType *);
stType * frontQ(stType *);

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
    printf("\nPerforming Preorder Traversal ... \n");
    preorder(tree);
    printf("\nPerforming Postorder Traversal ... \n");
    postorder(tree);
    printf("\nPerforming Breadth first traversal ... \n");
    BFS(tree);
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

void preorder (bstType * t)//root->left->right
{
    if (t != NULL) {//not at the end of leaf
        printf("Phone: %d\n", t->phone);//print root's data
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
        preorder(t->left);//go to left node
        preorder(t->right);//go to right node
    }
}

void postorder (bstType * t)//left->right->root
{
    if (t != NULL) {//not at the end of leaf
        preorder(t->left);//go to left node
        preorder(t->right);//go to right node
        printf("Phone: %d\n", t->phone);//print root's data
        printf("Room: %s\n", t->room);
        printf("Name: %s %s\n", t->fname, t->lname);
    }
}

void BFS(bstType * t){
    QType *Q=newQ();
    enQ(Q,t);
    while (!emptyQ(Q)){
        stType * currentPoint=frontQ(Q->front);
        deQ(Q);
        enQ(Q,currentPoint->data->left);
        enQ(Q,currentPoint->data->right);
    }
}

QType * newQ(){
    QType * Q = malloc(sizeof (QType));
    Q->front = NULL;
    Q->rear = NULL;
    Q->Count = 0;
    return Q;
}

void enQ (QType * Q, bstType * item)//push the data in to the queue
{
    if(item==NULL)return;

    stType * N = malloc(sizeof(stType));
    setData (N, item);//put the data into the node

    if (emptyQ(Q))//if queue is empty, front and rear equal to the save value
        Q->front = Q->rear = N;
    else {
        Q->rear->next = N;//node connect to the least of link list, and rear will be the next node of link list
        Q->rear = Q->rear->next;
    }
    Q->Count += 1;//number of node in the queue increase
}

void deQ (QType * Q)//pop the first node of the queue and return its value
{
    if (emptyQ(Q)) return;//check the queue whether is empty
    else if (Q->Count == 1) {//if only have one node, rear will be the NULL
        Q->front=NULL;
        Q->rear = NULL;
    }
    else Q->front=Q->front->next;//have more than one node, only front be the next, rear don't change
    Q->Count -= 1;//number of node in the queue decrease
}

int emptyQ (QType * Q)//check queue whether is empty.
{
    if (Q->Count == 0) return 1;//is empty return true
    else return 0;//else return false
}

void setData (stType * s, bstType * data)//link the data into the node
{
    s->data = data;
    s->next = NULL;//initial the data next link
}

stType * frontQ(stType * s){
    printf("Phone: %d\n", s->data->phone);
    printf("Room: %s\n",  s->data->room);
    printf("Name: %s %s\n",  s->data->fname,  s->data->lname);
    return s;
}