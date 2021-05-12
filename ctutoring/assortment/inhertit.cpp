#include <bits/stdc++.h>
using namespace std;

class Rectangle{
private:
    int length;
    int width;
public:
    Rectangle(){
        length = 0;
        width = 0;
    }
    Rectangle(int len, int wid){
        length = len;
        width = wid;
    }
    int area(){
        return length*width;
    }
    void print(){
        cout << "Length: " << length << endl
        << "Width: " << width << endl;
    }

};

class Cuboid : public Rectangle{
private:
    int height;
public:
    Cuboid():Rectangle(){
        height = 0;
    }
    Cuboid(int l, int w, int h):Rectangle(l,w){
        height = h;
    }
    int volume(){
        return area() * height;
    }
    void print(){
        Rectangle::print();
        cout << "Height: " << height << endl;
    }
};

int main(){

    Rectangle r1;
    Rectangle r2(5,4);

    Cuboid c1;
    Cuboid c2(5,4,8);

    cout << "Rectangle object 1:" << endl;
    r1.print();
    cout << "Area: " << r1.area() << endl;

    cout << "Rectangle object 2:" << endl;
    r2.print();
    cout << "Area: " << r2.area() << endl << endl;

    cout << "Cuboid object 1:" << endl;
    c1.print();
    cout << "Volume: " << c1.volume() << endl;

    cout << "Cuboid object 2:" << endl;
    c2.print();
    cout << "Volume: " << c2.volume() << endl;

    return 0;
}