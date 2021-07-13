#include <iostream>
#include <string>
#include "fixedLengthCoding.h"
using namespace std;

int main()
{
    string filename;
    fixedLengthCoding codes;
    cin >> filename;
    if(codes.readFromFile(filename)==0)
    {
        cout << "Message: " << codes.getMessage() << endl;
        
        codes.createAlphabet();
        cout << "Number of symbols in the alphabet = " << codes.getAlphabetSize() << endl;
        cout << "Characters in the alphabet = ";
        codes.printAlphabet();
        cout << "Number of bits per symbol = " << ceil(log2(codes.getAlphabetSize())) << endl;
        codes.printHistogram();
        codes.printCodes();
        
    }
    else
        cout << "File not found." << endl;
    return 0;
}
