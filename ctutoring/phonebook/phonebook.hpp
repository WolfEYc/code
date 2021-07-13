#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <iostream>
#include <string>

using namespace std;

struct contact
{
    bool available;
    string name;
    string phoneNumber;
    string email;
};

class phonebook
{
  private:
    int numberOfContacts = 0;
    int size = 0;
    struct contact *myContacts = nullptr;

  public:
    phonebook(const int);
    phonebook(const phonebook &);
    phonebook &operator=(const phonebook &);
    int getnumberOfContacts() const;
    int getSize() const;
    void addContact(const string, const string, const string);
    void removeContact(const string);
    void print() const;
    bool operator==(const phonebook&);
    ~phonebook();
};

#endif