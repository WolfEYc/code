#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
class student{
    private:
        std::string fname;
        std::string lname;
        int PSID;
        int ngrades;
        int *grades;

    public:
        student(const std::string& _fname, const std::string& _lname, int _PSID, int _ngrades);
        student(const student& objToCopy);
        student& operator= (const student & RHS);
        ~student();
        void setGrades();
        void print() const;
};

#endif