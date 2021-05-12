#include <bits/stdc++.h>
using namespace std;

class Multiplier{
protected:
    int size;
    int* arr;
public:
    Multiplier(){
        size = 0;
        arr = nullptr;
    }
    virtual void print(){}
};

class Tripler : public Multiplier{
public:
    Tripler(int s, int* a){
        arr = new int[s];
        size = s;
        for(int i = 0; i < s; i++)
            arr[i] = a[i]*3;
    }
    void print() override {
        for(int i = 0; i < size; i++)
            cout << arr[i]*2 <<" ";
        cout << endl;
    }
};

class Doubler : public Multiplier{
public:
    Doubler(int s, int* a){
        arr = new int[s];
        size = s;
        for(int i = 0; i < s; i++)
            arr[i] = a[i]*2;
    }
    void print(){
        for(int i = 0; i < size; i++)
            cout << arr[i] <<" ";
        cout << endl;
    }
};


int main(){

    int n;
    cout << "How many numbers would you like to enter? ";
    cin>>n;
    cout << "Enter " << n << " numbers seperated by a space:\n";
    int arr[n];
    for(int i = 0; i<n;i++)
        cin >> arr[i];

    Multiplier* mult[2];
    mult[0] = new Tripler(n, arr);
    mult[1] = new Doubler(n, arr);

    cout << "Doubled Array:\n";
    mult[1]->print();
    cout << "Tripled Array:\n";
    mult[0]->print();

    return 0;
}