#include <bits/stdc++.h>
using namespace std;

struct Node{
    char data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char data){
        this->data = data;
    }  
};

class truthtable{
private:
    string expression;
    string labels;
    vector<vector<bool>> table;
    unsigned it;
    Node* root;    
public:
    truthtable(string expression);
    ~truthtable();
    void clear();
    static void clear(Node* node);
    void generateTree();    
    void display();
    bool isValid();
    bool evaluateTree(Node* node);
    bool valueOf(char c);
};
