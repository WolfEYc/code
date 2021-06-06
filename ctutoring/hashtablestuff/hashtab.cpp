#include <bits/stdc++.h>
using namespace std;

class hashtable{
private:
    string* table;
    unsigned size;
public:
    hashtable(){
        table = nullptr;
        size = 0;
    }

    void expand(){
        string* newtable = new string[size*2];

        for(unsigned i = 0; i < size; i++){
            newtable[i] = table[i];
        }

        delete[] table;

        table = newtable;
    }

};

int main(){

}