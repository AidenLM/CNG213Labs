#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

/*A Node declaration to store a value and a link*/
struct Node
{
    int val;
    struct Node *next;
};

/*Queue Record that will store the following:
size: total number of elements stored in the list
front: it shows the front node of the queue (front of the queue)
rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
    struct Node *front;   /* pointer to front of queue */
    struct Node *rear;    /* pointer to rear of queue */
    int size;             /* number of items in queue */
};
typedef struct QueueRecord *Queue;

Queue CreateQueue();
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
void Enqueue(int, Queue);
int Dequeue(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);

int main()
{
    int queueSize;
    Queue myQueue;
    int exit, val;
    char command;

    myQueue = CreateQueue();

    exit = FALSE;

    while (!exit)
    {
        fflush(stdin);
        printf("Enter command i)nitialize e)nqueue d)equeue f)ront queue r)ear queue t)erminate: ");
        scanf("%c", &command);
        fflush(stdin);

        switch (command)
        {
            case 'i':
                MakeEmptyQueue(myQueue);
                break;
            case 'e':
                printf("enter value: ");
                scanf("%d", &val);
                Enqueue(val, myQueue);
                break;
            case 'd':
                val = Dequeue(myQueue);
                break;
            case 'f':
                val = FrontOfQueue(myQueue);
                if (val != -1)
                    printf("front element is %d\n", val);
                break;
            case 'r':
                val = RearOfQueue(myQueue);
                if (val != -1)
                    printf("rear element is %d\n", val);
                break;
            case 't':
                exit = TRUE;
                break;
            default:
                printf("command not recognized\n");
                break;
        }
        DisplayQueue(myQueue);
    }
    printf("\n");
    system("PAUSE");
    return 0;
}

/*This function initialises the queue*/
Queue CreateQueue()
{
    //TO BE COMPLETED
    struct QueueRecord *q = malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Queue not allocated!\n");
        exit(1);
    }

    MakeEmptyQueue(q);
    return q;
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
    //TO BE COMPLETED
    struct Node *dummy = malloc(sizeof(struct Node));
    if(dummy == NULL){
        printf("Dummy node not initiliazed!");
        exit(1);
    }
    q->size = 0;
    q->front = dummy;
    q->rear = dummy;

    q->front->next = NULL;
    q->rear = q->front;

}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
    //TO BE COMPLETED
    if(q->size == 0){
        return 1;
    }

    return 0;
}

/*Returns the queue size*/
int QueueSize(Queue q)
{
    //TO BE COMPLETED
    return q->size;
}

/*Enqueue - Adds a new element to the queue, simly creates a node and
adds it to the rear of the queue*/
void Enqueue(int x, Queue q)
{
    //TO BE COMPLETED
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->val = x;
    newNode->next = NULL;

    q->rear->next = newNode;
    q->rear = newNode;

    q->size++;
}

/*Dequeue - Removes a node from the queue, basically removes a node from
the front of the queue*/
int Dequeue(Queue q)
{
    //TO BE COMPLETED
    if(IsEmptyQueue(q)){
        printf("Queue is empty/ can not dequeue\n");
        return -1;
    }

    struct Node *removeNode = q->front->next;
    int value = removeNode->val;
    q->front->next = removeNode->next;

    if(q->rear == removeNode){
        q->rear = q->front;
    }

    free(removeNode);
    q->size--;
    return value;


}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->front->next->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->rear->val;
    else
    {
        printf("The queue is empty\n");
        return -1;
    }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *print;

    print = q->front->next;

    while (print != NULL)
    {
        printf("--> %d  ", print->val);
        print = print->next;
    }
    printf("\n");
}
