#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int nva=0, nextA=0, nextB=0, comps=0,A,B,C,D,E,F,G,H,I,J,K,L,M,N,O;

bool Tc1(){
    return A==B+C+E+F;
}

bool c1(){
    return A>D-21;
}

bool c2(){
    return D>E+21;
}

bool c3(){
    nva++;
    float a = ((D*D-417)/(E*E));
    A=int(a);
    return a-A==0 && A>3 && A<=50 && D*D==E*E*A+417;
}

bool c4(){
    return E+F<A;
}

bool c5(){
    return H*J+E*12==pow(G+I,2);
}

bool c6(){
    nva++;
    float g = F-sqrt(A+D+1);
    G = int(g);
    return  g-G==0 && G>0 && G<=50 && A+D==pow(F-G,2)-1;
}

bool c7(){
    return 4*J==pow(G,2)+39;
}

bool c8(){
    return pow(I-G,9)==pow(F-H,3);
}

bool c9(){
    nva++;
    float c = (G-pow((1+F*G*G-F),1.0/2))/(1-F);
    C = int(c);
    B = A-C-E-F;
    return c-C==0 && C>0 && Tc1() && pow(G-C,2)==F*C*C+1;
}

bool cI(){
    float i = pow(F-H,1.0/3.0)+G;
    I=int(i);
    nva++;
    return (i-I==0) && i>0 && i<=50;    
}

bool cJ(){
    float j = (G*G+39)/4;
    J=int(j);
    nva++; 
    return j-J==0 && J>0 && J<=50;
}

bool c10(){
    float k = sqrt(2*M+6);
    K = int(k);
    nva++;
    return k-K==0 && K>0 && K<=50 && 2*M==K*K-6 && M+O==K*K-10;;
}

bool c12(){
    float n = sqrt(M*M+291);
    N = int(n);
    nva++;
    return n-N==0 && N<=50 && N>0 && pow(N-O,3)+7 == (F-I)*N && N*N==M*M+291;
}

bool c15(){
    return pow(L,3)+I==(L+B)*K;
}

bool pA(){
    int runCount = 0;
    for(D=50;D>0;D--,nva++){
        for(E=2;E<=50 && c2();E+=2,nva++){           
            if(c3()){
                if(runCount<nextA)
                    runCount++;
                else{
                    B=A+20-D;
                    C=1;
                    F=D-E-21;
                    nva+=3;
                    return 1;
                }
            }
        }
    }    
    return 0;
}
bool pB(){
    int runCount = 0;
    for(H=1;H<=50;H++,nva++){        
        if(c6() && cJ() && c9() && cI() && c5()){
            if(runCount<nextB)
                runCount++;
            else return 1;                
        }
    }
    nextA++;
    if(pA())
        return pB();
    return 0;
}
bool pC(){
    O=sqrt(G*H*I*B+133);    
    for(M=47;M>0;M--,nva++){
        for(L=0;L<=50 && c10() && c12();L++,nva++){
            if(c15()){                
                return 1;
            }
        }
    }
    nextB++;
    if(pB())
        return pC();
    return 0;
}
void run(char prob,ostream &out){
    cout << "Problem "<< prob <<" ----------------------------"<<endl;
    switch(prob){
        case 'a':
            if(pA()){
                cout << "A: "<<A<<", B: "<<B<<", C: "<<C<<", D: "<<D<<", E: "<<E<<", F: "<<F<<endl<<"nva: "<<nva<<endl;
                pB(), pC();
                break;
            }
        case 'b':
            if(pA() && pB()){
                cout << "A: "<<A<<", B: "<<B<<", C: "<<C<<", D: "<<D<<", E: "<<E<<", F: "<<F<<", G: "<<G<<", H: "<<H<<", I: "<<I<<", J: "<<J<<endl<<"nva: "<<nva<<endl;
                pC();
                break;
            }
        default:
            if(pA() && pB() && pC()){
                cout << "A: "<<A<<", B: "<<B<<", C: "<<C<<", D: "<<D<<", E: "<<E<<", F: "<<F<<", G: "<<G<<", H: "<<H<<", I: "<<I<<", J: "<<J<<", K: "<<K<<", L: "<<L<<", M: "<<M<<", N: "<<N<<", O: "<<O<<endl<<"nva: "<<nva<<endl;
                break;
            }
            cout << "no solution exists"<<endl;
            out << "no solution exists";
            return;
    }
    out <<"A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,nva\n";
    out << A << ',' << B << ','<< C << ','<< D << ','<< E << ','<< F << ','<< G << ','<< H << ','<< I << ','<< J << ','<< K << ','<< L << ','<< M << ','<< N << ','<< O << ','<< nva;
}    

int main(){
    ofstream out("values.csv");
    char prob;
    cout << "Which CSP to solve? (a,b,c) ";
    cin >> prob;
    run(prob,out);
}
