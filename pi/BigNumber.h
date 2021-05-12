#include <string>
#include <iostream>
using namespace std;

class BigNumber {
private:
    string num;
public:
    string operator + (BigNumber n);
    string operator - (BigNumber n);
    string operator * (BigNumber n);
    string operator / (BigNumber n);
    void operator = (BigNumber n);
    void operator = (double n);
    void operator = (string n);
    void moveDec(int where);
    string toString();
};

void BigNumber::moveDec(int where){
    int index = num.find('.');

    //adds extra 0's
    while((index+where)>=int(num.size()-1))
        num+='0';    
    while(index+where <= 0){
        num='0'+num;
        index++;
    }
    
    //shift and replace
    if(where > 0)
        for(int i = index;i<index+where;i++)
            num[i] = num [i+1];
    else
        for(int i = index;i>index+where;i--)
            num[i] = num [i-1];    
    num[index+where]='.';        
}

string BigNumber::operator + (BigNumber n){
    string nstring = n.toString();
    string result = "";
    while(!nstring.empty() && !num.empty()){
        int d1 = nstring[nstring.size()-1]-48, d2 = num[num.size()-1]-48;
        int sum = d1+d2;
        if(sum>=10){//carryout
            
        }
    }
    return result;
}

string BigNumber::operator - (BigNumber n){
    string result;


    return result;
}

string BigNumber::operator * (BigNumber n){
    string result;


    return result;
}

string BigNumber::operator / (BigNumber n){
    string result;


    return result;
}

void BigNumber::operator = (BigNumber n){
    num = n.toString();
}

void BigNumber::operator = (double n){
    num = to_string(n);
}

void BigNumber::operator = (string n){
    num = n;
}

string BigNumber::toString() {
    return num;
}


