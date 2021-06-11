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
    vector<string> p_expressions;
    vector<string> expressions;
    string labels;
    vector<vector<bool>> table;
    unsigned it;
    vector<Node*> roots;    
public:
    truthtable();    
    void buildTable();
    ~truthtable();
    void clear();
    static void clear(Node* node);
    void addExpression(string expression);
    void generateTree(unsigned exp);    
    void display();
    bool isValid(unsigned exp);
    bool evaluateTree(Node* node);
    bool valueOf(char c);
};
