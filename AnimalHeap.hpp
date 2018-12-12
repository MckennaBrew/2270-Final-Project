#ifndef ANIMALHEAP_HPP
#define ANIMALHEAP_HPP

#include <iostream>
using namespace std;

struct Animal{
    string type; // will either be cat or dog
    int age;
    string name;
    string breed;
    int timeInShelter;
    Animal()
    {
        type = "";
        name = "unused";
        age = 0;
        breed = "";
        timeInShelter = 0;
    }
};

class AnimalHeap{
    private:
        bool isMax; // flag for whether its a min or max heap, true for max heap and false for min heap

        void repairUpwardMax(int); // heapfi functions for adding to the heap
        void repairUpwardMin(int);

        void repairDownwardMin(int); // heapify functions for deleting from the heap
        void repairDownwardMax(int);

        int currentQueueSize; // current size of the heap
        int maxQueueSize; // max size of the heap (passed in by the command line)

        Animal* animalHeap;

    public:
        //AnimalHeap();

        AnimalHeap(int, bool); // takes in a size and a bool which determines whether the heap will be a min heap or a max heap
        AnimalHeap(const AnimalHeap &copy); // copy constructor that we can use to replicate our existing heap
        ~AnimalHeap(); // deconstructor

        void printAnimal(); // mostly for testing

        int findAnimal(string); // finds an animal in the heap
        bool isFull(); // checks if the heap is full
        void resize(); // resizes the heap if it is full

        Animal adoptAnimal(string); // remove from the heap
        void rescueAnimal(Animal); // add to the heap

        void peek(); // look at the top of the heap
        bool removeTop(); // removes the top element from the heap

        Animal getTop();
        int getTopShelterTime();
        Animal getAnimal(string);

        int getQueueSize()
        {
            return currentQueueSize-1;
        }

        void printDogs();
        void printCats();

};
#endif
