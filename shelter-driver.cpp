#include "Shelter.hpp"
#include <sstream>
#include <string>
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;


int main(int argc, char* argv[]){
  if(argc!=2)
  {
    return -1;
  }

  Shelter shelter(stoi(argv[1]));
  bool complete = false;

  while(complete==false){
    cout << "======Main Menu======" << endl;
    cout << "1. Get Animal Information from File" << endl;
    cout << "2. Find a Specific Animal" << endl;
    cout << "3. Add an animal to the shelter" << endl;
    cout << "4. Adopt an animal" << endl;
    cout << "5. Print Dogs" << endl;
    cout << "6. Print Cats" << endl;
    cout << "7. Print all Animals in the Shelter" <<endl;
    cout << "8. Who needs to be adopted?" << endl;
    cout << "9. Find the average time an animal spends at the shelter" << endl;
    cout << "10. Quit" << endl;

    string userInput;
    getline(cin, userInput);

    //Reads in file information
    if(userInput=="1"){

      string nameFile;
      cout << "Enter filename:" << endl;
      getline(cin, nameFile);

      //cout << "test" << endl;

      ifstream mainfile(nameFile);
      string line1;

      //cout << "after line1" << endl;

      if(mainfile.is_open())
      {
        while(getline(mainfile, line1))
        {
          stringstream ss;

          ss << line1;
          string item;

          //define so we can pass later
          string type;
          int age;
          string name;
          string breed;
          int timeInShelter;

          //from file
          getline(ss, item, ',');
          type = item;

          getline(ss, item, ',');
          //cout << "item: " << item << endl;
          age = stoi(item);

          getline(ss, item, ',');
          name = item;

          getline(ss, item, ',');
          breed = item;

          getline(ss, item, ',');
          timeInShelter = stoi(item);

          shelter. add(type, age, name, breed, timeInShelter);
        }
        mainfile.close();
      }
    }

    //Find A Specific Animal
  else if(userInput=="2")
  {
    string nameA;

    cout << "Enter Name of Animal to Find:" << endl;
    getline(cin, nameA);

    shelter.find(nameA);
  }

// Adding animal to shelter
  else if(userInput=="3")
  {
    string animalType;
    cout << "What type of animal are they?: ";
    getline(cin, animalType);

    string animalName;
    cout << "What is their name?:  ";
    getline(cin, animalName);

    string animalAge;
    cout << "How old are they?: ";
    getline(cin, animalAge);

    string animalBreed;
    cout << "What breed are they?: ";
    getline(cin, animalBreed);

    shelter.add(animalType, stoi(animalAge), animalName, animalBreed, 0);
  }

  // adopt an animal
  else if(userInput == "4")
  {
      string animalLeaving;
      cout << "Enter the name of the animal you want to adopt: " << endl;
      getline(cin, animalLeaving);

      shelter.removeAnimal(animalLeaving);

  }
  //Print Dogs
  else if(userInput=="5")
  {
      shelter.printDogs();
  }

  //Print Cats
  else if(userInput=="6")
  {
      shelter.printCats();
  }

  //Print All
  else if(userInput=="7")
  {
      shelter.printInOrder();
  }

  //Peek
  else if(userInput=="8")
  {
    cout << "This is the animal that has been at the shelter the longest and needs a little extra love! " << endl;
    shelter.peek();
  }

  //find median
  else if(userInput=="9")
  {
    int tempM = shelter.getMedian();
    cout << "The average time an animal spends in our shelter is: " << tempM << " days" << endl;
  }
  //Quit
  else if(userInput=="10")
  {
    cout << "Goodbye!" << endl;
    break;
  }
 }
}
