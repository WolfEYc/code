#include "student.h"

int main(){

    student myStudent("CARLOS", "RINCON", 123456, 4);

    student gayStudent("bob", "builder", 6969, 2);


    myStudent.setGrades();
    myStudent.print();

    gayStudent.setGrades();
    gayStudent.print();

    myStudent = gayStudent;

    myStudent.print();


    return 0;
}