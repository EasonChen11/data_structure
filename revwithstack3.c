/*** INTEGER stack storage space allocated by newStack() ***/
/*** use of printf() in main() ***/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // stack size

typedef int dType;

struct storage {
	dType * data;//char point
};

typedef struct {
	int count;//size of stack
	struct storage * stack;
} skType;

skType * newStack(void);
int push (skType *, dType);
dType pop (skType *);
dType top (skType *);
void delStack(skType **);
void setData (struct storage *, int, dType);
dType getData (struct storage *, int);

	
int main(void)
{
	skType * S;

	S = newStack();

	push (S, 1);//push 1 to the stack
	push (S, 2);//push 2 to the stack
	push (S, 3);//push 3 to the stack

	printf("%d\n", top(S));//print top of the stack

	printf("%d", pop(S));//print top of the stack and remove it
	printf("%d", pop(S));
	printf("%d\n", pop(S));

	delStack(&S);//free the memory

}

skType * newStack(void)
{
	skType * s;
	s = malloc (sizeof(skType));//create new node
	s->stack = malloc (sizeof(struct storage));//create data first node
	s->stack->data = malloc (sizeof(dType)*SIZE);//create data memory
	for (int i; i<SIZE; i++)
		s->stack->data[i] = 0; // initialize 
	s->count = 0;
	return s;
}

int push (skType * s, dType data)//put the data in the stack
{
	if (s->count >= SIZE)
		return 0; // full
	setData (s->stack, s->count, data);//set data in the stack
	s->count++;//size+1
	return 1;
}

dType pop (skType * s)//remove data
{
	if (s->count == 0)
		return 0; // empty
	s->count--;//size-1
	return getData (s->stack, s->count);//return the least data
}

dType top (skType * s)//return the top data
{
	return getData(s->stack, s->count-1);
}

void delStack(skType ** s)//free the memory to the computer memory
{
	free((*s)->stack->data);
	free((*s)->stack);
	free(*s);
	*s = NULL;
}

void setData (struct storage * s, int i, dType data)//put data in the node
{
	s->data[i] = data;
}

dType getData (struct storage * s, int i)//return we give the index of data
{
	return s->data[i];
}

