#include "Pet.h"

Pet::Pet() : name(""){}

Pet::Pet(string name) : name(name) {}

string Pet::getName(){
    return name;
}

void Pet::setName(string name){
    this->name = name;
}

void Pet::print(){
    cout << "Name: " << name << endl;
}
