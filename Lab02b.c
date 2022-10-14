//
// Created by Eason chen on 2022/10/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define filename_size 20
#define name_size 20
struct PhoneBook{
    int phone_number;
    char name[name_size];
    struct PhoneBook *next;
};
typedef struct PhoneBook pb_type;

int readfile(pb_type ** normal_list_head,pb_type ** ascending_order_list_head,char *filename);

void AddData_to_Normal_List(pb_type **ascending_order_list_head,int input_phone_number,char username[]);

void AddData_to_Ascending_order_List(pb_type **ascending_order_list_head,int input_phone_number,char username[]);

void printScore(pb_type *head);

int main(){
    char filename[filename_size];
    int finish;
    pb_type *normal_list=NULL,*ascending_order_list=NULL;//two link lists save the data
    finish=readfile(&normal_list,&ascending_order_list,filename);
    finish?printf("close %s\nfinish!\n",filename): printf("%s can't open\n",filename);
}

int readfile(pb_type ** normal_list_head,pb_type ** ascending_order_list_head,char *filename) {//read data
    FILE *fp;
    printf("Please enter the file name to open:(example:./data.txt)");
    //fgets(filename, filename_size,stdin);
    scanf("%s",filename);//read input filename
    rewind(stdin);//clear
    assert(strlen(filename)<filename_size);//check the filename size legitimate
    if( (fp = fopen(filename,"r")) == NULL){//check open file legitimate
        fclose(fp);
        printf("cancel\n");
        return 0;
    }
    printf("read file:%s\n",filename);
    int input_phone_number;
    char username[name_size];
    while ( fscanf(fp, "%d",&input_phone_number)!=EOF){//check the file whether is ending
        fscanf(fp,"%s",username);//get user's name
        assert(strlen(username)<name_size);//check username is legitimate
        //fgets(username,name_size,fp);//fgets will read the space before the username
        rewind(stdin);//clear
        AddData_to_Normal_List(normal_list_head,input_phone_number,username);//add data in the according to the order of appearance link list
        AddData_to_Ascending_order_List(ascending_order_list_head,input_phone_number,username);//add data in the ascending order link list
    }
    fclose(fp);//close the file
    printf("order of appearance list:\n");
    printScore(*normal_list_head);
    printf("ascending order list:\n");
    printScore(*ascending_order_list_head);
    return 1;
}

void AddData_to_Normal_List(pb_type **ascending_order_list_head,int input_phone_number,char username[])//add data in the according to the order of appearance link list
{
    pb_type *save= (pb_type*)malloc(sizeof (pb_type));//create a node
    save->phone_number=input_phone_number;
    strcpy(save->name,username);
    save->next=NULL;
    if(*ascending_order_list_head==NULL){//first is NULL
        *ascending_order_list_head=save;
        return;
    }
    pb_type *now=(*ascending_order_list_head);
    while (now->next){//find the node that is last
        now=now->next;
    }
    now->next=save;//connect the node
}

void AddData_to_Ascending_order_List(pb_type **ascending_order_list_head,int input_phone_number,char username[])//add data in the ascending order link list
{
    pb_type *save= (pb_type*)malloc(sizeof (pb_type));//create a node
    save->phone_number=input_phone_number;
    strcpy(save->name,username);
    save->next=NULL;
    if(*ascending_order_list_head==NULL){//first is NULL
        *ascending_order_list_head=save;
        return;
    }
    if(save->phone_number < (*ascending_order_list_head)->phone_number){//phone number is smallest
        save->next=*ascending_order_list_head;
        *ascending_order_list_head=save;
        return;
    }
    pb_type *now=(*ascending_order_list_head)->next,*before=*ascending_order_list_head;
    while (now){//find the node's phone number bigger than input phone number
        if(save->phone_number < now->phone_number){
            before->next=save;
            save->next=now;
            return;
        }
        before=now;
        now=now->next;
    }
    before->next=save;//connect the node
}
void printScore(pb_type *head){//print the data on the screen
    printf("phone numbers\tnames\n");
    while (head){
        printf("%d\t\t%s\n",head->phone_number,head->name);
        head=head->next;
    }
    printf("\n");
}