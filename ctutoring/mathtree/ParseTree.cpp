//
//  ParseTree.cpp
//  LAB 5 2021
//
//  Created by Shawn Kitagawa on 5/27/21.
//

#include "ParseTree.hpp"

static void clear(Node* node){
    if(node == nullptr)
        return;

    clear(node->getLeft());
    clear(node->getRight());

    delete node;
}

bool isOperator(char letter)
{
    if (letter == '/' or letter == '*' or letter == '%' or letter == '+' or letter == '-' )
    {
        return true;
    }
    return false;
}

bool isOperand(char letter)
{
    return !isOperator(letter) && letter != '(' && letter != ')';
}

bool isAddorSub(char letter){
    return letter == '-' || letter == '+';
}

bool higherPrec(char first, char second){
    return (first=='*' || first=='/') && (second == '+' || second == '/');
}

void ParseTree::generateTree(string expression){
    clear(root);
    stack<Node*> theStack;
    for (size_t i = 0; i < expression.length(); i++)
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
    if(!theStack.empty())
        root = theStack.top();
}

ParseTree::ParseTree(string expression){
    root = nullptr;
    generateTree(expression);
}
    
ParseTree::~ParseTree()
{
    clear(root);
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
    
    return node->getValue() + preOrder(node->getLeft()) + preOrder(node->getRight());
}

string ParseTree::inOrder(Node* node)
{
    if(node==nullptr)
        return "";
    
    if(isAddorSub(node->getValue()))
        return '(' + inOrder(node->getLeft()) + node->getValue() + inOrder(node->getRight()) + ')';

    return inOrder(node->getLeft()) + node->getValue() + inOrder(node->getRight());
    
}

string ParseTree::postOrder(Node* node)
{
    if(node==nullptr)
        return "";
    
    return postOrder(node->getLeft()) + postOrder(node->getRight()) + node->getValue();
}

void ParseTree::parseInOrder(string input)
{
    stack<char> theStack;
    string buffer = "";
    char next;

    for(size_t i = 0; i < input.length(); i++){
        next = input[i];

        if(isOperand(next))
            buffer+=next;
        else if (next == '(')
            theStack.push(next);
        else if (next == ')'){
            bool isPopping = 1;
            while(!theStack.empty() and isPopping){
                char value = theStack.top();
                theStack.pop();
                if(value == '(')
                    isPopping = 0;
                else
                    buffer+=value;
            }
        }
        else if (isOperator(next)){
            bool isPopping = 1;
            while(!theStack.empty() and isPopping){
                char value = theStack.top();
                theStack.pop();
                if(value == '('){
                    theStack.push(value);
                    isPopping = 0;
                }
                else{
                    if(!higherPrec(value,next)){
                        theStack.push(value);
                        isPopping = 0;                        
                    }else
                        buffer+=value;
                }
            }
            theStack.push(next);
        }         
    }

    while(!theStack.empty()){
        buffer += theStack.top();
        theStack.pop();
    }

    generateTree(buffer);

}