#include "truthtable.hpp"

void truthtable::clear(Node* node){
    if(node == nullptr)
        return;

    clear(node->left);
    clear(node->right);

    delete node;
}

bool truthtable::valueOf(char c){
    return table[labels.find(c)][it];
}

bool areBracketsBalanced(string expr)
{ 
    stack<char> s;
    char x;
 
    // Traversing the Expression
    for (unsigned i = 0; i < expr.length(); i++)
    {
        if (expr[i] == '(' || expr[i] == '['
            || expr[i] == '{')
        {
            // Push the element in the stack
            s.push(expr[i]);
            continue;
        }
 
        // IF current current character is not opening
        // bracket, then it must be closing. So stack
        // cannot be empty at this point.
        if (s.empty())
            return false;
 
        switch (expr[i]) {
        case ')':
             
            // Store the top element in a
            x = s.top();
            s.pop();
            if (x == '{' || x == '[')
                return false;
            break;
 
        case '}':
 
            // Store the top element in b
            x = s.top();
            s.pop();
            if (x == '(' || x == '[')
                return false;
            break;
 
        case ']':
 
            // Store the top element in c
            x = s.top();
            s.pop();
            if (x == '(' || x == '{')
                return false;
            break;
        }
    }
 
    // Check Empty Stack
    return (s.empty());
}

int prec(char c){
    switch (c){ 
        case '-':
            return 5;      
        case '^':
            return 4;                    
        case '*':
            return 3;
        case '+':
            return 2;
        case '>':
            return 1;
        case '=':
            return 0;
    }
    return -1;
}

bool isOperand(char c){
    return (60 <= int(c) && int(c) <= 90) || (97 <= int(c) && int(c) <= 122);
}

bool isOperator(char c){
    switch(c){
        case '^':               
        case '>':
        case '+':
        case '*':
        case '=':
        case '-':
            return 1;
    }
    return 0;
}

bool isParenthesis(char c){
    return c == '[' || c == ']';
}

bool validChar(char c){
    return isOperator(c) || isOperand(c) || isParenthesis(c) || c == '-';
}

string inToPost(string input)
{
    stack<char> st;
    string buffer = "";
    char next;

    for(size_t i = 0; i < input.length(); i++){
        next = input[i];

        if(isOperand(next))
            buffer += next;
        else if (next == '[')
            st.push('[');
        else if (next == ']'){
            while(!st.empty() && st.top() != '[')
            {                  
                buffer += st.top();
                st.pop();
            }
            st.pop();
        }else{
            while(!st.empty() && prec(input[i]) < prec(st.top())) {                
                buffer += st.top();
                st.pop();
            }
            st.push(next);
        }
                
    }

    while(!st.empty()){
        buffer += st.top();
        st.pop();
    }

    return buffer;

}

void truthtable::generateTree(){

    clear(root);
    stack<Node*> theStack;
    for (size_t i = 0; i < postfix.length(); i++)
    {       
        
        char letter = postfix[i];
        
        if (isOperand(letter)){
            theStack.push(new Node(letter));
        }            
        else
        {
            Node* temp = new Node(letter);
               
            temp->right = theStack.top();
            theStack.pop();

            if(letter != '-'){
                temp->left = theStack.top();
                theStack.pop();
            }

            theStack.push(temp);
            
        }
        
    }
    if(!theStack.empty())
        root = theStack.top();
}

void truthtable::buildTable(){
    labels = "";
    for(char c : expression)
        if(isOperand(c) && labels.find(c) == string::npos)
            labels+=c;
    
    unsigned size = 1 << labels.length();     

    table = vector<vector<bool>> (labels.length() + 1, vector<bool>(size));

    for(unsigned l = 0; l < table.size() - 1; l++){
        bool mine = 0;
        unsigned flip = (1 << l);      
        for(unsigned b = 0; b < size; b++){
            if(!(b % flip))
                mine = !mine;  
            table[table.size() - 2 - l][b] = mine;
        }        
    }    
    
    generateTree();

    for(it = 0; it < size; it++)
        table[table.size()-1][it] = evaluateTree(root);
}

truthtable::truthtable(){};

void truthtable::setExpression(string expression){this->expression = expression, this->postfix = inToPost(expression);}

truthtable::truthtable(string exp){
    this->expression = exp;
    this->postfix = inToPost(exp);
}

truthtable::~truthtable(){
    clear(root);
}

bool truthtable::isValid(){
    if(!areBracketsBalanced(expression))
        return 0;
    
    for(char c : expression)
        if(!validChar(c))
            return 0;

    return 1;
        
}

bool truthtable::evaluateTree(Node* node){
    if(node == nullptr || node->data == '\0')
        throw exception();

    if(isOperand(node->data))
        return valueOf(node->data);

    if(node->data == '-')
        return !evaluateTree(node->right);

    if(isOperator(node->data)){
        switch(node->data){
            case '^':
                return evaluateTree(node->left) and evaluateTree(node->right);
            case '+':
                return evaluateTree(node->left) or evaluateTree(node->right);
            case '*':
                return evaluateTree(node->left) xor evaluateTree(node->right);
            case '>':
                if(evaluateTree(node->left))
                    return evaluateTree(node->right);
                return 1;
            case '=':
                return evaluateTree(node->left) == evaluateTree(node->right);
        }
    }

    //should have returned at some point!!!
    throw exception();
    
}

void truthtable::display(){
    //print lables
    cout << endl;

    for(char c : labels)
        cout << c << " ";
    cout << expression << endl;

    for(unsigned row = 0; row < table[0].size(); row++){
        for(unsigned col = 0; col < table.size(); col++){
            cout << table[col][row] << " ";
        }
        cout << endl;
    }

    cout << endl;
    
    
}