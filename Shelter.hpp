#ifndef Shelter_HPP
#define Shelter_HPP

#include "AnimalHeap.hpp"
#include <string>
#include <array>
#include <iostream>
using namespace std;


class Shelter{
    private:

        AnimalHeap shelterHeap;

        float median;
        AnimalHeap leftMedianHeap; // needs to be a max heap
        AnimalHeap rightMedianHeap; // needs to be a min heap


    public:
        Shelter(int); // will take in a size
        ~Shelter();

        void add(string, int, string, string, int); // string type, int age, string name, string breed, int timeInShelter // adds an animal
        void removeAnimal(string); // string name // removes an an animal

        void printCats();
        void printDogs();

        void printInOrder(); // prints the animals in the order of time they have been there

        void find(string name); // need to fix this i think
        void peek();

        void findMedian(Animal); // finds the median time an animal spends at the shelter

        float getMedian()
        {
            return median;
        }

        int Average(int, int); // helper function that finds the average betweem two numbers


};
#endif
