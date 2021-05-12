/*
    step 1: define abstract class Exercises with virtual workoutType() method
    step 2: define child classes that inherit Exercsies and override the workoutType() method
    step 3: define pointer objects in main of each child class
    step 4: run workoutType() methon for each object
*/

#include <bits/stdc++.h>
using namespace std;

class Exercises{
public:
    virtual void workoutType() const {}
};

class Burpees : public Exercises{
public:
    void workoutType() const override{
        cout << "Burpees: full body exercise." << endl;
    }
};

class Lunges : public Exercises{
public:
    void workoutType() const override{
        cout << "Lunges: lower body exercise." << endl;
    }
};

class BenchPress : public Exercises{
public:
    void workoutType() const override{
        cout << "Bench Press: upper body exercise." << endl;
    }
};

int main(){

    Exercises* burpees = new Burpees();
    Exercises* lunges = new Lunges();
    Exercises* benchPress = new BenchPress();

    cout << endl;
    burpees->workoutType();
    lunges->workoutType();
    benchPress->workoutType();
    cout << endl;


    return 0;
}