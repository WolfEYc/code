#include <iostream>

using namespace std;

int main() {
   float weight [5];
   
   
   for(int i = 0; i<5; i++)
   {
   
    cout << "Enter weight " + to_string(i+1) + ":\n";
    do
    {
      cin >> weight[i];
    }
    while (!weight[i]);
   
   //cout << weight;
   }
   return 0;
}