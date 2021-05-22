#include "list.hpp"

#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    List lst;
    lst.pushBack(15);
    lst.pushFront(33);
    lst.pushFront(20);
    lst.pushBack(50);
    lst.pushFront(40);
    lst += 80;
    std::cout << lst;
    std::cout << lst.length() << '\n';
    std::cout << "lst[3]=" << lst[3] << '\n';
    lst[2] = 90;
    std::cout << lst;
    std::cout << "Contains 50: " << lst.contains(50) << '\n'
        << "Contains -10: " << lst.contains(-10) << '\n';
    std::cout << "Remove 50: " << lst.remove(50) << ' ' << lst;
    std::cout << "Remove 80: " << lst.remove(80) << ' ' << lst;
    std::cout << "Remove -10: " << lst.remove(-10) << ' ' << lst;
    lst.pushFront(200);
    lst.pushBack(300);
    lst += 100;
    std::cout << lst;
    lst.remove(200);
    lst -= 40;
    std::cout << lst;
    std::cout << "Copy construction...\n";
    List lst2{lst};
    lst2.remove(90);
    std::cout << lst << lst2;
    std::cout << "Copy assignment...\n";
    lst2 = lst;
    std::cout << lst << lst2;
    lst.pushBack(-400);
    lst2.pushFront(-100);
    lst2 += -200;
    std::cout << lst << lst2;
    std::cout << lst.length() << ' ' << lst2.length() << '\n';
}
