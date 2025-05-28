#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node
{
    int  val;
    struct Node *next;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;

List CreateList(void);
void MakeEmptyList(List);
int ListSize(List);
int HeadOfList(List);
int TailOfList(List);
int IsEmptyList(List);
void DisplayList(List);
struct ListRecord* InsertElement(struct ListRecord *p,int val, int pos);
void DeleteList(struct ListRecord *p,int val);

int main()
{
    List myList;
    int exit, val, pos;
    char command;

    myList = CreateList();
    exit = FALSE;

    while (!exit)
    {
        fflush(stdin);
        printf("\n(i)nitialize\n");
        printf("(n)ew element\n");
        printf("(d)elete element\n");
        printf("(f)ind element\n");
        printf("(p)osition of element\n");
        printf("(h)ead of list\n");
        printf("(t)ail of list\n");
        printf("(e)xit\n");
        printf("Enter command: ");
        scanf("%c", &command);
        fflush(stdin);

        switch (command)
        {
            case 'i':
                MakeEmptyList(myList);
                break;
            case 'n':
                printf("enter value: ");
                scanf("%d", &val);
                printf("enter position: ");
                scanf("%d", &pos);
                myList = InsertElement(myList,val,pos);
                DisplayList(myList);
                //InsertList(myList, pos, val);
                break;
            case 'd':
                printf("enter value: ");
                scanf("%d", &val);
                DeleteList(myList, val);
                DisplayList(myList);
                break;
            case 'p':
                printf("enter value: ");
                scanf("%d", &val);
                //pos = GetPositionOfElement(myList, val);
                if (pos > 0)
                    printf("element %d at position %d\n", val, pos);
                break;
            case 'f':
                printf("enter position: ");
                scanf("%d", &pos);
                //val = GetElementAtPosition(myList, pos);
                if (val >= 0)
                    printf("element at position %d is %d\n", pos, val);
                break;
            case 'h':
                val = HeadOfList(myList);
                if (val != -1)
                    printf("front element is %d\n", val);
                break;
            case 't':
                val = TailOfList(myList);
                if (val != -1)
                    printf("rear element is %d\n", val);
                break;
            case 'e':
                exit = TRUE;
                break;
            default:
                printf("command not recognized\n");
                break;
        }
        DisplayList(myList);
    }

    printf("\n");
    system("PAUSE");
    return 0;
}

struct ListRecord* InsertElement(struct ListRecord *p,int val, int pos){

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->val =val;
    newNode->next = NULL;

    if(p->size == 0){
        // add to head
        p->head->next = newNode;
        p->size++;
    }
    else if(p->size > pos){
        //add to position
        if(pos == 1){
            newNode->next = p->head->next;
            p->head->next = newNode;
        }
        else{
            struct Node *tmp = p->head;
            for (int i = 0; i < pos-1; ++i) {
                tmp= tmp->next;
            }
            newNode->next = tmp->next;
            tmp ->next = newNode;
        }
        p->size++;
    }else if(p->size == pos){
        //add to last

        struct Node *tmp = p->head->next;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
    else{
        // add to last but if pos>size
        pos = p->size + 1;
        struct Node *tmp = p->head;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
        p->size++;

    }

    return p;

}

void DeleteList(struct ListRecord *p,int val){
    int pos=0;
    int posOfValue;
    //delete from head
    //delete from mid
    //delete from end

    //find pos of val
    struct Node *tmp = p->head;
    while(tmp != NULL){
        if(tmp->val == val){
            posOfValue = pos;
        }
        tmp = tmp->next;
        pos++;
    }

    if(posOfValue == 1){
        struct Node *deleteNode;
        deleteNode =p->head->next;
        p->head->next= p->head->next->next;
        printf("%d\n",p->head->next->val);
        free(deleteNode);
    }else{
        struct Node *tmp = p->head->next;
        struct Node *deleteNode;
        for (int i = 1; i < posOfValue-1; ++i) {
            tmp = tmp->next;
        }
        deleteNode = tmp->next;
        tmp->next = tmp->next->next;
        free(deleteNode);
    }





}

List CreateList()
{
    List l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!\n");
    else
        MakeEmptyList(l);

    return l;
}

void MakeEmptyList(List l)
{
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");

    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}

int IsEmptyList(List l)
{
    return (l->size == 0);
}

int ListSize(List l)
{
    return (l->size);
}

int HeadOfList(List l)
{
    if (!IsEmptyList(l))
        return l->head->next->val;
    else
    {
        printf("The linked list is empty\n");
        return -1;
    }
}

int TailOfList(List l)
{
    if (!IsEmptyList(l))
        return l->tail->val;
    else
    {
        printf("The linked list is empty\n");
        return -1;
    }
}

void DisplayList(List l)
{
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL)
    {
        printf("--> %d\t", p->val);
        p = p->next;
    }
    printf("\n");
}
