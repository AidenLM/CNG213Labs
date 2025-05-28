#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node
{
    int val;
    struct Node *next;
    struct Node *prev;
};

struct ListRecord
{
    struct Node *head;
    struct Node *tail;
    int length;
};
typedef struct ListRecord *DoubleList;

DoubleList CreateList(int);
void MakeEmptyList(DoubleList);
void InsertListAtPosition(DoubleList, int, int);
void DisplayList(DoubleList);

int main()
{
    DoubleList myList;
    int exit, val, pos;
    char command;
    exit = FALSE;

    myList = CreateList(0);

    while (!exit)
    {
        fflush(stdin);
        printf("\nMenu: \n i)nitialize\n n)ew element\n e(x)it\nEnter command: ");
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
                InsertListAtPosition(myList, pos, val);
                break;
            case 'x':
                exit = TRUE;
                break;
            default:
                printf("command not recognized\n");
                break;
        }
        printf("\n");
        DisplayList(myList);

    }

    printf("\n");
    system("PAUSE");
    return 0;
}

DoubleList CreateList(int size)
{
    DoubleList l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL){
        printf("Out of memory!\n");
        exit(1);
    }
    l->head = malloc(sizeof(struct Node));
    if (l->head == NULL){
        printf("Out of memory!\n");
        exit(1);
    }

    return l;



}

void MakeEmptyList(DoubleList l)
{
    //TO BE COMPLETED
    if(l == NULL){
        printf("List allocation is failed\n");
        exit(1);
    }

    l->head->next = NULL;
    l->head->prev = NULL;
    l->tail = l->head;
    l->length = 0;



}

void InsertListAtPosition(DoubleList l, int pos, int val)
{
    //TO BE COMPLETED
    if(l == NULL || l->head == NULL ){
        printf("list allocation is failed!");
        exit(1);
    }

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next= NULL;
    newNode->prev = NULL;
    if(l->length == 0){
        l->head->next = newNode;
        newNode->prev = l->head;
        l->length = pos;
        l->length++;
    }
    else if(l->length < pos){
        struct Node *tmp = l->head;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        newNode->prev = tmp;
        tmp->next = newNode;
        l->length++;
    }
    else{
        struct Node *tmp = l->head;
        for (int i = 0; i < pos-1 && tmp->next != NULL; ++i) {
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        newNode->prev = tmp;
        tmp->next = newNode;
        tmp->next->prev = newNode;
        l->length++;
    }
}

void DisplayList(DoubleList l)
{
    struct Node *p;

    p = l->head->next;
    printf("List content:\n");

    while (p != NULL)
    {
        printf("--> %d\t", p->val);
        p = p->next;
    }
}
