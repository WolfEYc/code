#include "avltree.hpp"
#include <iostream>
#include <cmath>
using namespace std;

template <typename k, typename v>
class fastmap{
private:
    AVLTree<k,v> trees*;
    size_t size;
public:
    fastmap(size_t size){
        this->size = size_t(ceil(log2(size)));
        trees = new AVLTree[this->size];
    }
    size_t hash(k key){
        string s = to_string(key);
        size_t hashval = 0;

        for(char c : s)
            hashval = int(c) << hashval;
        
        return hashval % size;
    }
    v* operator[](k key){
        
    } 


};
