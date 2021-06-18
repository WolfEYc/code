#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;

#define max 100

int find(char* arr, char c, unsigned n){
    for(unsigned i = 0; i < n; i++)
        if(arr[i] == c)
            return i;
    return -1;
}

int main(){

    unsigned uchars = 0;
    char input[max];

    cin.getline(input,max);

    unsigned strsize = strlen(input);

    char unique[strsize];
    unsigned each[strsize];

    for(unsigned i = 0; i < strsize; i++){
        char c = input[i];

        int index = find(unique, c, uchars);

        if(index == -1){ //first occurrence of char c in input
            unique[uchars] = c;
            each[uchars] = 1;
            uchars++;
        }else{
            each[index]++;
        }
    }


    cout << "Message: " << input << endl
        << "Number of symbols in the alphabet = " << uchars << endl
        << "Characters in the alphabet = ";


    for(unsigned i = 0; i < uchars; i++){
        if(!i)
            cout << unique[i];
        else
            cout << "," << unique[i];
    }

    cout << endl
        << "Number of bits per symbol = " << ceil(log2(uchars)) << endl
        << "Histogram showing the frequency of the symbols in the alphabet\n";

    for(unsigned i = 0; i < uchars; i++){
        cout << unique[i] << " | ";
        for(unsigned e = 0; e < each[i]; e++){
            cout << '*';
        }
        cout << endl;
    }

    return 0;
}
