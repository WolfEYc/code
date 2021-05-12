#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int letNum(char letter)
{
    if(letter > 96)
        return letter - 87;
    else if (letter > 64)
        return letter - 55;
    else
        return letter - 48;
}
char numLet(int num)
{
    if (num < 10)
        return num + 48;
    else
        return num + 55;
}
string hexToDec(string hex)
{
    int num = 0;
    for (int i = 0; i < hex.length(); i++)
        num += (letNum(hex[i]) * pow(16, hex.length() - i - 1));
    return to_string(num);
}
string decToHex(string dec)
{
    string out = "";
    long long num = stoll(dec);
    if(num<0)
        num += 4294967296;    
    while (num > 0) {
        out = numLet(num % 16) + out;
        num /= 16;
    }
    return out;
}
string decToBinary(string dec){
    long long num = stoll(dec);
    string out = "";  
    if(num<0){
        string bean = decToBinary(to_string(-1*num));
        if(bean.length()>16){
            out = "11111111111111111111111111111111";
        }else if(bean.length()>8){
            out = "1111111111111111";
        }else{
            out = "11111111";
        }        
        for(int i=0;i<bean.length();i++)
            if(bean[i]=='1')
                out[out.length()-bean.length()+i]='0';
        for(int i=out.length();i>0;i--){
            if(out[i]=='0'){
                out[i]='1';
                break;
            }
            out[i]='0';
        }
        return out;
    }   
    while (num > 0) {
        out = to_string(num % 2) + out;
        num /= 2;
    }    
    return out;
}
string biToDec(string bi){
    for(int i = 0; i<bi.length();i++)
        if(bi[i]!='0' && bi[i]!='1')
            return "invalid number";
    bool neg = 0;    
    if(bi.length()%8==0 && bi[0]=='1' && bi.length()!=24){
        neg=1;
        int i;
        while(bi.length()>0){
            if(bi[0]=='0')
                break;
            bi=bi.substr(1);
        }
        for(i = 0;i<bi.length();i++)
            if(bi[i]=='0')
                bi[i]='1';
            else
                bi[i]='0';          
        for(i=bi.length()-1;i>=0;i--){
            if(bi[i]=='0'){
                bi[i]='1';
                i = -2;
                break;
            }
            bi[i]='0';
        }        
        if(i!=-2)
            bi = '1'+bi;                
    }
    long long num = 0;
    long long c = 1;
    for(int i=bi.length()-1;i>=0;i--,c*=2)      
        num+=letNum(bi[i])*c;   
    return (neg==0) ? to_string(num) : "-"+to_string(num);
}



int main(int argc, char **argv){
    try{
        string from = argv[1],to = argv[2], num = argv[3];    
        if (from == "hex")
            if(to=="dec")
                cout << hexToDec(num);
            else
                cout<< decToBinary(hexToDec(num));
        if (from == "dec")
            if(to=="hex")
                cout << decToHex(num);
            else
                cout<< decToBinary(num);
        if(from == "bi")
            if(to=="dec")
                cout << biToDec(num);
            else
                cout << decToHex(biToDec(num));
    }catch(...){
        cout << "./main (from) (to) (number)";
    }
    cout << endl;
}
