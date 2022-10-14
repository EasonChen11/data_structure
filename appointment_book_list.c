/*** 	This program uses assert() in checking
	whether a certain value is observed.
	This is a way to make sure if your have
	correct values for your variables.
***/

// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WHO_LEN 16
#define WHAT_LEN 21
#define WHEN_LEN 15
#define WHERE_LEN 21
#define MAX_REC 10
#define FILE_NAME_LEN 100
// The record type
typedef struct {
    char who[WHO_LEN];
    char what[WHAT_LEN];
    char when[WHEN_LEN];
    char where[WHERE_LEN];
}Record;

/** These are the function prototypes **/
void new_gets(char* str, int limit);
void ReadFromFile (Record *, int *, char *);
int menu(void);
void EnterRecord (Record *, int *);
void ViewDay (Record [], int);
void ViewWeek (Record *, int);
void Modify (Record *, int);
void Delete (Record *, int *);
void Search (Record *, int);
void Quit (Record *, int, char *);
void Change(Record *,int);
void change(Record book[], int change1, int change2);

void print_data(Record book[],int count);

void ShowDates(Record Book[], int count, char date[]);

// Start of a main program
int main (void)
{
    Record AppBook[MAX_REC];
    int quit = 0, choice, count=0;
    char fileName[FILE_NAME_LEN];

    ReadFromFile (AppBook, &count, fileName);
    printf("%d records read from file\n", count);

    while (! quit) {
        choice = menu();  // get a choice
        switch (choice) { // process according to the choice
            case 1: EnterRecord(AppBook, &count);
                break;
            case 2: ViewDay(AppBook, count);
                break;
            case 3: ViewWeek(AppBook, count);
                break;
            case 4: Modify(AppBook, count);
                break;
            case 5: Delete(AppBook, &count);
                break;
            case 6: Search(AppBook, count);
                break;
            case 7:Change(AppBook, count);
                break;
            case 9: Quit(AppBook, count, fileName);
                quit = 1;
                break;
            default: printf("Please enter a choice 1-6 or 9 to quit\n");
        }
    }
}

void new_gets(char* str, int limit){
    gets(str);//get string
    assert(strlen(str)<limit);//check string don't overflow
    str[strlen(str)] = '\0';//remove '\n'
    rewind(stdin);//clear stdin
}

void ReadFromFile (Record * Book, int * count, char buff[])
{
    FILE * filePointer;
    int i;
    printf("ReadFromFile -- ask the file name from user");
    printf(" and process the file\n");

    printf("Please enter a absolute path of file to open/save: ");
    scanf("%s", buff);
    //strcpy(buff , "C:\\Users\\ysche\\Desktop\\Appointment Book list/data.txt\0");
    printf("Opening file: %s ....\n", buff);
    if( (filePointer = fopen(buff,"r")) == NULL){
        fclose(filePointer);
        return;
    }
    else
        while (fgets(Book[*count].who, WHO_LEN, filePointer) != NULL) {//read after EOF
            Book[*count].who[strlen(Book[*count].who)-1] = '\0';
            fgets(Book[*count].what, WHAT_LEN, filePointer);
            Book[*count].what[strlen(Book[*count].what)-1] = '\0';
            fgets(Book[*count].when, WHEN_LEN, filePointer);
            Book[*count].when[strlen(Book[*count].when)-1] = '\0';
            fgets(Book[*count].where, WHERE_LEN, filePointer);
            Book[*count].where[strlen(Book[*count].where)-1] = '\0';
            (* count) ++ ;
        }
    fclose(filePointer);//close the file
    assert(*count < MAX_REC); // avoid list overflow

// echo print
    print_data(Book, *count);
}

int menu(void)
{
    int pick;
    printf("***************************************\n");
    printf("*      Appointment Book Services      *\n");
    printf("*      -------------------------      *\n");
    printf("*   1. Enter Record       4. Modify   *\n");
    printf("*   2. View Day           5. Delete   *\n");
    printf("*   3. View Week          6. Search   *\n");
    printf("*   7. Change             9. Quit     *\n");
    printf("***************************************\n");
    printf("\nPlease enter a choice:");
    scanf("%d", &pick); // get a choice from the user
    getchar();//get '\n'
    return pick; // pass the value back
}

void EnterRecord (Record Book[], int * count)
{
    printf("\nEnterRecord -- to enter the who/what/when/where\n");
    printf("Please enter WHOM you have an appointment with: <%d",WHO_LEN-1);
    new_gets(Book[*count].who,WHO_LEN);
    printf("Please enter WHAT the event is: <%d",WHAT_LEN-1);
    new_gets(Book[*count].what,WHAT_LEN);
    printf("Please enter WHEN (yyyymmddhhmm): <%d",WHEN_LEN-1);
    new_gets(Book[*count].when,WHEN_LEN);
    printf("Please enter WHERE you have an appointment at: <%d",WHERE_LEN-1);
    new_gets(Book[*count].where,WHERE_LEN);
    printf("there are %d data\n", ++(*count));//read input

    assert(*count < MAX_REC);// avoid list overflow

    print_data(Book,*count);

}

void ViewDay (Record Book[], int count)
{
    char date[WHEN_LEN];
    printf("\nViewDay -- to show the appointments of a given day\n");
    printf("Please enter the day (yyyymmdd) to view: ");
    new_gets(date,WHEN_LEN);
    ShowDates(Book,count,date);
}

void ViewWeek (Record Book [], int count)
{
    char date[WHEN_LEN];
    int i=0;

    printf("\nViewWeek -- to show the appintments of a given week\n");
    printf("Please enter the day (yymmdd) to view: ");
    new_gets(date,WHEN_LEN);
    do {
        ShowDates (Book, count, date);
        date[5] = date[5] + 1;    // increment one day per loop
        if ((date[5] - '0') > 9) {
            date [4] = date[4] + 1;
            date [5] = date[5] - 10;
        }
        ++ i;
    } while (i < 7);   // 7 days to increment
}

void ShowDates(Record Book[], int count, char date[]) {
    int end=1;
    for(int i=0;i<count;i++){
        if (strncmp(date, Book[i].when,strlen(date)) == 0) {//if date = when print data
            printf("%d:\n",i);
            printf("Who: %s\n", Book[i].who);
            printf("What: %s\n", Book[i].what);
            printf("When: %s\n", Book[i].when);
            printf("Where: %s\n", Book[i].where);
            end=0;
        }
    }
    if(end){//if no data match
        printf("%s No data matches the criteria\n",date);
    }

}

void Change(Record Book [], int count){
    printf("\nChange -- to change a record\n");
    int change1,change2;
    printf("enter which two data change\nfirst:");
    scanf("%d",&change1);
    assert(change1<=count);
    printf("second:");
    scanf("%d",&change2);//enter two indexes to change
    assert(change2<=count);
    change(Book,change1-1,change2-1);//change value
    print_data(Book,count);
}

void Modify (Record Book [], int count)
{
    printf("\nModify -- to modify a record\n");
    int change;
    printf("enter which two data modify:");
    scanf("%d",&change);
    assert(change<=count);//enter two indexes to change
    change--;
    rewind(stdin);//clear
    printf("Please enter WHOM you have an appointment with: <%d",WHO_LEN-1);
    new_gets(Book[change].who,WHO_LEN);
    printf("Please enter WHAT the event is: <%d",WHAT_LEN-1);
    new_gets(Book[change].what,WHAT_LEN);
    printf("Please enter WHEN (yyyymmddhhmm): <%d",WHEN_LEN-1);
    new_gets(Book[change].when,WHEN_LEN);
    printf("Please enter WHERE you have an appointment at: <%d",WHERE_LEN-1);
    new_gets(Book[change].where,WHERE_LEN);
    print_data(Book,count);
}

void print_data(Record book[],int count) {//print data
    for(int i=0;i<count;i++){
        printf("%d:\n",i+1);
        printf("Who: %s\n", book[i].who);
        printf("What: %s\n", book[i].what);
        printf("When: %s\n", book[i].when);
        printf("Where: %s\n", book[i].where);
    }
}

void change(Record book[], int change1, int change2) {//change data of list
    Record save;
    save=book[change1];
    book[change1]=book[change2];
    book[change2]=save;
}

void Delete (Record Book [], int * count)
{
    printf("\nDelete --  to delete a record\n");
    printf("enter which data should delete:");
    int index;
    scanf("%d",&index);
    assert(index<=*count);//check index don't overflow
    for(int i=index-1;i<*count-1;i++){//move data forward
        change(Book,i,i+1);
    }
    print_data(Book,--(*count));
}

void Search (Record Book [], int count)
{
    printf("\nSearch --- to search a record by one of when/what/who/where\n");
    printf("which one to search : 1.when\t2.what\t3.who\t4.where :");
    int s;
    scanf("%d",&s);
    char *w;
    assert(s<=count || s==1 || s==2 || s==3 || s==4);//when/what/who/where choice one
    switch (s) {//switch case of 1~4
        case 1:
            w=(char*) malloc(sizeof (char)*WHEN_LEN);
            printf("enter WHEN to search : ");
            new_gets(w,WHEN_LEN);
            for(int i=0;i<count;i++){
                if(strncmp(w,Book[i].when,WHEN_LEN)==0){
                    printf("Who: %s\n", Book[i].who);
                    printf("What: %s\n", Book[i].what);
                    printf("When: %s\n", Book[i].when);
                    printf("Where: %s\n", Book[i].where);
                }
            }
            break;
        case 2:
            w=(char*) malloc(sizeof (char)*WHAT_LEN);
            printf("enter WHEN to search : ");
            new_gets(w,WHAT_LEN);
            for(int i=0;i<count;i++){
                if(strncmp(w,Book[i].when,WHAT_LEN)==0){
                    printf("Who: %s\n", Book[i].who);
                    printf("What: %s\n", Book[i].what);
                    printf("When: %s\n", Book[i].when);
                    printf("Where: %s\n", Book[i].where);
                }
            }
            break;
        case 3:
            w=(char*) malloc(sizeof (char)*WHO_LEN);
            printf("enter WHEN to search : ");
            new_gets(w,WHO_LEN);
            for(int i=0;i<count;i++){
                if(strncmp(w,Book[i].when,WHO_LEN)==0){
                    printf("Who: %s\n", Book[i].who);
                    printf("What: %s\n", Book[i].what);
                    printf("When: %s\n", Book[i].when);
                    printf("Where: %s\n", Book[i].where);
                }
            }
            break;
        case 4:
            w=(char*) malloc(sizeof (char)*WHERE_LEN);
            printf("enter WHEN to search : ");
            new_gets(w,WHERE_LEN);
            for(int i=0;i<count;i++){
                if(strncmp(w,Book[i].when,WHERE_LEN)==0){
                    printf("Who: %s\n", Book[i].who);
                    printf("What: %s\n", Book[i].what);
                    printf("When: %s\n", Book[i].when);
                    printf("Where: %s\n", Book[i].where);
                }
            }
            break;
        default:
            printf("please enter 1~4\n");
    }
}

void Quit (Record Book [], int count, char fileName[])
{
    int i;
    FILE * fp;

    printf("\nQuit --- It saves the current records ");
    printf("to the file and terminates the program.\n");

    printf("Saving to file: %s ... \n", fileName);
    fp = fopen ( fileName, "w");
    for (i = 0; i<count; ++i)
        fprintf(fp, "%s\n%s\n%s\n%s\n", Book[i].who,Book[i].what,Book[i].when,Book[i].where );//save data
    fclose(fp);
}
