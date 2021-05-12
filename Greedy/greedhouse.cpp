#include <iostream>
using namespace std;
int low (int* A,int N){
    int lowy = 0;
    for(int i=0;i<N;i++)
        if(A[i]<A[lowy])
            lowy = i;
    return lowy;
}
int main(){
    int N,B,A[N],C,L;
    cin >> N >> B;
    for(int i=0;i<N;i++)
        cin >> A[i];
    for(C=0,L=low(A,N); B>=L; C++,B-=A[L],A[L]=INT32_MAX,L=low(A,N));
    cout << C-1 << endl;    
}