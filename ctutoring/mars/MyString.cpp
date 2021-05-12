// TODO: Implement this source file
#include <iostream>
#include "MyString.h"

using namespace std;

size_t my_strlen (const char* ptr){
  int len = 0;
  while(ptr[len] != '\0') {
    len++;
  }
  return len;
}

void my_strcpy(char * &ptr_dest,const char* ptr_src, int n ){
  int i;
  for(i=0; i < n; i++) {
    ptr_dest[i] = ptr_src[i];
  }
  ptr_dest[i] = '\0';
}

// Define Method of class My String
MyString::MyString(){
  this->strSize = 0;
  this->strCap = 0;
  this->pointer = new char;
}

MyString::MyString(const char* str)
{
  if (str == nullptr) {
    this->pointer = new char;
    this->strSize = 0;
    this->strCap = 0;
  }
  else {
    this->strSize = my_strlen(str);
    this->strCap = strSize + 1;
    this->pointer = new char[my_strlen(str) + 1];
    // Copy character of val[]
    // using strcpy

    my_strcpy(pointer, str,strSize);
    cout << "The string passed is: "
         << pointer << endl;
  }
}

MyString::MyString(const MyString& str){
  this->strSize = str.size();
  this->strCap = str.capacity();
  this->pointer = new char[str.capacity()];
  my_strcpy(pointer, str.data(), strSize);
}

MyString::~MyString(){
  if (pointer != nullptr)
    delete [] pointer;
}

void MyString:: resize (size_t n){
  char *temp = new char[strCap + 1];
  my_strcpy(temp, pointer, strCap);

  if(pointer != nullptr)
    delete[] this->pointer;

  this->pointer = new char[n + 1];
  if (n > strCap){
    my_strcpy(pointer, temp, strSize);
   // for (int i=strCap+1; i<n; i++){
    //  pointer[i] = '\0';
   // }
   strCap = n;
  } else {
    my_strcpy(pointer, temp, n);
    strSize = n+1;
  }

  delete [] temp;
}

size_t MyString::capacity() const noexcept {
  return strCap;
}

size_t MyString::size() const noexcept {
  return strSize;
}

size_t MyString::length() const noexcept {
  return strSize;
}

const char* MyString::data() const noexcept {
  return pointer;
}

bool MyString::empty() const noexcept {
  if (strSize == 0)
    return true;
  else
    return false;
}

const char& MyString::front() const {
  if(pointer == nullptr)
    throw std::exception();
  return pointer[0];
  
}

const char& MyString::at (size_t pos) const {
  if(pos>=strSize)
    throw std::exception();
  return pointer[pos];
}

void MyString::clear() noexcept {
  if(strSize > 0){
    delete[] pointer;
    this->pointer = new char[1];
    this->pointer[0] = '\0';
    strSize = 0;
    strCap = 0;
  }
}

ostream& operator << (ostream& os, const MyString& str) {
  if(str.pointer != nullptr)
    os << str.data();
  return os;
}

MyString& MyString::operator= (const MyString& str) {
  delete [] pointer;
  strSize = str.size();
  strCap = str.capacity();
  pointer = new char[strCap+1];
  my_strcpy(pointer, str.data(), strSize);
  return *this;
}

MyString& MyString::operator+= (const MyString& str) {
  size_t oldSize = strSize;
  resize(strCap + str.capacity());
  for (size_t i=0; i< str.length(); i++) {
    pointer[i+oldSize] = str.data()[i];
  }
  strSize += str.strSize;
  return *this;
}

size_t MyString::find (const MyString& str, size_t pos) const noexcept{
  if (pos > strSize || str.strSize > strSize){
    return -1;
  } else {
      size_t i = pos;
      size_t j = 0;
      size_t yes = 0;
      while (i+j <= strSize -1 && j < str.strSize){
        if( pointer[i + j] == str.pointer[j] ){
          yes++;
          if (yes == str.strSize){
            return i;
          }
          j++;
        } else {
          yes = 0;
          j = 0;
          i++;
        }
      }
      return -1;
  }
  return -1;
}