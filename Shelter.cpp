#include "Shelter.hpp"
#include <iostream>
#include<string>
using namespace std;

Shelter::Shelter(int size) :
shelterHeap(size, true),
leftMedianHeap(size, true),
rightMedianHeap(size, false)  // will initlialize
{
    median = 0;
}

Shelter::~Shelter()
{

}

void Shelter::add(string type, int age, string name, string breed, int timeInShelter)
{
    Animal temp;

    temp.type = type;
    temp.age = age;
    temp.name = name;
    temp.breed = breed;
    temp.timeInShelter = timeInShelter;

    shelterHeap.rescueAnimal(temp);
}

void Shelter::removeAnimal(string name)
{
    Animal temp = shelterHeap.adoptAnimal(name);

    if(temp.age != 0)
    {
        findMedian(temp);
    }
}

void Shelter::printInOrder()
{
    // to print
    // print the top
    // remove the top
    // then repair downwards
    // then repeat

    AnimalHeap tempHeap = shelterHeap;

    //tempHeap.printAnimal();
    bool flag = true;

    while(flag != false)
    {
        tempHeap.peek();
        flag = tempHeap.removeTop();
    }
}

void Shelter::printDogs()
{
    shelterHeap.printDogs();
}

void Shelter::printCats(){
    shelterHeap.printCats();
}

void Shelter::find(string name)
{
    Animal temp = shelterHeap.getAnimal(name);

    if(temp.age == 0)
    {
        cout << "Animal not found." << endl;
    }
    else
    {
        cout << "Type: " << temp.type << endl;
        cout<< "Name: "<< temp.name << endl;
        cout<< "Age: "<< temp.age << endl;
        cout<< "Breed: "<< temp.breed << endl;
        cout<< "Time in Shelter: "<< temp.timeInShelter << endl;
    }
}

void Shelter::peek()
{
    shelterHeap.peek();
}

void Shelter::findMedian(Animal animalToAdd)
{
    int balance = (leftMedianHeap.getQueueSize()) - (rightMedianHeap.getQueueSize());

    /*
    cout << "median: " << median << " balance: " << balance << endl;
    cout << "left" << endl;
    leftMedianHeap.printDogs();
    cout << "right" << endl;
    rightMedianHeap.printDogs(); */

    if(balance == 1) // left heap is bigger than the right heap
    {
        if(animalToAdd.timeInShelter < median)
        {
            // remove top of left heap and put it in the right heap

            rightMedianHeap.rescueAnimal(leftMedianHeap.getTop());
            leftMedianHeap.removeTop();

            leftMedianHeap.rescueAnimal(animalToAdd);
        }
        else
        {
            rightMedianHeap.rescueAnimal(animalToAdd);
        }

        median = Average(rightMedianHeap.getTopShelterTime(), leftMedianHeap.getTopShelterTime());

    }
    else if (balance == 0) // the heaps are the same size
    {
        if(animalToAdd.timeInShelter < median) // animal to add fits in left heap
        {
            leftMedianHeap.rescueAnimal(animalToAdd);

            median = leftMedianHeap.getTopShelterTime();
        }
        else
        {
            rightMedianHeap.rescueAnimal(animalToAdd);

            median = rightMedianHeap.getTopShelterTime();
        }
    }
    else if(balance == -1) // the right heap is bigger than the left heap
    {
        if(animalToAdd.timeInShelter < median)
        {
            leftMedianHeap.rescueAnimal(animalToAdd);
        }
        else
        {
            leftMedianHeap.rescueAnimal(rightMedianHeap.getTop());
            rightMedianHeap.removeTop();

            rightMedianHeap.rescueAnimal(animalToAdd);
        }

        median = Average(rightMedianHeap.getTopShelterTime(), leftMedianHeap.getTopShelterTime());
    }

    return;
}

int Shelter::Average(int a, int b)
{
    return (a + b) / 2;
} 
