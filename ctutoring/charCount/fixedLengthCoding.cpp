// Write the implementation of the fixedLengthCoding class member functions here.
#include "fixedLengthCoding.h"

int find(symbol* characters, char c, int n)
{
    for(int i=0; i < n; i++)    
        if(characters[i].character == c)
            return i;
    return -1;
}

fixedLengthCoding::fixedLengthCoding() : message(string()), a_size(0), s_arr(nullptr) {}

fixedLengthCoding::~fixedLengthCoding(){
    delete[] s_arr;
}

string fixedLengthCoding::getMessage(){
    return message;
}

int fixedLengthCoding::getAlphabetSize(){
    return a_size;
}

int fixedLengthCoding::readFromFile(const string& filename){
    ifstream in(filename.c_str());
    if(!in.good())
        return -1;

    string sizestr;
    getline(in, sizestr);
    getline(in, message);

    a_size = stoi(sizestr);

    return 0;
}

void fixedLengthCoding::createAlphabet(){
    s_arr = new symbol[a_size];
    int bits = ceil(log2(a_size));

    char bcode[bits];
    
    for(int i = 0; i < a_size; i++){
        for(int b = 0; b != bits; b++){
            int j = i >> b;
            if(j & 1)
                bcode[b] = '1';
            else
                bcode[b] = '0';
        }        
        string temp = string(bcode);
        reverse(temp.begin(), temp.end());
        s_arr[i].code = temp;
    }


    for(int i = 0, u = 0; i < message.length(); i++){
        char c = message[i];

        int index = find(s_arr, c, a_size);

        if(index == -1)//Unique character found
        {           
            s_arr[u].character = c;
            s_arr[u].frequency = 1;
            u++;
        }
        else{
            s_arr[u].frequency++;
        }
    }
}

void fixedLengthCoding::printAlphabet(){
    for(int i = 0; i < a_size; i++){
        cout << s_arr[i].character;
        if(i != a_size - 1)
            cout << ",";
    }
    cout<< endl;
}

void fixedLengthCoding::printHistogram(){
    cout << "Histogram showing the frequency of the symbols in the alphabet\n";
    for(int i = 0; i < a_size; i++){
        cout << s_arr[i].character << " | ";
        for(int  e = 0; e < s_arr[i].frequency; e++){
            cout << '*';
        }
        cout << endl;
    }

}

void fixedLengthCoding::printCodes(){
    cout << "Fixed-length codes of the symbols in the alphabet\n";
    for(int i = 0; i < a_size; i++){
        cout << s_arr[i].character << " | ";
        cout << s_arr[i].code;
        cout << endl;
    }
}

