//410415069
#include <stdio.h>
#include <stdlib.h>
struct BSTnode{
    int number;
    struct BSTnode *left;
    struct BSTnode *right;
};
typedef struct BSTnode BST;
//Q1
BST* readfile();
BST* newnode(int n);
void connect(BST**head,BST*New);
void inorder(BST *bst);

//Q2
int readfileinarray(int heap[]);
void Heapify(int array[],int heap[],int arraySize);
void bottomup(int heap[],int heapindex);
void swap(int *a,int *b);
void printarray(int array[],int size);

int main()
{//Q1
    BST *firstnode=readfile();
    printf("inoder:\n");
    inorder(firstnode);
    printf("\n");
 //Q2
    int array[200],heap[200],arraySize;
    arraySize=readfileinarray(array);
    printf("content of the array:\n");
    printarray(array,arraySize);
    Heapify(array,heap,arraySize);
    printf("heap:\n");
    printarray(heap,arraySize);
    return 0;
}
//Q1
BST* readfile(){
    FILE *fp=fopen("inputA.txt","r");
    int input;
    BST *bst=NULL;
    while(fscanf(fp,"%d",&input)!=EOF){
        BST* New=newnode(input);
        connect(&bst,New);
    }
    fclose(fp);
    return bst;
}
BST* newnode(int n){
    BST *newNode=malloc(sizeof(BST));
    newNode->number=n;
    newNode->left=newNode->right=NULL;
    return newNode;
}
void connect(BST** head,BST* New){
    if(*head==NULL){
        *head=New;
        return;
    }
    if((*head)->number<New->number)connect(&((*head)->right),New);
    else connect(&((*head)->left),New);
}
void inorder(BST *bst){
    if(bst==NULL)return;
    inorder(bst->left);
    printf("%d ",bst->number);
    inorder(bst->right);
}

//Q2
int readfileinarray(int array[]){
    FILE *fp=fopen("inputB.txt","r");
    int index=0;
    while(fscanf(fp,"%d",&array[index++])!=EOF);
    fclose(fp);
    return index-1;
}
void Heapify(int array[],int heap[],int arraySize){
    int i=0;
    while(i<arraySize){
        heap[i]=array[i];
        bottomup(heap,i);
        i++;
    }
}
void bottomup(int heap[],int heapindex){
    while(heapindex!=0){
        if(heap[(heapindex-1)/2]<heap[heapindex]){
            swap(&heap[(heapindex-1)/2],&heap[heapindex]);
            heapindex=(heapindex-1)/2;
        }else break;
    }
}
void swap(int *a,int *b){
    int save=*a;
    *a=*b;
    *b=save;
}
void printarray(int array[],int size){
    int i=0;
    while(i<size){
        printf("%d ",array[i]);
        i++;
    }
    printf("\n");
}

