#include <bits/stdc++.h>
using namespace std;

class Employee{
private: //private data members
    string name;
    double salary;
public:
    Employee(){ //default constructor
        name = "unnamed";
        salary = 0.0;
    }
    Employee(string n, double s){ //custom constructor
        name = n;
        salary = s;
    }
    void setName(string newName){ //mutator for name
        name = newName;
    }
    void setSalary(double newSalary){ //mutator for salary
        salary = newSalary;
    }
    string getName(){
        return name;
    }
    double getSalary(){
        return salary;
    }
};

class Company{
private:
    int max;
    int curr;
    Employee* employees;
public:
    Company(int m){
        max = m;
        curr = 0;
        employees = new Employee[max];
    }
    ~Company(){
        delete[] employees;
    }
    void addEmployee(Employee e){ //takes in employee and adds it to the array
        employees[curr] = e;
        curr++;
    }
    float averageSalary(){
        double sum = 0.0;
        for(int i = 0; i < max; i++) //gets the sum of the salaries
            sum += employees[i].getSalary();
        return float(sum / curr); //returns the average
    }
};

int main(){
    int op;
    cout << "\nNumber of employee in the company: ";
    cin >> op;
    Company c(op);
    do{        
        cout << "\nMain menu\n"
        << "1. Add Employee\n"
        << "2. Print average salary\n"
        << "3. Quit\n"
        << "Choose an option: ";
        cin >> op;

        if(op == 1){
            string name;
            double salary;
            cout << "Enter employee name and salary, seperated by a space: ";
            cin >> name >> salary;
            Employee e(name,salary);
            c.addEmployee(e);
        }else if(op == 2){
            cout << "Average salary: $";
            printf("%.2f" , c.averageSalary());
            cout << endl;
        }


    }while(op!=3);

    cout << "Thank you for using this program. Goodbye!\n";

    return 0;
}
