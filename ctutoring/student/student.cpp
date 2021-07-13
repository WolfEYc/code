#include "student.h"

student::student(const std::string& _fname, const std::string& _lname, int _PSID, int _ngrades) : fname(_fname), lname(_lname), PSID(_PSID), ngrades(_ngrades), grades(new int[_ngrades]){}

student::student(const student& objToCopy){
    *this = objToCopy;
}

student& student::operator= (const student& RHS){
    delete[] grades;
    
    fname = std::string(RHS.fname);
    lname = std::string(RHS.lname);
    PSID = int(RHS.PSID);
    ngrades = int(RHS.ngrades);
    grades = new int[RHS.ngrades];
    
    for(int i = 0; i < ngrades; ++i)
        grades[i] = RHS.grades[i];

    return *this;
}

student::~student(){
    delete[] grades;
}
void student::setGrades(){
    for(int i = 0; i < ngrades; ++i)
        std::cin >> grades[i];
}
void student::print() const{
    std::cout << fname << " " << lname << " " << PSID << " ";
    for(int i = 0; i < ngrades; ++i)
        std::cout << grades[i] << " ";
    std::cout << std::endl;
}