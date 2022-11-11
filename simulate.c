/** This program simulates the processing of items arriving at different time
    The sample input file is inputA.txt, 
    in which each line represents item ID and arrival time of an item.
    The data is read into a linked list. 
    The simulated time is using the increment of "now" in a loop.
    If the arrival item of an item in the linked list is "now", 
    then it is enqueued.
    The time required to process an item is set as "timeNeeded".
    The simulation stops when there is no more items to process.
    Waiting time and largest number of items in the queue are recorded.
**/

#include <stdio.h>
#include <stdlib.h>

#define timeNeeded 3  // time needed to process an item

typedef struct item {
	int id;
	int arrTime;
} dType;

typedef struct storage {
	dType * data;           // to handle a structure
	struct storage * next;
} stType;  // storage type


typedef struct Q {
	stType * front;
	stType * rear;
	int Count;        // number of items in Q
	int ttlProcessed; // total items processed
	int ttlWaitTime;  // total waiting time
	int maxCount;     // largest number of items waiting
} QType;

QType * newQ (void);
void enQ (QType *, dType *);
dType * deQ (QType *);
int emptyQ (QType *);

void setData (stType *, dType *);
dType * getData (stType **);

void organize (stType **, char *);
void prResult (QType *);

int main(void)
{
	int now=0; 
	char filename[10];
	stType * L1 = NULL, * P;
	dType * itemP;
	QType * Q1;

	printf("Please enter the name of data file: ");
	scanf("%s", filename);

	organize (&L1, filename); // getting data in a linked list

	Q1 = newQ ();

	P = L1;
	while (P != NULL || ! emptyQ(Q1)) {
		while (P != NULL && P->data->arrTime <= now) {
			enQ(Q1, P->data);
			P = P->next;
		}
		if (!emptyQ(Q1)) {
			itemP = deQ(Q1);
			Q1->ttlWaitTime += (now - itemP->arrTime);
			Q1->ttlProcessed += 1;
			now += timeNeeded;
		}
		else now++; 
	}

	prResult (Q1);
}

QType * newQ (void)
{
	QType * Q = malloc(sizeof (QType));
	Q->front = NULL;
	Q->rear = NULL;
	Q->ttlProcessed = 0;
	Q->ttlWaitTime = 0;
	Q->Count = 0;
	Q->maxCount = 0;
	return Q;
}


void enQ (QType * Q, dType * item)
{
	stType * N = malloc(sizeof(stType));
	setData (N, item);

	if (emptyQ(Q))
		Q->front = Q->rear = N;
	else {
		Q->rear->next = N;
		Q->rear = Q->rear->next;
	}
	Q->Count += 1;
	if (Q->Count > Q->maxCount)    // update largest number of waiting
		Q->maxCount = Q->Count;
}


dType * deQ (QType * Q)
{
	dType * item;

	if (emptyQ(Q)) return NULL;
	else if (Q->Count == 1) {
		item = getData (&(Q->front));
		Q->rear = NULL;
	}
	else item = getData (&(Q->front));
	Q->Count -= 1;

	return item;
}

int emptyQ (QType * Q)
{
	if (Q->Count == 0) return 1;
	else return 0;
}

void setData (stType * s, dType * data)
{
	s->data = data;
	s->next = NULL;
}

dType * getData (stType ** s)
{
	dType * data;
	stType * p = *s;

	data = p->data;
	*s = (*s)->next;
	free(p);
	return data;
}

void organize (stType **L, char * fname)
{
	FILE *fp;
	int i;
	stType * P, *N;
    //printf("%s\n",fname);
	fp = fopen(fname, "r");
	
	*L = malloc (sizeof (stType));
	(*L)->data = malloc (sizeof (dType));
	fscanf (fp, "%d%d", &((*L)->data->id),&((*L)->data->arrTime));
	(*L)->next = NULL;

	N = malloc (sizeof (stType));
	N->data = malloc (sizeof (dType));
	N->next = NULL;

	P = *L;
	while (fscanf (fp, "%d%d", &(N->data->id),&(N->data->arrTime)) 
                      != EOF){
		P->next = N;
		P = P->next;
		N = malloc (sizeof (dType));
		N->data = malloc (sizeof (dType));
		N->next = NULL;
	}
	free(N->data);
	free(N);

	fclose(fp);
}
	
void prResult (QType * Q)
{
	printf("Totally %d items processed\n", Q->ttlProcessed);
	printf("Totally waiting time: %d \n", Q->ttlWaitTime);
	printf("Maximum number of items at one time %d \n", Q->maxCount);
	printf("Average waiting time: %4.2f \n", (Q->ttlWaitTime*1.0)/Q->ttlProcessed);
}

