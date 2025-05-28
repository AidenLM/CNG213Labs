//Mehmet Akif Elem
//2526283
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "list.h"
#include "queue.h"



// To parse input from program arguments
void parseInput(char *programArguments[], int *dogNumber, int *cageNumber, int *maxArrivalTime, int *maxServiceTime);

// To initialise, create and populate the dog list with random dog data
List createDogList(int numberOfDogs, int maxArrivalTime, int maxServiceTime);

//To initialise queue of the arrived dogs and cages availability data.
int* initialiseSimulator(Queue* dogQueue, int cageNumber);

//Adds the arrived dog into the priority queue
void newDog(Dog* dogData,Queue dogQueue);

//Randomly assign an available cage to the dog
void serveDog(Dog* dogData, int* cages, int cageNumber);

//Print the statistical data of the simulation run
void reportStatistics(List dogsDataList, int numberOfCages, int numberOfDogs, int clockTime);

//Clear dynamically allocated memories
void exitFromTheSimulation(List dogList, Queue dogQueue, int *cageData);


int main(int argc, char *argv[]) {
// Please ignore the lines and outputs I added to test whether the program works correctly
    int dogNumber, cageNumber, maxArrivalTime, maxServiceTime;
    parseInput(argv, &dogNumber, &cageNumber, &maxArrivalTime, &maxServiceTime);
    srand(time(NULL));

    List DogsList = createDogList(dogNumber, maxArrivalTime, maxServiceTime);
    DisplayList(DogsList);
    Queue waitingDogs;
    int* cageStatus = initialiseSimulator(&waitingDogs, cageNumber);

    int currentTime = 0;
    int dogsServed = 0;
    struct ListNode* IterDog = DogsList->head->next;

    while (dogsServed < dogNumber) {
        printf("Time: %d, Dogs served: %d\n", currentTime, dogsServed);
        fflush(stdin);
        // Add arrived dogs to the queue
        while (IterDog != NULL && IterDog->item->arrivalTime == currentTime) {
            printf("Dog arrived at time %d\n", IterDog->item->arrivalTime);
            newDog(IterDog->item, waitingDogs);
            IterDog = IterDog->next;
        }
        // Try to assign dogs in the queue to available cages
        // I didnt use enqueue function because its complicated I didnt want to use other c file I think readable that version
        while (!IsEmptyQueue(waitingDogs)) {
            // If queue is not empty keep dequeue dogs
            Dog* nextDog = FrontOfQueue(waitingDogs);
            int prevCage = nextDog->cageNumber;
            serveDog(nextDog, cageStatus, cageNumber);
            // if cage was successfully assigned
            if (nextDog->cageNumber != 0 && prevCage != nextDog->cageNumber) { // Check dog assigned
                nextDog->serviceStartTime = currentTime;
                Dequeue(waitingDogs);
            } else {
                break; // if no cage assigned wait until one free
            }
        }
        // Free cages of dogs completed
        struct ListNode* tmp = DogsList->head->next;
        while (tmp != NULL) {
            Dog* d = tmp->item;
            if (d->cageNumber > 0 && currentTime == d->serviceStartTime + d->serviceTime) {
                cageStatus[d->cageNumber-1] = 1;
                d->cageNumber = 0;
                dogsServed++;
            }
            tmp = tmp->next;
        }
        usleep(100000);  // Slow down for debug
        currentTime++;
    }
    reportStatistics(DogsList, cageNumber, dogNumber, currentTime);
    exitFromTheSimulation(DogsList, waitingDogs, cageStatus);

    return 0;
}

// take input from terminal
void parseInput(char *programArguments[], int *dogNumber, int *cageNumber, int *maxArrivalTime, int *maxServiceTime){
    *dogNumber = atoi(programArguments[1]);
    *cageNumber = atoi(programArguments[2]);
    *maxArrivalTime = atoi(programArguments[3]);
    *maxServiceTime = atoi(programArguments[4]);

}

//create list and order dog list according to arrival time
List createDogList(int numberOfDogs, int maxArrivalTime, int maxServiceTime){
    // I added on last node and ordered because this code is readable and less risky it can be added according to order while inserting node, but I didn't choose
    List dogList = CreateList();
    for (int i = 0; i < numberOfDogs; ++i) {
        Dog *newDog =  createRandomDog(maxArrivalTime,maxServiceTime);
        InsertToListEnd(dogList,newDog);
    }

    InsertListOrderedByArrivalTime(dogList,NULL);

        return dogList;
}
// create queue and prepare cage
int* initialiseSimulator(Queue* dogQueue, int cageNumber){

    *dogQueue = CreateQueue();
    int *reservedCage = malloc(sizeof(int)* cageNumber);
    for (int i = 0; i < cageNumber; i++) {
        reservedCage[i] = 1;
    }
    return reservedCage;
}
// assign new dog to queue depends on priority
void newDog(Dog* dogData, Queue dogQueue)
{// Add dog according to priority
    struct QueueNode *qt = dogQueue->front;
    struct QueueNode *newNode = malloc(sizeof(struct QueueNode));
    newNode->value = dogData;
    newNode->next = NULL;
    if (dogQueue->front->next == NULL) {
        dogQueue->front->next = newNode;
        dogQueue->rear = newNode;
    }
    else if (dogData->dogType == 'D') {
        while (qt->next != NULL && qt->next->value->dogType == 'D') qt = qt->next;

        newNode->next = qt->next;
        qt->next = newNode;
    }
    else if (dogData->dogType == 'U') {
        while (qt->next != NULL && (qt->next->value->dogType == 'D' || qt->next->value->dogType == 'U')) qt = qt->next;

        newNode->next = qt->next;
        qt->next = newNode;
    }
    else if (dogData->dogType == 'W') {
        while (qt->next != NULL) qt = qt->next;

        qt->next = newNode;
        newNode->next = NULL;
        dogQueue->rear = newNode;
    }
    dogQueue->size++;
}


void reportStatistics(List dogsDataList, int numberOfCages, int numberOfDogs, int clockTime)
{
    int dCount = 0;
    int maleCount = 0;
    int femaleCount = 0;
    int wCount = 0;
    int uCount = 0;
    int neuteredCount = 0;
    int notNeuteredCount = 0;
    int *cageUsed = malloc(sizeof(int) * numberOfCages);
    for (int i = 0; i < numberOfCages; i++) {
        cageUsed[i] = 0;
    }
    int totalWait = 0;
    int maxWait = 0;

    struct ListNode *tmp = dogsDataList->head->next;
    while (tmp != NULL) {
        Dog *d= tmp->item;

        // dog type count
        if (d->dogType =='D') {
            dCount++;
        } else if (d->dogType == 'U') {
            uCount++;
        } else if (d->dogType == 'W') {
            wCount++;
        }
        // cage usage
        if (d->cageNumber > 0 && d->cageNumber <= numberOfCages) {
            cageUsed[d->cageNumber - 1]++;
        }
        // wait time
        int wait = d->serviceStartTime -d->arrivalTime;
        totalWait += wait;
        if (wait > maxWait) {
            maxWait = wait;
        }
        // gender count
        if (d->dogGender == 1) {
            maleCount++;
        } else {
            femaleCount++;
        }
        // neutered count
        if (d->isNeutered == 1) {
            neuteredCount++;
        } else {
            notNeuteredCount++;
        }
        tmp = tmp->next;
    }
    float avgWait = (float)totalWait / (float)numberOfDogs;
    printf("****************Report*****************\n");
    printf("The number of cages: %d\n", numberOfCages);
    printf("The number of dogs: %d\n", numberOfDogs);
    printf("Number of dogs for each dog type:\n");
    printf(" Dangerous: %d\n", dCount);
    printf(" Unwell: %d\n", uCount);
    printf(" Well: %d\n", wCount);

    printf("Number of dogs for each cage:\n");
    for (int i = 0; i < numberOfCages; i++) {
        printf(" Cage %d: %d\n", i + 1, cageUsed[i]);
    }
    printf("Completion time: %d\n", clockTime);
    printf("Average time spent in the queue: %.1f\n", avgWait);
    printf("Maximum waiting time: %d\n", maxWait);
    if (maleCount >= femaleCount) {
        printf("Most gender usage: Male\n");
    } else {
        printf("Most gender usage: Female\n");
    }

    if (neuteredCount >= notNeuteredCount) {
        printf("Most neutered usage: Neutered\n");
    } else {
        printf("Most neutered usage: Not Neutered\n");
    }

    free(cageUsed);
}

// find empty cage and serve it
void serveDog(Dog* dogData, int* cagesStatus, int cageNumber) {
    for (int i = 0; i < cageNumber; i++) {
        if (cagesStatus[i] == 1) { // cage is available
            dogData->cageNumber = i + 1;
            cagesStatus[i] = 0;
            return;
        }
    }

}


void exitFromTheSimulation(List dogList, Queue dogQueue, int* cageData)
{
    deleteList(dogList);
    deleteQueue(dogQueue);
    free(cageData);
    printf("--END--\n");
}
