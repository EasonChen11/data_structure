#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <dbdaoint.h>
//#include <vss.h>

#define WHO_LEN 15
#define WHAT_LEN 20
#define WHEN_LEN 10
#define WHERE_LEN 20

const int month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
struct Time{
    int year;
    int month;
    int day;
    int hour;
    int min;
};
struct information{
    char who[WHO_LEN];
    char what[WHAT_LEN];
    struct Time when;
    char where[WHERE_LEN];
    struct information *next;
};

typedef struct information Record;

char* new_gets(char *str,int limits);
int ReadFromFile(Record ** Book,int *count,char buff[]);


int menu();

void Show(Record * Book);

void Quit(Record * Book,char *);
void Modify (Record *Book, int count);
void EnterRecord(Record ** Book,int *count);

void ViewDay(Record * Book);

void Delete(Record ** Book,int count);

int main (void)
{
    Record * AppBook=NULL;
    char buff[WHEN_LEN];
    int quit = 0, choice,count=0;
    if (ReadFromFile (&AppBook,&count,buff))
        return 0;
    while (! quit) {
        choice = menu(); // get a choice
        switch (choice) { // process according to the choice
            case 1: EnterRecord(&AppBook,&count); break;
            case 2: ViewDay(AppBook); break;
                //case 3: ViewWeek(AppBook); break;
            case 4: Modify(AppBook,count); break;
            case 5: Delete(&AppBook,count); break;
                //case 6: Search(AppBook); break;
            case 7: Show(AppBook);break;
            case 9: Quit(AppBook,buff); quit = 1; break;
            default: printf("Please enter a choice 1-7 or 9 to quit\n");
        }
    }
}

void Delete(Record ** Book,int count) {
    int index=1,search;
    printf("which data should delete:");
    scanf("%d",&search);
    assert(search<=count && search>0);
    Record *before=*Book,*now=*Book;
    while ( index++<search){
        before=now;
        now=now->next;
    }
    if(before==now){
        *Book=now->next;
        free(now);
    }else{
        before->next=now->next;
        free(now);
    }
    printf("After delete data:\n");
    Show(*Book);
}

/*void ViewDay(Record * Book) {
    printf("Enter search Day : ");
    char search_Day[WHEN_LEN];
    int vd =0;
    fgets(search_Day, WHEN_LEN, stdin);
    search_Day[strlen(search_Day)-1]='\0';
    Record *day_data = (Record*) malloc(sizeof (Record)),*first_data,*before;
    first_data = day_data;
    before = day_data;
    while (Book){
        if(strcmp(Book->when, search_Day)==0){
            vd++;
            strcpy(day_data->who, Book->who);
            strcpy(day_data->what, Book->what);
            strcpy(day_data->when, Book->when);
            strcpy(day_data->where, Book->where);
            day_data->next = (Record*) malloc(sizeof (Record));
            before = day_data;
            day_data = day_data->next;
        }
        Book = Book->next;
    }
    before->next = NULL;
    free(day_data);
    if(!vd){
        printf("Don't have data!\n");
    } else{

        printf("Data : \n");
        Show(first_data);
    }
}*/
void Modify (Record *Book, int count)
{
    printf("\nModify -- to modify a record\n");
}

void EnterRecord(Record ** Book,int *count) {
    Record *save=(Record*) malloc(sizeof (Record));
    new_gets(save->who, WHO_LEN);
    printf("Please enter name : ");
    fgets(save->who, WHO_LEN, stdin);
    save->who[strlen(save->who)-1]='\0';
    printf("Please enter thing : ");
    fgets(save->what, WHAT_LEN, stdin);
    save->what[strlen(save->what)-1]='\0';
    printf("Please enter time : ");
    scanf("%d %d %d %d %d",&save->when.year,&save->when.month, &save->when.day,&save->when.hour,&save->when.min);
    printf("Please enter location : ");
    fgets(save->where, WHERE_LEN, stdin);
    save->where[strlen(save->where)-1]='\0';
    save->next = NULL;
    if (*Book == NULL){
        *Book=save;
    }else{
        Record *now=*Book;
        while(now->next){
            now=now->next;
        }
        now->next = (Record*) malloc(sizeof (Record));
        save=save->next;
        save->next=NULL;
    }
}

void Quit(Record * Book, char buff[]) {
    FILE *output;
    printf("ReadFromFile -- ask the file name from user");
    printf(" and process the file\n");

    printf("Please enter a absolute path of file to open/save: ");
    scanf("%s", buff);
    //strcpy(buff , "C:\\Users\\ysche\\Desktop\\Appointment Book list/data.txt\0");
    printf("Opening file: %s ....\n", buff);
    if( (output = fopen(buff,"r")) == NULL){
        fclose(output);
        return;
    }
    Record *before;
    while (Book != NULL){
        fprintf(output, "%s\n", Book->who);
        fprintf(output, "%s\n", Book->what);
        fprintf(output, "%d %d %d %d %d\n",Book->when.year,Book->when.month, Book->when.day,Book->when.hour,Book->when.min);
        fprintf(output, "%s\n", Book->where);
        before = Book;
        Book = Book->next;
        free(before);
    }
    printf("Cancel!\n");
    fclose(output);
}

void Show(Record * Book) {
    int i=1;
    while (Book != NULL){
        printf("name\t\tthing\t\ttime\t\tlocation\n");
        printf("%d.%s\t", i++,Book->who);
        printf("%s\t", Book->what);
        printf("%d %d %d %d %d\t",Book->when.year,Book->when.month, Book->when.day,Book->when.hour,Book->when.min);
        printf("%s\n", Book->where);
        Book = Book->next;
    }
}

int menu() {
    //printf("1.EnterRecord, 2.ViewDay, 3.ViewWeek, 4.Modify, 5.Delete, 6.Search, 7.Show, 9.Quit: ");
    printf("***************************************\n");
    printf("*      Appointment Book Services      *\n");
    printf("*      -------------------------      *\n");
    printf("*   1. Enter Record       4. Modify   *\n");
    printf("*   2. View Day           5. Delete   *\n");
    printf("*   3. View Week          6. Search   *\n");
    printf("*   7. Show               9. Quit     *\n");
    printf("***************************************\n");
    printf("\nPlease enter a choice:");int i;
    scanf("%d",&i);
    getchar();
    return i;
}

int ReadFromFile(Record ** Book,int *count, char buff[]) {
    FILE * input;
    printf("ReadFromFile -- ask the file name from user");
    printf(" and process the file\n");

    printf("Please enter a absolute path of file to open/save: ");
    scanf("%s", buff);
    //strcpy(buff , "C:\\Users\\ysche\\Desktop\\Appointment Book list/data.txt\0");
    printf("Opening file: %s ....\n", buff);
    input = fopen(buff,"r");
    if (input==NULL){
        printf("Error\n");
        fclose(input);
        return 1;
    }
    printf("Read file ...");
    char save_data[WHO_LEN];
    Record *save=(Record*) malloc(sizeof(Record));;
    if(fgets(save_data, WHO_LEN, input)!= NULL){
        strcpy(save->who, save_data);
        save->who[strlen(save->who)-1]='\0';
        fgets(save->what, WHAT_LEN, input);
        save->what[strlen(save->what)-1]='\0';
        fscanf(input,"%d %d %d %d %d",&save->when.year,&save->when.month, &save->when.day,&save->when.hour,&save->when.min);
        fgets(save->where, WHERE_LEN, input);
        save->where[strlen(save->where)-1]='\0';
        save->next = NULL;
        *Book=save;
        *count++;
    } else{
        return 0;
    }
    while (fgets(save_data, WHO_LEN, input) != NULL) {
        save->next = (Record*) malloc(sizeof (Record));
        save = save->next;
        strcpy(save->who, save_data);
        save->who[strlen(save->who)-1]='\0';
        fgets(save->what, WHAT_LEN, input);
        save->what[strlen(save->what)-1]='\0';
        fscanf(input,"%d %d %d %d %d",&save->when.year,&save->when.month, &save->when.day,&save->when.hour,&save->when.min);
        fgets(save->where, WHERE_LEN, input);
        save->where[strlen(save->where)-1]='\0';
        save->next = NULL;
        *count++;
    }
    fclose(input);
    printf("finish\n");
    return 0;
}

char* new_gets(char *str,int limits){
    gets(str);
    assert(strlen(str)>=limits);
    return str;
}