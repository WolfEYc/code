#include <bits/stdc++.h>
using namespace std;

class Movie {
private:
    int numActors; string *actors; string director;
public:
    bool isInMovie(const string& actor) const;
    void printActors() const;
    void readActors(); //populates the actors array 
    void setDirector(string dr);
    string getDirector() const;
    Movie();
    Movie(int nA);
    ~Movie();
};

Movie::Movie(){
    numActors=10;//default constructor
    director="";//empty string""
    actors= new string [numActors];//dynamical allocate an array of size numActors
}

bool Movie::isInMovie(const string& actor) const{
    for(int i=0;i<numActors;i++){
        if(actors[i]==actor)//[] array
        {
            return true;
        }
    }
    return false;//he's not in the movie
}

void Movie::setDirector(string dir){
    director = dir;
}

string Movie::getDirector() const{ return director; }

void Movie::printActors() const{
    for(int i = 0; i < numActors; i++)
        cout << actors[i] << endl;
}