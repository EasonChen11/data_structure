/*** checking if the parentheses "{}, [], ()" match or not  ***/
/*** the stack storage allocated by newStack() ***/
/*** more compact if-else ***/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // stack size

typedef char dType;

struct storage {
	dType * data;//data is a pointer not list
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
int empty(skType *);

	
int main(void)
{
	char buff[50];
	int i;
	skType * S = newStack();

	printf("Please enter an experession: ");
	scanf("%s", buff);
	printf("This is what entered: %s\n", buff);

	for (i=0; buff[i] != '\0'; ++i) {
		if (buff[i] == '{' || buff[i] == '[' || buff[i] == '(')//if the operator is open"{[("
			push (S, buff[i]);//we put the operator to the stack
		else //if the input is other thing we will skip until the operator is close"}])"
			if (buff[i] == '}' && pop (S) != '{') break;//check the operator match
			else if (buff[i] == ']' && pop (S) != '[') break;
			else if (buff[i] == ')' && pop (S) != '(') break;
	}//the top operator should be matching if input operator can't match together is error
    //the operator we put before later to match. So,we use stack to save the operator
	if (empty(S))
		printf("All matched.\n");
	else
		printf("Unmatch with %c.\n", buff[i]);


	delStack(&S);

}

skType * newStack(void)
{
	skType * s;
	s = malloc (sizeof(skType));//create new node
	s->stack = malloc (sizeof(struct storage));//create data first node
	s->stack->data = malloc (sizeof(dType)*SIZE);//create data memory
	for (int i; i<SIZE; i++)
		s->stack->data[i] = '\0'; // initialize 
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
	return getData (s->stack, s->count);//get data which in the least node
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

int empty(skType * s)//check the stack whether the stack is empty
{
	if (s->count == 0) return 1;
	else return 0;
}
