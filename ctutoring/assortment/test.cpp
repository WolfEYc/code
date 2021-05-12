#include <iostream>
using namespace std;

void change (int &n){

    n = 4;
}


int main(){

    int number = 10;

    cout << number << endl;

    change (number);

    cout << number << endl;

}