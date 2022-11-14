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
#include <string.h>
#define timeNeeded 3  // time needed to process an item
#define max(a, b) a>b?a:b
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
    int openTime;   //open for next item can deal with
} QType;

QType * newQ (void);
void enQ (QType *, dType *);
dType * deQ (QType *);
int emptyQ (QType *);

void setData (stType *, dType *);
dType * getData (stType **);

void organize (stType **, char *);
void prResult (QType *, QType *);

int main(void)
{
    int now=0;
    char filename[20];
    stType * L1 = NULL, * P;
    dType * itemP;
    QType * Q1, *Q2;

    printf("Please enter the name of data file: ");
    scanf("%s", filename);
    strcpy(filename,"inputA.txt");
    organize (&L1, filename); // getting data in a linked list

    Q1 = newQ ();//initial queue
    Q2 = newQ ();//initial queue

    P = L1;
    while (P != NULL || ! emptyQ(Q1) || !emptyQ(Q2)) {//if link list isn't at least or two queues aren't empty
        while (P != NULL && P->data->arrTime <= now) {//if the item's arrival time is before now, push into queue
            if (Q1->Count <= Q2->Count)
                enQ(Q1, P->data);//push into queue
            else enQ(Q2, P->data);
            P = P->next;
        }
        if (!emptyQ(Q1) && Q1->openTime<=now) {
            itemP = deQ(Q1);//pop the item out to queue
            Q1->ttlWaitTime += (now - itemP->arrTime);//wait time is the item arrival time until the item is used
            Q1->ttlProcessed += 1;//deal with one item
            Q1->openTime = now + timeNeeded;//now time will pass the time of deal with one item need times
        }
        if (!emptyQ(Q2) && Q2->openTime<=now) {
            itemP = deQ(Q2);//pop the item out to queue
            Q2->ttlWaitTime += (now - itemP->arrTime);//wait time is the item arrival time until the item is used
            Q2->ttlProcessed += 1;//deal with one item
            Q2->openTime = now + timeNeeded;//now time will pass the time of deal with one item need times
        }
        now++;//if no item in the queue pass to the next time
    }

    prResult (Q1, Q2);//print result
}

QType * newQ (void)//create the queue and initial the value of queue
{
    QType * Q = malloc(sizeof (QType));
    Q->front = NULL;
    Q->rear = NULL;
    Q->ttlProcessed = 0;
    Q->ttlWaitTime = 0;
    Q->Count = 0;
    Q->maxCount = 0;
    Q->openTime=0;
    return Q;
}


void enQ (QType * Q, dType * item)//push the data in to the queue
{
    stType * N = malloc(sizeof(stType));
    setData (N, item);//put the data into the node

    if (emptyQ(Q))//if queue is empty, front and rear equal to the save value
        Q->front = Q->rear = N;
    else {
        Q->rear->next = N;//node connect to the least of link list, and rear will be the next node of link list
        Q->rear = Q->rear->next;
    }
    Q->Count += 1;//number of node in the queue increase
    if (Q->Count > Q->maxCount)    // update largest number of waiting
        Q->maxCount = Q->Count;
}


dType * deQ (QType * Q)//pop the first node of the queue and return its value
{
    dType * item;

    if (emptyQ(Q)) return NULL;//check the queue whether is empty
    else if (Q->Count == 1) {//if only have one node, rear will be the NULL
        item = getData (&(Q->front));
        Q->rear = NULL;
    }
    else item = getData (&(Q->front));//have more than one node, only front be the next, rear don't change
    Q->Count -= 1;//number of node in the queue decrease

    return item;
}

int emptyQ (QType * Q)//check queue whether is empty.
{
    if (Q->Count == 0) return 1;//is empty return true
    else return 0;//else return false
}

void setData (stType * s, dType * data)//link the data into the node
{
    s->data = data;
    s->next = NULL;//initial the data next link
}

dType * getData (stType ** s)//get the front data, front move to next node and remove the before front
{
    /*why call by address? We call the Q->front into the function. When we want to change the value about front,
  we should change Q->front value, but we only call the front value, it can't change the vale of the Q.
  So, we need call by address to change the global value which will change in the function.*/
    dType * data;
    stType * p = *s;

    data = p->data;//get the front data
    *s = (*s)->next;//front be the next
    free(p);//free the before front
    return data;
}

void organize (stType **L, char * fname)//read the file get the data into the link list
{
    FILE *fp;
    int i;
    stType * P, *N;
    //printf("%s\n",fname);
    fp = fopen(fname, "r");//open the file
    printf("open file %s\n",fname);
    *L = malloc (sizeof (stType));
    (*L)->data = malloc (sizeof (dType));//first node connect
    fscanf (fp, "%d%d", &((*L)->data->id),&((*L)->data->arrTime));
    (*L)->next = NULL;

    N = malloc (sizeof (stType));//create another node
    N->data = malloc (sizeof (dType));
    N->next = NULL;

    P = *L;
    while (fscanf (fp, "%d%d", &(N->data->id),&(N->data->arrTime))//read from file until EOF
           != EOF){
        P->next = N;
        P = P->next;//got to next node
        N = malloc (sizeof (dType));
        N->data = malloc (sizeof (dType));//create another node
        N->next = NULL;
    }
    free(N->data);
    free(N);//free the save memory

    fclose(fp);//close the file
}

void prResult (QType * Q1, QType *Q2)//print result of the total processed,total waiting times, number of maximum waiting items and average of waiting times
{
    printf("Totally %d items processed\n", Q1->ttlProcessed+Q2->ttlProcessed);
    printf("Totally waiting time: %d \n", Q1->ttlWaitTime+Q1->ttlWaitTime);
    printf("Maximum number of items at one time %d \n", max(Q1->maxCount,Q2->maxCount));
    printf("Average waiting time: %4.2f \n", ((Q1->ttlWaitTime+Q2->ttlWaitTime)*1.0)/(Q1->ttlProcessed+Q2->ttlProcessed));
}

