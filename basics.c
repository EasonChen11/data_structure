/*** stack storage space pre-declared as an array with SIZE ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10 // stack size

typedef char dType;

struct storage {
	dType data[SIZE];
};//data we should save

typedef struct {
	int count;
	struct storage * stack;
} skType;//first node save how many data and first node

skType * newStack(void);
int push (skType *, dType);
dType pop (skType *);
dType top (skType *);
void delStack(skType *);
void setData (struct storage *, int, dType);
dType getData (struct storage *, int);


int main(void)
{
	skType * S = newStack();

	push (S, 'a'); push (S, 'b'); push (S, 'c');

	putchar (top (S)); putchar ('\n');

	putchar (pop (S)); putchar (pop (S)); putchar (pop (S));
	putchar ('\n');

	delStack(S);
//print is "ccba" and the stack will be empty
}

skType * newStack(void)//create new stack
{
	skType * s;
	s = malloc (sizeof(skType));
	s->stack = malloc (sizeof(struct storage));
	strcpy(s->stack->data, ""); // initialize
	s->count = 0;
	return s;
}

int push (skType * s, dType data)//we will put the data in the stack least
{
	if (s->count >= SIZE)
		return 0; // full
	setData (s->stack, s->count, data);//put the data in the stack
	s->count++;//have more node
	return 1;
}

dType pop (skType * s)//we will delete data which is the least in the stack
{
	if (s->count == 0)
		return 0; // empty
	s->count--;//delete node in the stack
	return getData (s->stack, s->count);//get the data which we put it in the stack least
}

dType top (skType * s)
{
	return getData(s->stack, s->count-1);//return the least data in the stack
}

void delStack(skType * s)//free the memory to the computer memory
{
	free(s);
}

void setData (struct storage * s, int i, dType data)
{
	s->data[i] = data;//add node and push the data in to the stack
}

dType getData (struct storage * s, int i)
{
	return s->data[i];//get the data which the index given
}

