#include <iostream>
using namespace std;

struct node{
    int val;
    node* next=nullptr;
};

int largest(node* root){    
    if(root->next==NULL){
        return root->val;
    }else{
        if(root->val > root->next->val){
            root->next = root->next->next;
            return largest(root);
        }else{
            return largest(root->next);
        }
    }   
}

void addnode(node* root,int data){
    if(root->next == nullptr){
        root->next = new node;
        root->next->val = data;
    }else addnode(root->next,data);
}

int main(){

    node* head = new node;
    head -> val = 9;
    addnode(head,12);
    addnode(head,14);
    addnode(head,3);

   
    cout << largest(head)<<endl;
    cout << largest(head)<<endl;
    
    return 0;
}