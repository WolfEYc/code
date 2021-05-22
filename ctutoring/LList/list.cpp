#include "list.hpp"
#include <iostream>
#include <cstring>

using namespace std;

//Got help from OH
List::List()
    : head(nullptr), len(0)
{}
List::List(const List& other)
    : head(nullptr), len(0) //list(new int[other.len])
{
    //go through entire list
    //use push back for each node 
    for(unsigned i = 0; i < other.length(); i++)
        pushBack(other[i]);
}

void List::clear(){
    if(len != 0){
        Node* curr = head;
        while(curr!=nullptr){
            Node* toDel = curr;
            curr = curr->next;
            delete toDel;
            len--;
        }
    }
}

List::~List() {
    clear();
}

List& List::operator=(const List& other)
{ 
    clear();
    
    for(unsigned i = 0; i < other.length(); i++)
        pushBack(other[i]);

    return *this;
}


unsigned List::length() const { return len; }

void List::pushFront(int data)
{
    /**
     * Adds a new node with the given data to the front of the list.
     *
     * MUST run in constant time.
     */
    Node* new_node = new Node;
    new_node->data = data;

    //if the list is empty make the new node the head 
    if (len == 0) 
    {
        new_node->next = nullptr;
        head = new_node;
    }
    else 
    {
        new_node->next = head;
        head = new_node;
    }
    len++;
        
}


void List::pushBack(int data)
{
    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */ 
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = nullptr;

    if (len == 0)
    {        
        head = new_node;        
    }
    else{
        Node* curr = head;
        while(curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = new_node;
    }

    len++;  
}


void List::operator+=(int data)
{
    /**
     * Adds a new node with the given data to the back of the list.
     *
     * MUST run in constant time.
     */
    pushBack(data);
}


int& List::operator[](unsigned index)
{ 
    if (index >= len)
        throw out_of_range("Index given out of bounds");
    else
    {
        Node* curr_node = head;
        for (unsigned i = 0; i < index; ++i)
            curr_node = curr_node->next;
        
        return curr_node->data;        
    }
}


const int& List::operator[] (unsigned index) const
{
    /**
     * Accesses the element that is @index nodes past the first node in
     * the list.
     *
     * Throws std::out_of_range exception (the message doesn't matter) if
     * given an out-of-range index.
     */
    if (index >= len)
        throw out_of_range("Index given out of bounds");
    else
    {
        Node* curr_node = head;
        for (unsigned i = 0; i < index; ++i)
            curr_node = curr_node->next;
        
        return curr_node->data;        
    }
}


bool List::contains(int data) const
{
    /**
     * Returns true if a node that contains the given data exists in the list.
     * Returns false otherwise.
     */
    Node* cur_node = head;
    while(cur_node != nullptr)
    {
        if (cur_node->data == data)
            return true;
    
        cur_node = cur_node->next;
    }
    return false;
    
}


bool List::remove(int data)
{
    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     * Returns true if a node was removed; returns false otherwise.
     */
    Node* curr = head;
    Node* prev = new Node;
    Node* toDel = prev;
    prev->next = head;
    
    unsigned count = 0;

    while(curr != nullptr)
    {
        if (curr->data == data)
        {
            if(count==0){
                delete toDel;
                head = curr->next;                
            }else
                prev->next = curr->next;
                                                  
            delete curr;
            len--;

            return true;
        }

        prev = curr;
        if(count == 0)
            delete toDel;
        

        curr = curr->next;
        count++;      
    }
    return false;    
}


void List::operator-=(int data)
{
    /**
     * Removes the FIRST occurrence (starting from the front of the list)
     * of a node that contains the given data.
     */
    remove(data);

}


std::ostream& operator<<(std::ostream& os, const List& list)
{
    /**
     * Prints the contents of this list.
     */
    
    //Node* curr_node = list.head;
    for (unsigned i = 0; i < list.length(); i++)
    {
        os << list[i] << ' ';
        
    }
    
    os << '\n';
    return os;

}
