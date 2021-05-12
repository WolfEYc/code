#include <iostream>
using namespace std;

void printNice(string* A,int size){
    for(int i=0;i<size;i++)
        cout << A[i] << " "; // prints a line after each element in the array
    cout << endl; // puts a line after the function finishes printing the array
}

int main (){

    string Jamielist [] = {"jamie","has", "a" , "new","lenovo", "laptop!"};
    int size = 6;

    string Isaaclist [] = {"Isaac","has", "a" , "External","Ubunutu", "SSD Drive!"};

    printNice(Jamielist,size); // sends Jamielist to the printnice function via parameters

    printNice(Isaaclist,size); // same for the Isaaclist of same size

    return 0;
}
