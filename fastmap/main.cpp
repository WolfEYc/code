#include "tmap.hpp"
#include <chrono>
#include <map>

using Clock = std::chrono::high_resolution_clock;
using T = chrono::_V2::system_clock::time_point;

int64_t nanoduration(T t1, T t2){
    return chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

string gen_random(int len) {
    string s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}


void fasterOutput(int64_t fastmap, int64_t normmap){
    if(fastmap > normmap){
        cout << "normal map speed is ";
        cout << fastmap - normmap;
        cout << " ms faster\n";
    }else{
        cout << "fast map speed is ";
        cout << normmap - fastmap;
        cout << " ms faster\n";
    }
}

void fasterOutput(int64_t fastmap, int64_t normmap){
    if(fastmap > normmap){
        cout << "normal map speed is ";
        cout << fastmap - normmap;
        cout << " ms faster\n";
    }else{
        cout << "fast map speed is ";
        cout << normmap - fastmap;
        cout << " ms faster\n";
    }
}

int main(){

    srand(time(NULL));

    unsigned tests = 10;
    int64_t finput_avg = 0;
    int64_t ninput_avg = 0;
    int64_t fLk_avg = 0;
    int64_t nLk_avg = 0;

    size_t elems = 10000000;
    int strlen = 10;

    cout << "Running test on " << elems << " key/value pairs...\n";

    for(unsigned t = 0; t < tests; ++t){

        tmap<string,int> fmap(elems);
        unordered_map<string,int> nmap;
        vector<string> strs(elems);
        vector<int> vals(elems);


        //generate keys
        for(size_t i = 0; i != elems; i++){
            strs[i] = gen_random(strlen);
            vals[i] = rand();            
        }

        T i_fmap_1 = Clock::now();

        for(size_t i = 0; i != elems; i++){
            fmap[strs[i]] = vals[i];            
        }

        T i_fmap_2 = Clock::now();


        T i_nmap_1 = Clock::now();

        for(size_t i = 0; i != elems; i++){
            nmap[strs[i]] = vals[i];            
        }

        T i_nmap_2 = Clock::now();

        int64_t nmapInputSpeed = nanoduration(i_nmap_1, i_nmap_2);

        int64_t fmapInputSpeed = nanoduration(i_fmap_1, i_fmap_2);


        T l_fmap_1 = Clock::now();

        for(size_t i = 0; i != elems; i++){
            if(fmap.find(strs[i]) == nullptr){
                cout << "Missing key: " << strs[i] << endl;
            }
        }

        T l_fmap_2 = Clock::now();


        T l_nmap_1 = Clock::now();

        for(size_t i = 0; i != elems; i++){
            if(nmap.find(strs[i]) == nmap.end()){
                cout << "Missing key: " << strs[i] << endl;
            }
        }

        T l_nmap_2 = Clock::now();

        int64_t nmapLkSpeed = nanoduration(l_nmap_1, l_nmap_2);

        int64_t fmapLkSpeed = nanoduration(l_fmap_1, l_fmap_2);


        finput_avg+= fmapInputSpeed;  
        ninput_avg+= nmapInputSpeed;
        fLk_avg+= fmapLkSpeed;
        nLk_avg+= nmapLkSpeed;

        cout << t+1 << "/" << tests << endl
        << "Input: ";
        fasterOutput(fmapInputSpeed, nmapInputSpeed);
        cout << "Lookup: ";
        fasterOutput(fmapLkSpeed, nmapLkSpeed);
        cout << endl
        << "Space: ";

        size_t nmap_space = 0;

        for(size_t b = 0; b < nmap.bucket_count(); b++){
            nmap_space += nmap.bucket_size(b) * sizeof(nmap[strs[0]]);
        }

        size_t fmap_space = fmap.calcMemUsage();

        

    }

    finput_avg/=tests;
    ninput_avg/=tests;
    fLk_avg/=tests;
    nLk_avg/=tests;

    cout << endl << endl
    << "Average Input Winner:\n";
    fasterOutput(finput_avg, ninput_avg);

    cout << endl
    << "Average Lookup Winner:\n";
    fasterOutput(fLk_avg, nLk_avg);

    return 0;
}
