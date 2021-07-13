// Add the include guard
#ifndef fixedL
#define fixedL

// Add the libraries needed by your solution
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

struct symbol
{
    char character;
    int frequency;
    string code;
};

// Write the definition of the fixedLengthCoding class
class fixedLengthCoding{
private:
    string message;
    int a_size;
    symbol* s_arr;
public:
    fixedLengthCoding();
    ~fixedLengthCoding();
    string getMessage();
    int getAlphabetSize();
    int readFromFile(const string& filename);
    void createAlphabet();
    void printAlphabet();
    void printHistogram();
    void printCodes();
};

#endif
