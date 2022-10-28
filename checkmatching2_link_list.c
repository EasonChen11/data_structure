/*** checking if the parentheses "{}, [], ()" match or not  ***/
/*** the stack storage allocated by newStack() ***/
/*** more compact if-else ***/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // stack size

typedef char dType;

struct storage {
	dType  data;//data is a pointer not list
    struct storage *next;
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
void setData (skType *, dType);
dType getData (struct storage *);
int empty(skType *);
dType removenode(skType * s);

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

skType * newStack(void)//create new stack
{
	skType * s;
	s = malloc (sizeof(skType));//create new node
	s->stack = NULL;//create data first node initialize
	s->count = 0;
	return s;
}

int push (skType * s, dType data)//put the data in the stack
{
	if (s->count >= SIZE)
		return 0; // full
	setData (s,  data);//set data in the stack
	s->count++;//size+1
	return 1;
}

dType pop (skType * s)//remove data
{
	if (s->count == 0)
		return 0; // empty
	s->count--;//size-1
	return removenode (s);//remove first node
}

dType removenode(skType * s) {//remove first node
    struct storage *first_node=s->stack;
    dType first_data=first_node->data;//save first node data
    s->stack=first_node->next;
    free(first_node);//free the first node memory
    return first_data;
}

dType top (skType * s)//return the top data
{
	return getData(s->stack);
}

void delStack(skType ** s)//free the memory to the computer memory
{
    struct storage *del_node;
    while((*s)->stack){//step by step remove node
        del_node = (*s)->stack;
        (*s)->stack=del_node->next;
	    free(del_node);
    }
	free((*s)->stack);
	free(*s);
	*s = NULL;
}

void setData (skType * s, dType data)//put data in the node
{
    struct storage *save= malloc(sizeof(struct storage));//create a node
    save->data=data;//Store the item to the node
    save->next=s->stack;
    s->stack=save;//link at first
}

dType getData (struct storage * s)//return we give the index of data
{
	return s->data;
}

int empty(skType * s)//check the stack whether the stack is empty
{
	if (s->count == 0) return 1;
	else return 0;
}
