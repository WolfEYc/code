#include <bits/stdc++.h>
using namespace std;

class Book {
private:
    string title;
    string author;
    string publisher;
    int year;
    string edition;

public:
    Book();  //default_construction
    Book(string title, string author, string publisher,
         int year, string edition);

    //mutators_change the data in private
    void settitle(const string &title);//address of string.do not change address
    void setauthor(const string &author);

    void setpublisher(const string &publisher);//
    void setyear(int year);

    void setedition(const string &edition);

    //accessors_access data in private
    string gettitle() const;

    string getauthor() const;

    string getpublisher() const;

    int getyear() const;

    string getedition() const;

};

Book::Book(){
    this->title = "";
    this->author = "";
    this->edition = "";
    this->publisher = "";
    this->year = 0;
}

Book::Book(string title, string author, string publisher,
         int year, string edition)
{
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->edition = edition;
}



