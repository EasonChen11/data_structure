/** This program is perform the basic operations of a queue. **/
/** The storage uses a linked list of integers. **/

#include <stdio.h>
#include <stdlib.h>

typedef int dType;

typedef struct storage {
	dType data;
	struct storage * next;
} stType;  // storage type

typedef struct Q {//contain first node, least node and how many node in the link list
	stType * front;
	stType * rear;
	int Count;        // number of items in Q
} QType;

void enQ (QType *, dType);
dType deQ (QType *);
QType * newQ (void);
int emptyQ (QType *);

void setData (stType *, dType);
dType getData (stType **);

int main(void)
{
	QType *Q1;

	Q1 = newQ ();
	enQ (Q1, 10);//put data in the queue
	enQ (Q1, 20);
	enQ (Q1, 30);
	printf("%d\n", deQ(Q1));
	printf("%d\n", deQ(Q1));
	printf("%d\n", deQ(Q1));
}

QType * newQ (void)//create a new queue and initial the front ,rear and count
{
	QType * Q = malloc(sizeof (QType));//create a new node to record front, rear, and count
	Q->front = NULL;
	Q->rear = NULL;
	Q->Count = 0;//have no node
	return Q;
}


void enQ (QType * Q, dType item)//add node
{
	stType * N = malloc(sizeof(stType));//create new node of queue
	setData (N, item);//set information in the node

	if (emptyQ(Q))//if new node is the first node, front = rear
		Q->front = Q->rear = N;
	else {
		Q->rear->next = N;//new node connect the rear node ,rear move to the least node,and front don't move
		Q->rear = Q->rear->next;
	}
	Q->Count += 1;//record add one node
}

dType deQ (QType * Q)//remove the front of queue
{
	dType item;

	if (emptyQ(Q)) return -100000; // incorrect negative number
	else if (Q->Count == 1) {//if queue only have one node, getData function let front be the next node(NULL), and we should set rear be the NULL
		item = getData (&(Q->front));
		Q->rear = NULL;
	}
	else item = getData (&(Q->front));//if queue have more than one node, only set front be the next node(not NULL)
	Q->Count -= 1;//decrease recording quantity

	return item;//return which information we remove
}

int emptyQ (QType * Q)//check the queue if it's empty
{
	if (Q->Count == 0) return 1;//is empty return true
	else return 0;//not empty return false
}

void setData (stType * s, dType data)//set information record in the node
{
	s->data = data;//record the information in the node
	s->next = NULL;//initial node connect
}

dType getData (stType ** s)//git the queue first data and remove the node
{
	dType data;
	stType * p = *s;//save the first node

	data = p->data;//get the information of node
	*s = (*s)->next;//be the next node
	free(p);//free the memory
	return data;//return get information
}
