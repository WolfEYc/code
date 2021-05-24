#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

using namespace sf;

void printVector2f(Vector2f v){
    std::cout << "("<< v.x << "," << v.y << ")" << std::endl;
}

int main(){

    /*
    Vector2f midpoint (5.f,5.f), origin (3.f,2.f);

    Vector2f myendpt, otherendpt, weirdpt;

    myendpt.x = midpoint.x + (midpoint.x - origin.x);
    myendpt.y = midpoint.y + (midpoint.y - origin.y);

    otherendpt = midpoint + (midpoint - origin);
    
    weirdpt = (2.f,2.f)*midpoint-origin;

    printVector2f(myendpt);
    printVector2f(otherendpt);
    printVector2f(weirdpt);
    */

   unsigned b = 0;

   std::cout << !b << std::endl;

   b++;

   std::cout << !b << std::endl;

   return 0;
}
