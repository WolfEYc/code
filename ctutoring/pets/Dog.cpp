#include "Dog.h"

Dog::Dog() : Pet(), breed("") {}

Dog::Dog(string name, string breed) : Pet(name), breed(breed) {}

string Dog::getBreed(){
    return breed;
}

void Dog::setBreed(string breed){
    this->breed = breed;
}

void Dog::print(){
    Pet::print();
    cout << "Breed: " << breed << endl;
}