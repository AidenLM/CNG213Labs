#include "list.h"
//Mehmet Akif Elem
//2526283
List CreateList()
{
    List l;
    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL) printf("Out of memory!\n");
    else MakeEmptyList(l);

    return l;

}

void MakeEmptyList(List l)
{
    l->head = (struct ListNode *) malloc(sizeof(struct ListNode));
    if (l->head == NULL) printf("Out of memory!\n");
    l->head->next = NULL;
    l->tail = l->head;
}

void InsertList(List l, int pos, Dog* data)
{
    struct ListNode *newNode = (struct ListNode *) malloc(sizeof(struct ListNode));
    newNode->item = data;
    newNode->next = NULL;

    if (pos > (l->length)) {
        pos = (l->length + 1);
    }

    if (pos == 1) {
        newNode->next = l->head->next;
        l->head->next = newNode;

        if (l->length == 0) {
            l->tail = newNode;
        }
    } else if (pos == (l->length) + 1) {
        l->tail->next = newNode;
        l->tail = newNode;
    } else {
        struct ListNode *tmp = l->head;
        for (int i = 0; i < pos - 1; i++) {
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }

    l->length++;
}

void InsertToListEnd(List l, Dog* dog){
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->item = dog;
    newNode->next = NULL;
    l->tail->next = newNode;
    l->tail = newNode;
}

void InsertToListHead(List l, Dog* dog){
    //To be completed
    struct ListNode *newNode = malloc(sizeof(struct ListNode));
    newNode->item = dog;
    newNode->next = NULL;
    newNode->next = l->head->next;
    l->head->next = newNode;
}

void InsertListOrderedByArrivalTime(List l, Dog* newDog){
    struct ListNode *c, *cn, *cnn, *tmp;
    int sorted;
    tmp = l->head;

    do {
        c = tmp;
        sorted = 0;

        while(c->next->next != NULL) {
            cn = c->next;
            cnn = cn->next;

            if(cn->item->arrivalTime > cnn->item->arrivalTime) {
                cn->next = cnn->next;
                cnn->next = cn;
                c->next = cnn;
                sorted++;
            }
            else {
                c = c->next;
            }
        }

    } while (sorted != 0);
}

Dog* DeleteFirstNode(List l){
    //To be completed
    struct ListNode *removeNode;
    if(l->head->next == NULL){
        printf("Dog list is empty!\n");
        return NULL;
    }else{
        removeNode = l->head->next;
        l->head->next = l->head->next->next;
        Dog* removedDog = removeNode->item;
        free(removeNode);
        return removedDog;
    }
}

void DeleteFromList(List l, Dog* v)
{
    if (l == NULL ) {
        printf("List is empty!\n");
        return;
    }

    if (l->head->next == NULL ) {
        printf("List is empty!\n");
        return;
    }
    struct ListNode* tmp = l->head;

    while (tmp->next != NULL) {
        if (tmp->next->item == v) {
            struct ListNode* toDelete = tmp->next;
            tmp->next = toDelete->next;

            if (toDelete == l->tail) {
                l->tail = tmp;
            }
            free(toDelete->item);
            free(toDelete);
            l->length--;
            return;
        }
        tmp = tmp->next;
    }

    printf("Dog not found in list!\n");
}


int IsEmptyList(List l)
{
    int isItEmpty = -1;
    if(l->length == 0) isItEmpty = 1;
    else isItEmpty = 0;
    return isItEmpty;
}

int ListSize(List l)
{
    return l->length;
}

Dog* HeadOfList(List l)
{
    if (!IsEmptyList(l))
        return l->head->next->item;
    else {
        printf("The linked list is empty\n");
        return NULL;
    }
}

Dog* TailOfList(List l)
{
    if (!IsEmptyList(l))
        return l->tail->item;
    else {
        printf("The linked list is empty\n");
        return NULL;
    }
}

void DisplayList(List l)
{
    struct ListNode *p;
    p = l->head->next;
    printf("List content:\n");
    while (p != NULL) {
        printf("%c %2d %2d %2d %2d %6s %12s\n",
               p->item->dogType,
               p->item->arrivalTime,
               p->item->serviceTime,
               p->item->serviceStartTime,
               p->item->cageNumber,
               p->item->dogGender == 1 ? "Male" : "Female", p->item->isNeutered == 1 ? "Neutered" : "Not Neutered");
        p = p->next;
    }
    printf("\n");
}

void deleteList(List toDeleteList) {
    if (toDeleteList == NULL) return;
    struct ListNode* current = toDeleteList->head->next;
    struct ListNode* temp;
    while (current != NULL) {
        temp = current->next;
        free(current->item);
        free(current);
        current = temp;
    }
    toDeleteList->head->next = NULL;
}


