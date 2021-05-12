#include "linked_list.h"
#include <iostream>
#include <string>
using std::cout, std::endl, std::string, std::ostream;

void MyList::add(string name, int score) {
    MyNode* newNode = new MyNode(name, score);
    if(empty()){
        _headPtr->setNext(newNode);
        _tailPtr = newNode;
        _size++;
    }else{
        insert(name,score,size());
    }
}

void MyList::clear() {
    // TODO
    free(_headPtr);
    free(_tailPtr);
    _size = 0;
}

bool MyList::remove(string name) {
    // TODO
    if(empty())
        return false;

    MyNode* curr = _headPtr;
    MyNode* prev = curr;
    while(curr->next() != nullptr){
        prev = curr;
        curr = curr->next();
        if(curr->name() == name){
            prev->setNext(curr->next());
            _size--;
            return true;
        }
    }
    return false;

}

bool MyList::insert(string name, int score, size_t index) {
    // TODO
    if(index < 0 || index > size())
        return false;

    MyNode* curr = _headPtr;
    MyNode* newNode = new MyNode(name,score);
    for(size_t i = 0; i < index; i++){
        curr = curr->next();
    }

    newNode->setNext(curr->next());
    curr->setNext(newNode);
    _size++;
    return true;
}

MyList::MyList()
  : _size(0), _headPtr(new MyNode("",0)), _tailPtr(nullptr) { }

MyList::~MyList() {
    clear();
}

size_t MyList::size() {
    return _size;
}

bool MyList::empty() {
    return _headPtr->next() == nullptr;
}

MyNode* MyList::head() const {
    return _headPtr->next();
}

ostream& operator<<(ostream& os, const MyList& myList) {
    MyNode* _current = myList.head();
    if (_current == nullptr) {
        os << "Linked list is empty" << endl;
        return os;
    }

    while (_current != nullptr) {
        os << "[ " << _current->name() << ", " << _current->score() << " ]" << endl;
        _current = _current->next();
    }
    return os;
}

MyNode::MyNode(std::string name, int score)
    : _name(name), _score(score), _nextPtr(nullptr) {}

std::string MyNode::name()  {
    return _name;
}

int MyNode::score() {
    return _score;
}

void MyNode::setNext(MyNode* other) {
    _nextPtr = other;
}

MyNode* MyNode::next() {
    return _nextPtr;
}
