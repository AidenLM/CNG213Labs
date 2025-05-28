#include <stdio.h>
#include <stdlib.h>

//To represent an empty stack, EMPTY_TOS -1 is used
#define EMPTY_TOS -1
#define FALSE 0
#define TRUE 1

//Node declaration that will be used to store data in a stack
struct Node
{
    int x;
    int y;
    struct Node *next;
};

struct Polygon{
    struct Node *polygonList;
    struct Polygon *next;
};

//Declaration of a stack node
typedef struct Node StackRecord;
typedef StackRecord *Stack;

//Function signatures
Stack CreateStack();
void MakeEmptyStack(Stack);
void PushStack(int x,int y, Stack s);
int PopStack(Stack);
int TopOfStack(Stack);
int IsEmptyStack(Stack);
void DisplayStack(Stack);
void CopyStack(Stack s);
struct Polygon* CompletePolygon(Stack s,struct Polygon *p);

int main()
{
    Stack myStack;
    int exit, x,y;
    char command;

    myStack = CreateStack();
    struct Polygon *myPolygon = NULL;
    exit = FALSE;

    while (!exit)
    {
        fflush(stdin);
        printf("Enter command i)nitialize p)ush r)emove (pop) t)op of stack c)opy stack a)dd to polygon list e)xit: ");
        scanf("%c", &command);
        fflush(stdin);

        switch (command)
        {
            case 'a':
                myPolygon = CompletePolygon(myStack,myPolygon);
                DisplayStack(myPolygon->polygonList);
                break;
            case 'c':
                CopyStack(myStack);
                break;
            case 'i':
                MakeEmptyStack(myStack);
                break;
            case 'p':
                printf("enter value of (x,y): ");
                scanf("%d %d", &x,&y);
                PushStack(x,y, myStack);
                break;
            case 'r':
                if (IsEmptyStack(myStack))
                    printf("The stack is empty!\n");
                else
                    x = PopStack(myStack);
                printf("Pop value from stack = %d\n", x);
                break;
            case 't':
                x = TopOfStack(myStack);
                if (x != -1)
                    printf("top element is %d\n", x);
                break;
            case 'e':
                exit = TRUE;
                break;
            default:
                printf("command not recognized\n");
                break;
        }
        DisplayStack(myStack);
    }

    printf("\n");
    system("PAUSE");
    return 0;
}

//This function initialises a stack with a dummy node
Stack CreateStack()
{
    //TO BE COMPLETED
    Stack s = malloc(sizeof(struct Node));
    if(s ==  NULL){
        printf("there is no stack bro\n");
        exit(1);
    }
    s->next = NULL;
    return s;

}

//This function empties the content of a stack
void MakeEmptyStack(Stack s)
{
    //TO BE COMPLETED
    s = NULL;

}

//This function checks if a stack is empty or not
int IsEmptyStack(Stack s)
{
    //TO BE COMPLETED
    if(s ->next == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//This function checks if a stack is full
int IsFullStack(Stack s)
{
    return FALSE;
}

//This function creates a new node, adds the value of x to this node
//and then pushes this new node to the given stack
void PushStack(int x,int y, Stack s)
{
    //TO BE COMPLETED
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->x = x;
    newNode->y = y;

    if(s->next == NULL){

        s->next = newNode;
    }else{
        newNode->next = s->next;
        s->next = newNode;
    }
}

//This function pops the top node from the stack frees the memory location
//of that node and returns the value stored in that top node
int PopStack(Stack s)
{
    //TO BE COMPLETED
    if(IsEmptyStack(s)){
        printf("Stuck is empty\n");
        return -1;
    }else{
        int topOfPopValueX = s->next->x;

        struct Node *removeNode;
        removeNode = s->next;
        if(s->next->next !=NULL){
            s->next = s->next->next;

        }else{
            s->next = NULL;
        }
        free(removeNode);
        return topOfPopValueX;
    }



}

//This function returns the value stored at the top node
int TopOfStack(Stack s)
{
    //TO BE COMPLETED

}

//This function displays the content of a stack
void DisplayStack(Stack s)
{
    struct Node *p;
    printf("Stack content:\n");
    if (IsEmptyStack(s))
        printf("The stack is empty!\n");
    else{
        p = s->next;
        while (p != NULL)
        {
            printf("\t--> %d,%d\n", p->x,p->y);

            p = p->next;
        }
    }
}

void CopyStack(Stack s){

    struct Node *s2 = NULL;
    while (s != NULL){
        struct Node *tmp = s;
        s = s->next;

        tmp->next = s2;
        s2 = tmp;
    }
    DisplayStack(s2);

    struct Node *s3 = NULL;
    while (s2 != NULL){
        struct Node *tmp2 = s2;
        s2 = s2->next;

        tmp2->next = s3;
        s3 = tmp2;
    }
    DisplayStack(s3);

}

struct Polygon* CompletePolygon(Stack s,struct Polygon *p){
    struct Node* tmp = s;
    struct Node* s2;

    while(tmp != NULL){

        struct Node *newNode = malloc(sizeof(struct Node));
        newNode->x = tmp->x;
        newNode->y = tmp->y;
        newNode->next = NULL;

        if(s2 == NULL){
            s2 = newNode;
        }else{
            newNode->next = s2;
            s2 = newNode;
        }

    }

    struct Node* tmp2 = s2;
    struct Node* s3;
    while(tmp2 != NULL){

        struct Node *newNode2 = malloc(sizeof(struct Node));
        newNode2->x = tmp->x;
        newNode2->y = tmp->y;
        newNode2->next = NULL;

        if(s3 == NULL){
            s3 = newNode2;
        }else{
            newNode2->next = s3;
            s3 = newNode2;
        }

        if(p->polygonList == NULL){
            p->polygonList = newNode2;
        }else{
            newNode2->next = p->polygonList;
            p->polygonList = newNode2;
        }

    }


    return p;
}
