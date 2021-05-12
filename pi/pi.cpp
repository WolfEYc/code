#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

int main(){
    srand(time(NULL));
    
    unsigned long long int n,numInCircle=0;
    long double four = 4.0;
    cout << "depth: " << setprecision(100);
    cin >> n;

    for(int i=1;i<=n;i++){
        float x = float(rand())/RAND_MAX;
        float y = float(rand())/RAND_MAX;
        if(x*x+y*y<=1)
            numInCircle++;
    }
    cout << four*numInCircle/n << endl;

    return 0;
}