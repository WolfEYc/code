#include <string>
#include <iostream>
using namespace std;

#include "Pet.h"
#include "Dog.h"

int main()
{
   Dog vdog;
   Pet vpet;
   vdog.setName("Tiny");
   vdog.setBreed("Great Dane");
   vpet = vdog;
   vpet.print();
   
   Pet *ppet;
   Dog *pdog;
   pdog = new Dog;
   pdog->setName("Tiny");
   pdog->setBreed("Great Dane");
   ppet = pdog;
   ppet->print();
   pdog->print();
   return 0;
}
