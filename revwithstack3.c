/*** INTEGER stack storage space allocated by newStack() ***/
/*** use of printf() in main() ***/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // stack size

typedef int dType;

struct storage {
	dType * data;
};

typedef struct {
	int count;
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
	push (S, 2);
	push (S, 3);

	printf("%d\n", top(S));

	printf("%d", pop(S));
	printf("%d", pop(S));
	printf("%d\n", pop(S));

	delStack(&S);

}

skType * newStack(void)
{
	skType * s;
	s = malloc (sizeof(skType));
	s->stack = malloc (sizeof(struct storage));
	s->stack->data = malloc (sizeof(dType)*SIZE);
	for (int i; i<SIZE; i++)
		s->stack->data[i] = 0; // initialize 
	s->count = 0;
	return s;
}

int push (skType * s, dType data)
{
	if (s->count >= SIZE)
		return 0; // full
	setData (s->stack, s->count, data);
	s->count++;
	return 1;
}

dType pop (skType * s)
{
	if (s->count == 0)
		return 0; // empty
	s->count--;
	return getData (s->stack, s->count);
}

dType top (skType * s)
{
	return getData(s->stack, s->count-1);
}

void delStack(skType ** s)
{
	free((*s)->stack->data);
	free((*s)->stack);
	free(*s);
	*s = NULL;
}

void setData (struct storage * s, int i, dType data)
{
	s->data[i] = data;
}

dType getData (struct storage * s, int i)
{
	return s->data[i];
}

