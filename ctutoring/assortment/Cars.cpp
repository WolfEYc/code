#include <bits/stdc++.h>
using namespace std;

class Car{
public:
    virtual void speak(){}
};

class Toyota : public Car{
public:
    void speak() override {
        cout << "This is a Toyota\n";
    }    
};

class Honda : public Car{
public:
    void speak() override {
        cout << "This is a Honda\n";
    }
};

void drive(Car* car){
    car->speak();
    cout << "Vroom Vroom\n";
}

int main(){
    Car* toyota = new Toyota;
    Car* honda = new Honda;

    toyota->speak();
    honda->speak();

    drive(toyota);
    drive(honda);

    return 0;
}
