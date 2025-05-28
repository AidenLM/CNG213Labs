#include "Dog.h"
#include <time.h>

//Mehmet Akif Elem
//2526283
//This function will create a dynamically allocated dog with random values and return its address.
Dog* createRandomDog(int maxArrivalTime, int maxServiceTime){
    //To be completed
    int type;
    Dog *new = malloc(sizeof(Dog));
    type = randomizer(3);
    if (type == 0)
        new->dogType = 'D';
    else if (type == 1)
        new->dogType = 'U';
    else
        new->dogType = 'W';
    new->arrivalTime = randomizer(maxArrivalTime);
    new->serviceTime = randomizer(maxServiceTime);
    new->serviceStartTime = 0;
    new->cageNumber = 0;
    new->dogGender = randomizer(2);
    new->isNeutered = randomizer(2);

    return new;

}

int randomizer(int max){
    return rand() % max;
}


//This function gets a dogs address and prints its values.
void printDogInformation(Dog* dog){
    if(dog != NULL){
        printf("%c %2d %2d %2d %2d %6s %12s\n", dog->dogType, dog->arrivalTime, dog->serviceTime, dog->serviceStartTime, dog->cageNumber, dog->dogGender == 1 ? "Male" : "Female", dog->isNeutered == 1 ? "Neutered" : "Not Neutered");
    }
}