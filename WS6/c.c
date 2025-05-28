//
// Created by Mehmet Akif LM on 8.04.2025.
//

#include <stdlib.h>
#include <stdio.h>
#define TRUE 1
#define FALSE 0

struct Node {

    int val;
    struct Node *next;
};

struct Node* PushStack(int, struct Node *s);
struct Node* PopStack(struct Node *s);
int TopOfStack(struct Node *s);
int IsEmptyStack(struct Node *s);
void DisplayStack(struct Node *s);



int main() {
    struct Node *myStack = NULL;
    int exit, val;
    char command;



    exit = FALSE;

    while (!exit) {
        fflush(stdin);
        printf("Enter command p)ush r)emove (pop) t)op of stack e)xit: ");
        scanf("%c", &command);
        fflush(stdin);

        switch (command) {

            case 'p':
                printf("enter value: ");
                scanf("%d", &val);
                myStack = PushStack(val, myStack);
                break;
            case 'r':
                if (IsEmptyStack(myStack))
                    printf("The stack is empty!\n");
                else
                    if(myStack != NULL){
                        val = myStack->val;
                    }
                    else{
                        val = -1;
                    }
                    myStack = PopStack(myStack);
                printf("Pop value from stack = %d\n", val);
                break;
            case 't':
                val = TopOfStack(myStack);
                if (val != -1)
                    printf("top element is %d\n", val);
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
}



//This function empties the content of a stack


//This function checks if a stack is empty or not
int IsEmptyStack(struct Node *s)
{
    //TO BE COMPLETED
    if(s == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//This function checks if a stack is full
int IsFullStack(struct Node *s)
{

    return FALSE;
}

//This function creates a new node, adds the value of x to this node
//and then pushes this new node to the given stack
struct Node* PushStack(int x, struct Node *s)
{
    //TO BE COMPLETED

    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->val = x;
    newNode->next = NULL;

    if(s == NULL){
        s = newNode;
    }else{
        newNode->next = s;
        s = newNode;

    }

    return s;

}

//This function pops the top node from the stack frees the memory location
//of that node and returns the value stored in that top node
struct Node* PopStack(struct Node *s)
{
    //TO BE COMPLETED
    if(s->next != NULL ){
        struct Node *removeTop;
        removeTop = s;
        s= s->next;
        free(removeTop);
    }else{
        s = NULL;
    }

    return s;
}

//This function returns the value stored at the top node
int TopOfStack(struct Node *s)
{
    //TO BE COMPLETE
    return s->val;
}

//This function displays the content of a stack
void DisplayStack(struct Node *s)
{
    struct Node *p;
    printf("Stack content:\n");
    if (IsEmptyStack(s))
        printf("The stack is empty!\n");
    else{
        p = s;
        while (p != NULL)
        {
            printf("\t--> %d\n", p->val);
            p = p->next;
        }
    }
}


