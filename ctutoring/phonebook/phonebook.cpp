#include "phonebook.hpp"

   // Overloaded Constructor
    phonebook::phonebook(const int size_)
    {
        size = size_;
        if (size < 1)
            size = 1;
        numberOfContacts = 0;
        myContacts = new struct contact[size];
        for (int i=0;i<size;i++)
            myContacts[i].available = true;
    }

    // Write the implementation of the Destructor
    phonebook::~phonebook(){
        delete[] myContacts;
    }
    
    // Write the implementation of the Copy Constructor
    phonebook::phonebook(const phonebook& other){
        *this = other;
    }
    
   // Write the implementation of the copy-assignment operator
    phonebook& phonebook::operator=(const phonebook &other){
        delete[] myContacts;
        size = other.size;
        if (size < 1)
            size = 1;
        numberOfContacts = 0;
        myContacts = new struct contact[size];
        for (int i=0;i<size;i++)
            myContacts[i].available = true;
        for(int i = 0; i < other.numberOfContacts; i++){
            addContact(other.myContacts[i].name, other.myContacts[i].phoneNumber, other.myContacts[i].email);
        }
        
        return *this;
    }
    
    
    
    int phonebook::getnumberOfContacts() const
    {
        return numberOfContacts;
    }

    int phonebook::getSize() const
    {
        return size;
    }

    void phonebook::addContact(const string name, const string phonenumber,const string email)
    {
        if (numberOfContacts == size)
            cout << "The Phonebook is Full!!" << endl;
        else
        {
            for (int i=0;i<size;i++)
            {
                if (myContacts[i].available == true)
                {
                    myContacts[i].name = name;
                    myContacts[i].phoneNumber = phonenumber;
                    myContacts[i].email = email;
                    myContacts[i].available = false;
                    numberOfContacts++;
                    break;
                }
            }
        }

    }
    
    void phonebook::removeContact(const string name)
    {
        if (numberOfContacts == 0)
            cout << "The Phonebook is Empty!!!" << endl;
        else
        {
            bool found = false;
            for(int i=0;i<size;i++)
            {
                if (myContacts[i].name == name)
                {
                    myContacts[i].available = true;
                    numberOfContacts--;
                    cout << name << " was deleted from your Phonebook" << endl;
                    found = true;
                    break;
                }
            }
            if (found == false)
                cout << name << " is not in your PhoneBook" << endl;
        }
        

    }
    
   bool phonebook::operator==(const phonebook& RHS)
   {
      if (this == &RHS)
         return true;
      else
      {
         if(size != RHS.size || numberOfContacts != RHS.numberOfContacts)
            return false;
         else
         {
            for (int i=0;i<size;i++)
            {
               if (myContacts[i].available != RHS.myContacts[i].available || 
                   myContacts[i].name != RHS.myContacts[i].name ||
                   myContacts[i].phoneNumber != RHS.myContacts[i].phoneNumber ||
                   myContacts[i].email != RHS.myContacts[i].email)
                        return false;
            }
            return true;
         }
      }
   }
    
    void phonebook::print() const
    {
        cout << "NAME\t\tPHONE NUMBER\t\tEMAIL\n\n";
        for(int i=0; i < size; i++)
        {
            if (myContacts[i].available == false)
            {
                cout << myContacts[i].name << "\t\t" << myContacts[i].phoneNumber << "\t\t" << myContacts[i].email << endl;
            }
        }
    }