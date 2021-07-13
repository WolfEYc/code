
// header of Dog class
#ifndef DOG_H
#define DOG_H

#include <string>
#include <iostream>
#include "Pet.h"
using namespace std;

class Dog: public Pet{
public:
   Dog();
   Dog(string, string);
   string getBreed();
   void setBreed(string);
   void print() override;

private:
   string breed;
};


#endif //Dog.h