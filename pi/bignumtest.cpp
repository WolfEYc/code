#include "BigNumber.h"
#include <iostream>
using namespace std;

int main (){
    BigNumber n;

    n = 2.0;

    cout << n.toString() << endl;

    n.moveDec(-3);

    cout << n.toString() << endl;

    return 0;
}