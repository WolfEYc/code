#include <bits/stdc++.h>
using namespace std;

class Pizza{
protected:
    int size;
    int numToppings;
public:
    Pizza(){
        this->size = 0;
        this->numToppings = 0;
    }
    virtual float getTotal(){return size; }
    virtual void getInput(){}
};

class DeepDishPizza: public Pizza{
public:
    float getTotal() override{
        return numToppings*.5+size*2.5;
    }
    void getInput() override{
        int s;
        cout << "Deep Dish Pizza:\n";
        while(true){            
            cout << "Enter a size (8 or 12 inches): ";
            cin >> s;
            if(s==8 || s == 12) break;
            cout << "Invalid Entry\n";
        }
        this->size = s;
        cout << "Enter the number of Toppings: ";
        cin >> s;
        this->numToppings = s;
    }
};

class RegularPizza: public Pizza{
public:
    float getTotal() override{
        return numToppings*.5+size*1.5; 
    }
    void getInput() override{
        int s;
        cout << "Original Pizza:\n";
        while(true){
            cout << "Enter a size (8, 12, 14, or 16 inches): ";
            cin >> s;
            if(s==8 || s == 12 || s==14 || s==16) break;
            cout << "Invalid Entry\n";
        }
        this->size = s;
        cout << "Enter the number of Toppings: ";
        cin >> s;
        this->numToppings = s;
    }
};

int main(){

    Pizza* deepDishPizza = new DeepDishPizza;
    Pizza* regularPizza = new RegularPizza;

    deepDishPizza->getInput();
    cout << "Total: $";
    printf("%.2f",deepDishPizza->getTotal());
    cout << endl << endl;
    regularPizza->getInput();
    cout << "Total: $";
    printf("%.2f",regularPizza->getTotal());
    cout << endl << endl;
    return 0;
}
