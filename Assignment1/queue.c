#include "queue.h"
//Mehmet Akif Elem
//2526283


Queue CreateQueue()
{
    struct QueueRecord *q = malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Queue not allocated!\n");
        exit(1);
    }
    MakeEmptyQueue(q);
    return q;
}

void MakeEmptyQueue(Queue q)
{
    struct QueueNode *dummy = malloc(sizeof(struct QueueNode));
    if(dummy == NULL){
        printf("Dummy node not initialized!");
        exit(1);
    }
    q->size = 0;
    q->front = dummy;
    q->rear = dummy;

    q->front->next = NULL;
    q->rear = q->front;
}

void Enqueue(Dog* newDog, Queue q)
{
    //To be completed
    struct QueueNode *newNode = malloc(sizeof(struct QueueNode));
    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = newDog;
    if(newDog->dogType == 'D') newNode->priority=3;
    else if (newDog->dogType =='U') newNode->priority=2;
    else if (newDog->dogType == 'W') newNode->priority=1;
    else newNode->priority = 100;
    newNode->next = NULL;

    q->rear->next = newNode;
    q->rear = newNode;

    q->size++;
}

Dog* Dequeue(Queue q)
{
    if(IsEmptyQueue(q)){
        printf("Queue is empty/ can not dequeue\n");
        return NULL;
    }

    struct QueueNode *removeNode = q->front->next;
    q->front->next = removeNode->next;
    if(q->rear == removeNode){
        q->rear = q->front;
    }
    Dog *removeNodeVal = removeNode->value;
    free(removeNode);
    q->size--;
    return removeNodeVal;
}

int IsEmptyQueue(Queue q)
{
    if(q->size == 0){
        return 1;
    }
    return 0;
}

int QueueSize(Queue q)
{
    return q->size;
}

Dog* FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->front->next->value;
    else
    {
        printf("The queue is empty\n");
        return NULL;
    }
}

Dog* RearOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
        return q->rear->value;
    else
    {
        printf("The queue is empty\n");
        return NULL;
    }
}

void DisplayQueue(Queue q)
{
    struct QueueNode *print;
    print = q->front->next;
    while (print != NULL)
    {
        printf("--> %c  ", print->value->dogType);
        print = print->next;
    }
    printf("\n");
}

void deleteQueue(Queue toDeleteList)
{
    if (toDeleteList == NULL) return;
    struct QueueNode *current = toDeleteList->front;
    while (current != NULL) {
        struct QueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(toDeleteList);
}
