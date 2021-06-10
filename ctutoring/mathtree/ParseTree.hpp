//
//  ParseTree.hpp
//  LAB 5 2021
//
//  Created by Shawn Kitagawa on 5/27/21.
//

#ifndef ParseTree_hpp
#define ParseTree_hpp
#include <stack>
#include <iostream>
#include <stdio.h>
using namespace std;



class Node
{
private:
    char value;
    Node * right;
    Node * left;
    
public:
    Node (char value)
    {
        this->right = this->left = nullptr;
        this->value = value;
    }
    // setters
    void setRight(Node * right)
    {
        this->right = right;
        
    }
    void setLeft(Node * left)
    {
        this->left = left;
        
    }
    
    //gettters
    Node *getRight()
    {
        return this->right;
    }
    Node *getLeft()
    {
        return this->left;
    }
    
    char getValue()
    {
        return this->value;
    }
    
};


class ParseTree
{
private:
    Node * root;
    
public:
    ParseTree(string expression); 
    
    ~ParseTree();
    
    string preOrder();
    string preOrder(Node* node);
    
    string inOrder();
    string inOrder(Node* node);
    
    string postOrder();
    string postOrder(Node* node);
    
    
    void parseInOrder(string input);
    void generateTree(string postfix);
    
};




#endif /* ParseTree_hpp */


