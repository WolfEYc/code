#include <bits/stdc++.h>
using namespace std;

class Shape{ //abstract shape class
public:
    virtual void print(){}
    virtual double area(){return 0.0;}
    virtual double perimeter(){return 0.0;}
};

class Rectangle : public Shape{ //derived rectangle class
private:
    double length, width; 
public:
    Rectangle(double len, double wid){ //custom constructor
        length = len;
        width = wid;
    }
    void print() override{ //print override
        cout << "Rectangle of " << length << " X " << width << endl
        << "Area: " << area() << endl
        << "Perimeter: " << perimeter() << endl;
    }
    double area () override{ //area override
        return length*width;
    }
    double perimeter () override{ //perimeter override
        return length*2 + width*2;
    }
};

class Triangle : public Shape{ //derived triangle class
private:
    double a, b, c; //side 1 2 and 3
public:
    Triangle(double s1, double s2, double s3){ //constructor overide
        a = s1;
        b = s2;
        c = s3;
    }
    void print() override{ //print func
        cout << "Triangle of " << a << " X " << b << " X " << c << endl
        << "Area: " << area() << endl
        << "Perimeter: " << perimeter() << endl;
    }
    double area () override{ //area override
        double s = (a+b+c)/2;
        return pow(s*(s-a)*(s-b)*(s-c), .5);
    }
    double perimeter () override{ //perimiter override
        return a+b+c;
    }
};

class Circle : public Shape{ //derived Circle class
private:
    double r; // radius 
public:
    Circle(double radius){ //custom constructor
        r = radius;
    }
    void print() override{ //print override
        cout << "Circle of radius: " << r << endl
        << "Area: " << area() << endl
        << "Perimeter: " << perimeter() << endl;
    }
    double area () override{ //area override
        return r*r*3.14;
    }
    double perimeter () override{ //perimeter override
        return 2*3.14*r;
    }
};

int main(){

    char op;
    do{
        int choice;
        cout << "1-Rectangle\n"
        << "2-Triangle\n"
        << "3-Circle\n"
        << "Choose a shape: ";
        cin >> choice;

        if(choice == 1){ //beep boop
            double len, wid;
            cout << "Enter length and width, seperated by a space: ";
            cin >> len >> wid;
            Shape* s = new Rectangle(len,wid);
            s->print();
            delete s;
        }
        else if (choice == 2){
            double a, b, c;
            cout << "Enter 3 sides, seperated by a space: ";
            cin >> a >> b >> c;
            Shape* s = new Triangle(a,b,c);
            s->print();
            delete s;
        }
        else if (choice == 3){
            double r;
            cout << "Enter a radius (>0.0): ";
            cin >> r;
            Shape* s = new Circle(r);
            s->print();
            delete s;
        }

        cout << "Do it again (y/n)? ";
        cin >> op;

    }while(op == 'y');

    cout << "Goodbye!" << endl;

    return 0;
}

