#include "avltree.hpp"
#include <functional>
#include <cmath>

template <typename k, typename v>
class tmap{
private:
    AVLTree<k,v>* trees; 
protected:
    hash<k> f;
    int64_t hashf(k key){
        return f(key) % roots;
    }
    v* seed;
    size_t roots;
public:

    //create a tmap optimized for "size" elements
    tmap(int64_t size){
        roots = size;
        trees = new AVLTree<k,v>[roots];
        seed = nullptr;
    }

    //create an unoptimized tmap
    tmap(){
        this->roots = 10;
        trees = new AVLTree<k,v>[this->roots];
        seed = nullptr;
    }

    ~tmap(){
        delete[] trees;
    }

    //allows for insertion and modification just like a normal map
    v& operator[](const k &key){
        trees[hashf(key)].insert(key,seed);
        return *seed;
    }

    //will return pointer to value if found, otherwise returns nullptr
    v* find(const k &key){
        Node<k,v>* node = trees[hashf(key)].find(key);
        return node != nullptr ? node->val : nullptr;
    }

    size_t size() const{
        return roots;
    }

    //returns tree at given index of hashtable, only reccomended for testing purposes
    AVLTree<k,v>& getTree(size_t index){
        if(index >= roots)
            throw new exception;
        return trees[index];
    }

};

template <typename k, typename v>
ostream& operator<<(ostream& os, tmap<k,v>& fastmap){
    for(size_t i = 0; i != fastmap.size(); i++){
        if(fastmap.getTree(i).height()){
            fastmap.getTree(i).output(os);
            os << endl;
        }
    }
    return os;
}
