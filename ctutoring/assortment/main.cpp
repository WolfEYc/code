/*Program Name: Virtual, inheritance!!!!!
Date: April, 13th.*/

/*
•• Business P10.3
Implement a base class Appointment and derived classes Onetime, Daily, Weekly, and Monthly.
An appointment has a description (for example, “see the dentist”) and a date and time.
Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
For example, for a monthly appointment, you must check whether the day of the month matches.
Then fill a vector of Appointment* with a mixture of appointments.
Have the user enter a date and print out all appointments that happen on that date.

•• Business P10.4
Improve the appointment book program of Exercise •• Business P10.3.
Give the user the option to add new appointments.
The user must specify the type of the appointment, the description, and the date and time.

*/


#include <cmath>
#include <vector>
#include <iostream>
using namespace std;



//would like to know how many days are in the month?
int getNDays(int month, int year) {
    if (month == 2) { // if month is feb
        if ((year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0))) // and year is leap year
            return 29; // it will have 29 days
        else // if not leap year
            return 28; // it will have 28 days
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        // if month is apr, jun, sep, nov
        return 30; // it will have 30 days
    }
    else // else for all other months
        return 31; // will have 31 days
}

class Appointment {
private:
    int year, month, Nmaxdays, day, timeh;//0-23
    string description;
public:
    Appointment(int yearset, int monthset, int dayset, int timehset, string descriptionset) {
        year = yearset;
        month = monthset;
        day = dayset;
        timeh = timehset;
        description = descriptionset;

        if (month < 1)
            month = 1;
        else if (month > 12)
            month = 12;
            
        if (day < 1)
            day = 1;
    }

    bool exactmatch(int yeartocheck, int monthtocheck, int daytocheck){
        return (yeartocheck == year && monthtocheck == month && daytocheck == day);
    }
    //when i have monthly appointment, if the date user typed in is not in advance, it's the past appoinment and cannot be a match for the Appointment.
    bool future(int yeartocheck, int monthtocheck, int daytocheck){
        if(yeartocheck > year)
            return true;
        else if (yeartocheck < year)
            return false;
        else if (monthtocheck > month)
            return true;
        else if (monthtocheck < month)
            return false;
        else if (daytocheck > day)
            return true;
        else
            return false;
    }

    void printer() {
        cout << month << '/' << day << '/' << year << '\t' << description << '\n';
    }

    virtual bool occurs_on(int yeartocheck, int monthtocheck, int daytocheck) { //Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
        return exactmatch(yeartocheck, monthtocheck, daytocheck);//yeartochech, monthtocheck, daytocheck entered by user vs. year, month, day are saved as a appointment data already
    }

    
};


class Monthly:public Appointment{
public:
    Monthly(int y,int m,int d,int t,string s):Appointment(y,m,d,t,s){
        
    }

    bool occurs_on(int yeartocheck, int monthtocheck, int daytocheck) { //Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
        if (exactmatch(yeartocheck, monthtocheck, daytocheck))
            return true;
        else
            while (future(yeartocheck, monthtocheck, daytocheck)){
                monthtocheck--;
                if (monthtocheck < 1){
                    monthtocheck = 12;
                    yeartocheck--;
                }
                if (exactmatch(yeartocheck, monthtocheck, daytocheck))
                    return true;
            }
        return false;
    }
};

class Weekly:public Appointment{
public:
    Weekly(int y,int m,int d,int t,string s):Appointment(y,m,d,t,s){
        
    }
    bool occurs_on(int yeartocheck, int monthtocheck, int daytocheck) { //Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
        if (exactmatch(yeartocheck, monthtocheck, daytocheck))
            return true;
        else
            while (future(yeartocheck, monthtocheck, daytocheck)){
                daytocheck-=7;
                if (daytocheck < 1){
                    monthtocheck--;
                    if(monthtocheck < 1){
                        monthtocheck=12;
                        yeartocheck--;
                    }
                    daytocheck +=  getNDays(monthtocheck, yeartocheck);                   
                }
                if (exactmatch(yeartocheck,monthtocheck,daytocheck))
                    return true;
            }
        return false;
    }

};

class Daily:public Appointment{
public:
    Daily(int y,int m,int d,int t,string s):Appointment(y,m,d,t,s){
        
    }
    bool occurs_on(int yeartocheck, int monthtocheck, int daytocheck) { //Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
        
        return future(yeartocheck, monthtocheck, daytocheck) || exactmatch(yeartocheck,monthtocheck,daytocheck);  
        
    }
};

class Onetime:public Appointment{
public:
    Onetime(int y,int m,int d,int t,string s):Appointment(y,m,d,t,s){
        
    }
    bool occurs_on(int yeartocheck, int monthtocheck, int daytocheck) { //Write a virtual function occurs_on(int year, int month, int day) that checks whether the appointment occurs on that date.
        return exactmatch(yeartocheck, monthtocheck, daytocheck);
    }        
};


            int main() {
                int year_entered, month_entered, day_entered, timeh_entered;
                string descriptionstring , ApptType;
                bool thisdateornot;
                vector<Appointment*> biglist;//Then fill a vector of Appointment* with a mixture of appointments. appointment pointer
                biglist.push_back(new Monthly(2022, 4, 15, 3,"first monthly"));//push_back: keep addding in vector one more.New- appointment will be separate and store in biglist.
                biglist.push_back(new Monthly(2023, 3, 25, 5, "second monthly"));
                biglist.push_back(new Monthly(2021, 6, 3, 17, "third monthly"));

                biglist.push_back(new Weekly(2022, 2, 20, 17, "first weekly"));
                biglist.push_back(new Weekly(2021, 8, 13, 21, "second weekly"));
                biglist.push_back(new Weekly(2021, 7, 23, 7, "third weekly"));

                biglist.push_back(new Daily(2023, 2, 20, 17, "only daily"));

                biglist.push_back(new Onetime(2021, 8, 13, 21, "first one time"));
                biglist.push_back(new Onetime(2021, 7, 23, 7, "second one time"));

                //Users are allowed add more appointment in the data book.

                while(true){                   
                    cout << "Enter year (or 0 to stop): \n";
                    cin >> year_entered;
                    if (year_entered==0)
                        break;
                    cout << "Enter month: \n";
                    cin >> month_entered;
                    cout << "Enter day: \n";
                    cin >> day_entered;
                    cout << "Enter hour: \n";
                    cin >> timeh_entered;
                    cout << "Enter description: \n";
                    cin >> descriptionstring;
                    cout << "Enter Daily/Weekly/Monthly/Onetime: \n";
                    cin >> ApptType;

                    //is this Daily or Monthly or OneTime or Weekly?
                    if(ApptType == "Daily")
                        biglist.push_back(new Daily(year_entered,month_entered,day_entered,timeh_entered,descriptionstring));
                    else if (ApptType == "Monthly"){
                        biglist.push_back(new Monthly(year_entered,month_entered,day_entered,timeh_entered,descriptionstring));
                    }else if (ApptType == "Weekly"){
                        biglist.push_back(new Weekly(year_entered,month_entered,day_entered,timeh_entered,descriptionstring));
                    }else if (ApptType == "OneTime"){
                        biglist.push_back(new Onetime(year_entered,month_entered,day_entered,timeh_entered,descriptionstring));
                    }

                }
                /*
                for(unsigned int i = 0; i <biglist.size();i++){
                    biglist[i]->printer();
                }
                */



                
                //User's data to check
                cout << "Enter Appt to check: \n";
                cout << "Enter year: \n";
                cin >> year_entered;
                cout << "Enter month: \n";
                cin >> month_entered;
                cout << "Enter day: \n";
                cin >> day_entered;

                for (unsigned int it = 0; it < biglist.size(); it++) {//size_t : unsigned int USUALLY
                    thisdateornot = biglist[it]->occurs_on(year_entered, month_entered, day_entered);//	thisdateornot = (*biglist[it]).occurs_on(year_entered, month_entered, day_entered);
                    if (thisdateornot)
                        biglist[it]->printer();
                }

                

                for (unsigned int it = 0; it < biglist.size(); it++) {//size_t : unsigned int USUALLY
                    delete (biglist[it]); //
                }

                return 0;
            }