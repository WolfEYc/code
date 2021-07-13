// header of Pet class
#ifndef PET_H
#define PET_H

#include <string>
#include <iostream>
using namespace std;

class Pet{     // Use the virtual qualifier when needed
public:
   Pet();
   Pet(string);
   string getName();
   void setName(string);
   virtual void print();

private:
   string name;
};


#endif //Pet.h