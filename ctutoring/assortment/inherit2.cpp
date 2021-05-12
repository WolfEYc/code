#include <bits/stdc++.h>
using namespace std;

class Scores{
protected:
    int numScores;
    double* scores;
public:
    void getScores(){
        cout << "How many scores would you like to enter? ";
        cin >> numScores;
        cout << "Enter 5 scores seperated by a space: ";

        scores = new double[numScores];
        for(int i = 0; i<numScores; i++)
            cin >> scores[i];
        cout << endl;       
    }
    void print(){
        cout << "Assignments Scores:" << endl;
        for (int i = 0; i < numScores; i++)
            cout << "Assignment " << i+1 << ": " << scores[i] << endl;
        cout << endl;
    }
};

class Percentage : public Scores{
protected:
    double percentage;
public:
    void calcPercentage(){
        percentage = 0;

        for(int i = 0; i<numScores; i++)
            percentage += scores[i];

        percentage/=numScores;
        percentage = round(percentage * 10.0)/10.0;
    }
    void print(){
        Scores::print();
        cout << "Total Percentage: " << percentage << "%" << endl;
    }
};

class Grade : public Percentage{
private:
    string lettergrade;
public:
    void calcGrade(){
        if (percentage >= 90.0){
            lettergrade = "A";
        }
        else if (percentage >= 87.0){
            lettergrade = "A-";
        }
        else if (percentage >= 84){
            lettergrade = "B+";
        }
        else if (percentage >= 80){
            lettergrade = "B";
        }
        else if (percentage >= 77)
        {
            lettergrade = "B-";
        }
        else if (percentage >= 74)
        {
            lettergrade = "C+";
        }
        else if (percentage >= 70){
            lettergrade = "C";
        }
        else if (percentage >= 67){
            lettergrade = "C-";
        }
        else if (percentage >= 64)
        {
            lettergrade = "D+";
        }
        else if (percentage >= 60){
            lettergrade = "D";
        }else if (percentage >= 57.0){
            lettergrade = "D-";
        }else{
            lettergrade = "E";
        }        
    }
    void print(){
        Percentage::print();
        cout << "Final Grade: " << lettergrade << endl;
    }
};

int main(){

    Grade grade;

    grade.getScores();
    grade.calcPercentage();
    grade.calcGrade();
    grade.print();

    return 0;
}