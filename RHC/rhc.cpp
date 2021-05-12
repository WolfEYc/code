#include <iostream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

double F(float x,float y) {
    return (1+ pow(x + y +1,2)*(19-(14*x)+(3*pow(x,2))-(14*y)+(6*x*y)+(3*pow(y,2))))
        *(30+(pow((2*x)-(3*y),2))*(18-(32*x)+(12*pow(x,2))+(4*y)-(36*x*y)+(27*pow(y,2))));
}
struct result{
    pair<float,float> xy; //sol
    double f; //f(sol)
    int sols=0; //#of sols
};
float randy(float cur,int s,float z,int i){//generates random x or y value given constraints
    float higher = cur+(z/(i*s)),lower = cur-(z/(i*s));
    if((i%2==0 || lower<-2) && (higher<=2))
        return higher;
    else
        return lower;    
}
int minIndex (pair<float,float> Sols[],int p){//returns the index with the lowest F(sol)
    int min = 0;
    for(int i=1;i<=p;i++)
        if(F(Sols[i].first,Sols[i].second)<F(Sols[min].first,Sols[min].second))
            min = i;
    return min;
}
result RHC (pair<float,float> sp, int p, float z,int seed){
    //seed will be the number of iterations and used to calulate p neighbors in z    
    result sol;
    sol.xy=sp;    
    for(int s=1;s<=seed;s++){//runs the generator
        pair<float,float> Sols[p+1];//stores each seeds solutions
        Sols[0]=sol.xy;
        for(int i=1;i<=p;i++){//generates each neighboor
            Sols[i].first = randy(sol.xy.first,s,z,i); //this random sols x
            Sols[i].second = randy(sol.xy.second,s,z,i); // and y
            sol.sols++;
        }
        int minInd = minIndex(Sols,p);
        sol.xy=Sols[minInd];
        if(minInd == 0)
            break;
    }
    sol.f = F(sol.xy.first,sol.xy.second);
    return sol;
}
void run(pair<float,float>* sp, int p, float z,ofstream& out){
    int seed1 = rand() % 10000 + 1000, seed2 = rand() % 10000 + 1000;
    out << "p="<<p<<",Run1,Run1,Run1,Run2,Run2,Run2\n";
    out << "z="<<z<<",#sol searched,sol,f(sol),#sol searched,sol,f(sol)\n";
    for(int i=0;i<4;i++){
        result resultsol = RHC(sp[i],p,z,seed1),resultsol2 = RHC(sp[i],p,z,seed2);
        out<<"("<<sp[i].first<<" "<<sp[i].second<<"),"
        <<resultsol.sols<<","<<resultsol.xy.first<<" "<<resultsol.xy.second<<","<<resultsol.f<<"," 
        <<resultsol2.sols<<","<< resultsol2.xy.first<<" "<< resultsol2.xy.second<<","<<resultsol2.f<<"\n";        
    }
    out << "\n";
}
int main (){
    ofstream first("p=30_&_z=0.03.csv"),second("p=30_&_z=0.1.csv")
    ,third("p=120_&_z=0.03.csv"),fourth("p=120_&_z=0.1.csv"),run33("33th.csv");
    srand(time(NULL));

    pair<float,float> sp[5];
    sp[0].first = 0.4;
    sp[0].second = -0.5;
    sp[1].first = -0.5;
    sp[1].second = 0.3;
    sp[2].first = 1;
    sp[2].second = -2;
    sp[3].first = 0;
    sp[3].second = 0;

    run(sp,30,0.03,first);
    run(sp,30,0.1,second);
    run(sp,120,0.03,third);
    run(sp,120,0.1,fourth);
    run(sp,120,2,run33);
}
