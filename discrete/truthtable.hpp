#include <bits/stdc++.h>
using namespace std;

struct Node{
    char data = '\0';
    Node* left = nullptr;
    Node* right = nullptr;
    Node(char data){
        this->data = data;
    }  
};

class truthtable{
private:
    string postfix;
    string expression;
    string labels;
    vector<vector<bool>> table;
    unsigned it;
    Node* root;    
public:
    truthtable();
    truthtable(string exp);
    void buildTable();
    ~truthtable();
    void clear();
    static void clear(Node* node);
    void setExpression(string expression);
    void generateTree();    
    void display();
    bool isValid();
    bool evaluateTree(Node* node);
    bool valueOf(char c);
};
