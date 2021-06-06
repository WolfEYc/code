//
//  ParseTree.cpp
//  LAB 5 2021
//
//  Created by Shawn Kitagawa on 5/27/21.
//

#include "ParseTree.hpp"

ParseTree::ParseTree(string expression){

    stack<Node*> theStack;
    for (int i = 0; i < expression.length(); i++)
    {
        char letter = expression[i];
        if (isOperand(letter)){
            theStack.push(new Node(letter));
        }            
        else
        {
            Node* temp = new Node(letter);
                
            temp->setRight(theStack.top());
            theStack.pop();

            temp->setLeft(theStack.top());
            theStack.pop();

            theStack.push(temp);
            
        }
        
    }
    root = theStack.top();
}
    
ParseTree::~ParseTree()
{
    clear(root);
}

void clear(Node* node){
    if(node == nullptr)
        return;

    clear(node->getLeft());
    clear(node->getRight());

    delete node;
}

bool ParseTree::isOperand(char letter)
{
    if (letter == '/' or letter == '*' or letter == '%' or letter == '+' or letter == '-' )
    {
        return true;
    }
    return false;
}

string ParseTree::preOrder()
{
    return preOrder(root);
}

string ParseTree::inOrder()
{
    return inOrder(root);
}

string ParseTree::postOrder()
{
    return postOrder(root);
}

string ParseTree::preOrder(Node* node)
{
    if(node==nullptr)
        return "";
    
    return node->getValue() + " " + postOrder(node->getLeft()) + postOrder(node->getRight());
}

string ParseTree::inOrder(Node* node)
{
    if(node==nullptr)
        return "";
    
    return postOrder(node->getLeft()) + node->getValue() + " " + postOrder(node->getRight());
}

string ParseTree::postOrder(Node* node)
{
    if(node==nullptr)
        return "";
    
    return postOrder(node->getLeft()) + postOrder(node->getRight()) + node->getValue() + " ";
}

void ParseTree::parseInOrder(string input)
{
    
}