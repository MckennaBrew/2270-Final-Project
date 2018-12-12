#include "AnimalHeap.hpp"
#include <iostream>
#include<string>
using namespace std;

//Constructor creates the 4 separate heaps and initializes queueSizes.
AnimalHeap::AnimalHeap(int queueSize, bool flag)
{
  maxQueueSize = queueSize;
  currentQueueSize = 0;

  animalHeap = new Animal[maxQueueSize];

  isMax = flag; // will be true for max heap, false for min heap
}

AnimalHeap::AnimalHeap(const AnimalHeap &copy)
{
  currentQueueSize = copy.currentQueueSize;
  animalHeap = new Animal[copy.maxQueueSize]; //creating a new object that is copying our pre-existing heap

  for(int i = 0; i < currentQueueSize; i++)
  {
    animalHeap[i] = copy.animalHeap[i]; // so we can make a temp animal heap in the shelter class
  }
}


//Deconstructor
AnimalHeap::~AnimalHeap()
{
  //delete
  if(animalHeap!=NULL)
  {
    delete []animalHeap;
  }
}

// functions adds an animal to the heap
void AnimalHeap::rescueAnimal(Animal newAnimal)
{
  if(currentQueueSize == maxQueueSize)
  {
    cout << "resizing" << endl;
    resize();
  }

  //cout << "adding dog" << endl;

  int y = currentQueueSize;
  currentQueueSize++;

  animalHeap[y] = newAnimal;

  /* animalHeap[y].age = _age;
  animalHeap[y].breed = _breed;
  dogMaxHeap[y].name= dogMinHeap[y].name = _name;
  dogMaxHeap[y].timeInShelter= dogMinHeap[y].timeInShelter = _timeInShelter; */

  //cout << "test 2" << endl;

  if(isMax)
  {
    repairUpwardMax(y);
  }
  else
  {
    repairUpwardMin(y);
  }
}

// reapair up for max heaps
void AnimalHeap::repairUpwardMax(int nodeIndex)
{
  int p = (nodeIndex-1)/2; //int largest=nodeIndex;

  if(nodeIndex >= 0 && animalHeap[p].timeInShelter < animalHeap[nodeIndex].timeInShelter)
  {
    Animal temp = animalHeap[nodeIndex];
    animalHeap[nodeIndex] = animalHeap[p];
    animalHeap[p] = temp;
    repairUpwardMax(p);
  }

  //tie-breaker scenario
  if(nodeIndex >= 0 && animalHeap[p].timeInShelter == animalHeap[nodeIndex].timeInShelter)
  {
    if(animalHeap[p].age < animalHeap[nodeIndex].age)
    {
      Animal temp = animalHeap[nodeIndex];
      animalHeap[nodeIndex] = animalHeap[p];
      animalHeap[p] = temp;
      repairUpwardMax(p);
    }
  }
}

//Repairs up for Min Heap
void AnimalHeap::repairUpwardMin(int nodeIndex)
{
  int p = (nodeIndex-1)/2;

  //int largest=nodeIndex;
  if(nodeIndex >= 0 && animalHeap[p].timeInShelter > animalHeap[nodeIndex].timeInShelter)
  {
    Animal temp = animalHeap[nodeIndex];
    animalHeap[nodeIndex] = animalHeap[p];
    animalHeap[p] = temp;
    repairUpwardMin(p);
  }
  //tie-breaker scenario
  else if(nodeIndex >= 0 && animalHeap[p].timeInShelter == animalHeap[nodeIndex].timeInShelter)
  {
    if(animalHeap[p].age > animalHeap[nodeIndex].age)
    {
      Animal temp = animalHeap[nodeIndex];
      animalHeap[nodeIndex] = animalHeap[p];
      animalHeap[p] = temp;
      repairUpwardMin(p);
    }
  }
}

// adoptDog for Max Heap
Animal AnimalHeap::adoptAnimal(string name) // need to fix this!!//////////////////////////////////////////
{
  int nodeIndex = findAnimal(name);
  Animal temp;

  if(nodeIndex < 0)
  {
    cout << "Animal not found." << endl;
    return temp;
  }

  temp = animalHeap[nodeIndex];
  animalHeap[nodeIndex] = animalHeap[currentQueueSize-1]; // -1 is the next available one index wise

  currentQueueSize--;

  if(isMax)
  {
    repairDownwardMax(nodeIndex);
  }
  else
  {
    repairDownwardMin(nodeIndex);
  }

  cout<< "Congrats on finding a forever friend in "<< name << "!!"<<endl;


  return temp;
}

// Repairs down for a max heap
void AnimalHeap::repairDownwardMax(int nodeIndex)
{
  int l = (2*nodeIndex) + 1;
  int r = (2*nodeIndex) + 2;

  int smallest = nodeIndex;

  if(l < currentQueueSize && animalHeap[l].timeInShelter > animalHeap[smallest].timeInShelter)
  {
    smallest = l;
  }
  if(r < currentQueueSize && animalHeap[r].timeInShelter > animalHeap[smallest].timeInShelter)
  {
    smallest = r;
  }
  else if(r < currentQueueSize && animalHeap[r].timeInShelter == animalHeap[smallest].timeInShelter) // assuming that q size is a valid number versus not a valid number for the index
  {
    if(animalHeap[r].age < animalHeap[smallest].age)
    {
      smallest = r;
    }
  }
  else if(l < currentQueueSize && animalHeap[l].timeInShelter == animalHeap[smallest].timeInShelter)
  {
    if(animalHeap[l].age < animalHeap[smallest].age)
    {
      smallest = l;
    }
  }

  if(smallest != nodeIndex)
  {
    Animal temp = animalHeap[nodeIndex];
    animalHeap[nodeIndex] = animalHeap[smallest];
    animalHeap[smallest] = temp;
    repairDownwardMax(smallest);
  }
}

// reapair down for dog min heap
void AnimalHeap::repairDownwardMin(int nodeIndex)
{
  int l = (2*nodeIndex) + 1;
  int r = (2*nodeIndex) + 2;

  int smallest = nodeIndex;

  if(l < currentQueueSize && animalHeap[l].timeInShelter < animalHeap[smallest].timeInShelter)
  {
    smallest = l;
  }
  if(r < currentQueueSize && animalHeap[r].timeInShelter < animalHeap[smallest].timeInShelter)
  {
    smallest = r;
  }
  else if(r < currentQueueSize && animalHeap[r].timeInShelter == animalHeap[smallest].timeInShelter) // assuming that q size is a valid number versus not a valid number for the index
  {
    if(animalHeap[r].age > animalHeap[smallest].age)
    {
      smallest = r;
    }
  }
  else if(l < currentQueueSize && animalHeap[l].timeInShelter == animalHeap[smallest].timeInShelter)
  {
    if(animalHeap[l].age > animalHeap[smallest].age)
    {
      smallest = l;
    }
  }

  if(smallest != nodeIndex)
  {
    Animal temp = animalHeap[nodeIndex];
    animalHeap[nodeIndex] = animalHeap[smallest];
    animalHeap[smallest] = temp;
    repairDownwardMin(smallest);
  }
}


void AnimalHeap::peek()
{
  cout<< "Type: "<< animalHeap[0].type << endl;
  cout<< "Name: "<< animalHeap[0].name << endl;
  cout<< "Age: "<< animalHeap[0].age << endl;
  cout<< "Breed: "<< animalHeap[0].breed << endl;
  cout<< "Time in Shelter: "<< animalHeap[0].timeInShelter << endl;
  cout << "********" << endl;
}

int AnimalHeap::findAnimal(string _name)
{
    for(int t=0; t < currentQueueSize; t++){

      if(animalHeap[t].name == _name)
      {
          //cout<<"Found!"<<endl;
          return t; // returning node index
      }
    }

    return -1;
}

void AnimalHeap::printAnimal()
{

  for(int t = 0; t < currentQueueSize; t++)
  {
    cout << "Type: " << animalHeap[t].type << endl;
    cout << "Name: " << animalHeap[t].name<< endl;
    cout << "Age: "<< animalHeap[t].age << endl;
    cout << "Breed: "<< animalHeap[t].breed << endl;
    cout << "Time in Shelter: "<< animalHeap[t].timeInShelter << endl;
    cout << "**********************" << endl;
  }
}


void AnimalHeap::resize()
{
  Animal tempArray[currentQueueSize];
  int tempSize = currentQueueSize;

  //Dog tempArrayMin[currentDogQueueSize];

  for(int y=0; y<currentQueueSize; y++)
  {
    tempArray[y] = animalHeap[y];
  }

    //double the size
  delete []animalHeap; // have to delete because we dynamically alocated

  maxQueueSize = maxQueueSize*2;
  currentQueueSize = 0;

  animalHeap = new Animal[maxQueueSize];

    //reassign
  for(int i = 0; i < tempSize; i++)
  {
    Animal temp = tempArray[i];
    rescueAnimal(temp);
  }
}


bool AnimalHeap::isFull(){

  if(currentQueueSize==maxQueueSize)
  {
    //resizeDog();
    return true;

  }
  else
  {
    cout << "false" << endl;
    return false;
  }
}

bool AnimalHeap::removeTop()
{

  if(currentQueueSize-2 < 0) //-2 because otherwise it prints the last one twice
  {
    return false;
  }

  animalHeap[0] = animalHeap[currentQueueSize-1]; // -1 is the next available one index wise

  currentQueueSize--;

  if(isMax)
  {
    repairDownwardMax(0);
  }
  else
  {
    repairDownwardMin(0);
  }

  return true;

}

Animal AnimalHeap::getAnimal(string name)
{
  Animal tempAnimal;

  int temp = findAnimal(name);

  if(temp >= 0)
  {
    tempAnimal = animalHeap[temp];
  }

  return tempAnimal;
}

Animal AnimalHeap::getTop()
{
  return animalHeap[0];
}

int AnimalHeap::getTopShelterTime()
{
  return animalHeap[0].timeInShelter;
}


void AnimalHeap::printDogs()
{
  for(int i = 0; i < currentQueueSize; i++)
  {
    if(animalHeap[i].type == "dog")
    {
      cout << "Name: " << animalHeap[i].name<< endl;
      cout << "Age: "<< animalHeap[i].age << endl;
      cout << "Breed: "<< animalHeap[i].breed << endl;
      cout << "Time in Shelter: "<< animalHeap[i].timeInShelter << endl;
      cout << "**********************" << endl;
    }
  }
}

void AnimalHeap::printCats(){
  for(int i=0; i<currentQueueSize; i++){
    if(animalHeap[i].type =="cat"){
      cout << "Name: " << animalHeap[i].name<< endl;
      cout << "Age: "<< animalHeap[i].age << endl;
      cout << "Breed: "<< animalHeap[i].breed << endl;
      cout << "Time in Shelter: "<< animalHeap[i].timeInShelter << endl;
      cout << "**********************" << endl;
    }
  }
}
