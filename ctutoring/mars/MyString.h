// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
using namespace std;

class MyString {

  public:
    size_t strSize = 0;
    size_t strCap = 0;
    char* pointer = nullptr;
    // Default Constructor
    MyString();

    // Copy Constructor
    MyString(const MyString& str);

    // From c-string Constructor
    MyString(const char* str);

    // Destructor
    ~MyString();

    void resize (size_t n);
    size_t capacity() const noexcept;
    size_t size() const noexcept;
    size_t length() const noexcept;
    const char* data() const noexcept;
    bool empty() const noexcept;
    const char& front() const;
    const char& at (size_t pos) const;
    void clear() noexcept;

    MyString& operator= (const MyString& str);
    MyString& operator+= (const MyString& str);
    size_t find (const MyString& str, size_t pos = 0) const noexcept;
    friend ostream& operator << (ostream& os, const MyString& str);
};

#endif
