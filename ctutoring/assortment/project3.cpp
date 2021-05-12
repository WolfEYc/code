//This source file contains the definition for Date, Time and Appointment classes plus the main program
//You are to make necessary changes to these classes and derive a Session class from Appointment so that
//the program will work as shown in the provided main program.
//Also, put your name, class, assignment and date here as comments

#include <bits/stdc++.h>
#include <typeinfo>

using namespace std;

class Date
{
private:
	int day, month, year;
public:
	Date(int = 1, int = 1, int = 1900);
	void set(int = 1, int = 1, int = 1900);
	void get();
	void print() const;
	bool operator==(const Date &) const;
};

class Time
{
private:
	int hour, minute;
public:
	Time(int = 0, int = 0);
	void set(int = 0, int = 0);
	void get();
	void print() const;
	int get_hour() const;
	int get_minute() const;
	Time operator-(const Time &) const; // returns the difference of two Time objects
	bool operator==(const Time &) const; // compares two Time objects and returns True if first < second
	bool operator<(const Time &) const; // compares two Time objects and returns True if first < second
	bool operator>(const Time &) const; // compares two Time objects and returns True if first > second
};

class Appointment
{
protected:
	Date date;
	Time start_time, end_time;
	char description[40], location[40];
public:
	Appointment();
	void get();
	virtual void print() const;
	Date get_date() const;
	Time get_start_time() const;
	Time get_end_time() const;
};

class Session : public Appointment{
private:
	char client_id[11], fname[21], lname[21];
	float hourly_charge;
public:
	Session():Appointment(){
		get();
	}
	~Session(){}
	void get(){
		cout << "Enter client's id: ";
		cin >> client_id;
		cout << "Enter client's first name: ";
		cin >> fname;
		cout << "Enter client's last name: ";
		cin >> lname;
		cout << "Enter hourly charge: ";
		cin >> hourly_charge;
	}
	void print() const override{
		Appointment::print();
		cout << "\nClient ID: " << client_id << endl
		 << "Client first name: " << fname << endl
		 << "Client last name: " << lname << endl
		 << "Hourly charge: " << hourly_charge << endl;
	}
	float calc_charge(){
		return (end_time-start_time).get_hour() * hourly_charge;
	}
	char* get_id() { return client_id; }
	char* get_lname() { return lname; }
	char* get_fname() { return fname; }
};

class Student{
private:
	char* name; //max 21 characater name
	int length;
public:
	Student(){
		name = nullptr;
		length = 0;
	}
	void read(){
		
		string beans;
		getline(cin, beans);
		length = beans.length();
		name = new char[length];
		for(int i = 0; i < length; i++)
			name[i] = beans[i];
	}
	void print(){
		cout << name << endl;
	}
	~Student(){
		if(name != nullptr)
			delete[] name;
	}
};

class Exam : public Appointment{
private:
	int numStudents;
	Student* students;
public:
	Exam(int n):Appointment(){
		numStudents = n;
		students = new Student[numStudents];
	}

	~Exam(){
		delete[] students;
	}

	void read(){
		Appointment::get();

		cout << "Enter names of students taking the exam:\n";
		for(int i = 0; i < numStudents; i++)
			students[i].read();
		
	}

	void print(){
		cout << description << " on ";
		date.print();
		cout << " from ";
		start_time.print();
		cout << " ";
		end_time.print();
		cout << " at " << location << endl
		<< "Students taking the exam:\n";

		for(int i = 0; i < numStudents; i++)
			students[i].print();

	}

};

Date::Date(int d, int m, int y)
{
	set(d, m, y);
}

void Date::set(int d, int m, int y)
{
	if (d >= 1 && d <= 31)
		day = d;
	else
	{
		cout << "\ninvalid day";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (m >= 1 && m <= 12)
		month = m;
	else
	{
		cout << "\ninvalid month";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
	if (y >= 1900 && y <= 3000)
		year = y;
	else
	{
		cout << "\ninvalid year";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Date::get()
{
	char ch;

	cout << "Enter date in mm/dd/yyyy format: ";
	cin >> month >> ch >> day >> ch >> year;

	while (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 3000)
	{
		cout << "\nInvalid date entered" << endl;
		cout << "\nEnter date in mm/dd/yyyy format: ";
		cin >> day >> ch >> month >> ch >> year;
	}
}

void Date::print() const
{
	cout << month << "/" << day << "/" << year;
}

bool Date::operator==(const Date &d) const
{
	return day == d.day && month == d.month && year == d.year;
}

Time::Time(int h, int m)
{
	set(h, m);
}

void Time::set(int h, int m)
{
	if (h >= 0 && h <= 24)
		hour = h;
	else
	{
		cout << "\nInvalid hour";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}

	if (m >= 0 && m <= 60)
		minute = m;
	else
	{
		cout << "\nInvalid minute";
		cout << "\nPress any key to continue";
		system("pause");
		exit(1);
	}
}

void Time::get()
{
	char ch;

	cout << "Enter time in military [hour:minute] format: ";
	cin >> hour >> ch >> minute;

	while (hour < 0 || hour > 24 || minute < 0 || minute > 60)
	{
		cout << "\nInvalid time entered";
		cout << "\nEnter time in military [hour:minute] format: ";
		cin >> hour >> ch >> minute;
	}
}

void Time::print() const
{
	cout << hour << ":" << minute;
}

int Time::get_hour() const
{
	return hour;
}

int Time::get_minute() const
{
	return minute;
}

Time Time::operator-(const Time &t) const
{
	if (minute >= t.minute)   // check minutes before creating the temp object
		return Time(hour - t.hour, minute - t.minute);
	else
		return Time(hour - t.hour - 1, minute + 60 - t.minute);
}

bool Time::operator==(const Time &t) const
{
	return hour == t.hour && minute == t.minute;
}

bool Time::operator<(const Time &t) const
{
	if (hour < t.hour)
		return true;
	else if ((hour == t.hour) && (minute < t.minute))
		return true;
	else
		return false;
}

bool Time::operator>(const Time &t) const
{
	return !(*this == t) && !(*this < t); // if not equal and not less, it must be greater
}

Appointment::Appointment() : date(), start_time(), end_time()
{
	strcpy(description, "");
	strcpy(location, "");
}

void Appointment::get()
{
	char c;

	date.get();

	do
	{
		cout << "Start time - ";
		start_time.get();

		cin.ignore(20, '\n');

		cout << "End time - ";
		end_time.get();

		cin.ignore(20, '\n');

		if (start_time.get_hour() > end_time.get_hour())
			cout << "\nEnd time cannot be earlier than start time" << endl;

	} while (start_time.get_hour() > end_time.get_hour());

	cout << "Enter description: ";
	int i = 0;
	cin.get(c);
	while (c != '\n')
	{
		description[i++] = c;
		cin.get(c);
	}
	description[i] = '\0';

	cout << "Enter location: ";
	i = 0;
	cin.get(c);
	while (c != '\n')
	{
		location[i++] = c;
		cin.get(c);
	}
	location[i] = '\0';
}

void Appointment::print() const
{
	cout << "\nAppointment Date: ";
	date.print();
	cout << "\nStart time: ";
	start_time.print();
	cout << "\nEnd time: ";
	end_time.print();
	cout << "\nDescription: " << description;
	cout << "\nLocation: " << location;
}

Date Appointment::get_date() const
{
	return date;
}

Time Appointment::get_start_time() const
{
	return start_time;
}

Time Appointment::get_end_time() const
{
	return end_time;
}

bool conflict(Appointment *, Appointment *[], int, int&); // params: Appt *, Appt *[], array size and index of Appt with conflict

int select_appt(Appointment *[], int);

enum classType { appt, session };

int main()
{
	Appointment *ap[100], *temp;
	Session *sp;
	classType type[100];
	int choice, selection, count = 0, index, i;
	char id[11], fname[21], lname[21];
	Date date;
	float charges = 0.0;
	bool found;
	bool flag = false;

	do
	{
		cout << "\nAppointment Management program by Sue :)"
			<< "\nChoose one of the following: "
			<< "\n------------------------------"
			<< "\n1. Create a new appointment"
			<< "\n2. Create a new session"
			<< "\n3. View all appointments and sessions"
			<< "\n4. Edit appointment/session"
			<< "\n5. Check a date for appointments/sessions"
			<< "\n6. View sessions for a client"
			<< "\n7. View charges for a client"
			<< "\n8. View total charges for all clients"
			<< "\n9. Delete an appointment or session"
			<< "\n10. Quit"
			<< "\n----------------------------->";

		cin >> choice;

		system("cls");

		switch (choice)
		{
		case 1:		temp = new Appointment;				 // create temp Appointment pointer
			temp->get();						 // read values into temp 
			if (conflict(temp, ap, count, index)) // if there is a conflict with an existing Appointment
			{									 // index will identify it
				cout << "\nThis will conflict with: ";
				ap[index]->print();	 // print conflicting Appointment
				cout << "\n\nAppointment not entered.";
			}
			else
			{
				ap[count] = temp;
				type[count] = appt; // parallel array is used to identify the type of object ptr stored in ap[]
				count++;
			}
			break;

		case 2:		temp = new Session;					 // create temp Session pointer
			temp->get();						 // read values into temp 
			if (conflict(temp, ap, count, index)) // if there is a conflict with an existing Session
			{									 // index will identify it
				cout << "\nThis will conflict with: ";
				ap[index]->print();	 // print conflicting Session
				cout << "\n\nSession not entered.";
			}
			else
			{
				ap[count] = temp; // store Sessions in both arrays because when searching for Session info
				type[count] = session; //parallel array is used to identify the type of object ptr stored in ap[]
				count++;
			}
			break;

		case 3:		for (i = 0; i < count; i++)
		{
			ap[i]->print();
			cout << endl;
		}
					break;

		case 4:		if ((choice = select_appt(ap, count)) == -1) // Specified date could not be found
		{
			cout << "\nThere are no appointments or sessions on this date.";
			break;
		}
					else
					{
						temp = ap[choice];					// save the pointer to the Appt. or Session to be deleted.

						if (choice < count - 1)				// if the one being deleted is not the last in the array
							for (i = choice; i < count; i++) // shift all Appt pointers into lower-index place in array
							{
							ap[i - 1] = ap[i];
							type[i - 1] = type[i];
							}

						count--;
					}

					do
					{
						cout << "\nEnter 1 to select an appointment and 2 to choose a session: ";
						cin >> selection;

						if (selection == 1)
						{
							ap[count] = new Appointment;
							type[count] = appt; //parallel array is used to identify the type of object ptr stored in ap[]
						}
						else if (selection == 2)					 // if the new one is a Session
						{
							ap[count] = new Session;
							type[count] = session; //parallel array is used to identify the type of object ptr stored in ap[]
						}

					} while (selection < 1 || selection > 2);

					ap[count]->get();	// enter values into newly created object but don't increment count until verified

					if (conflict(ap[count], ap, count, index)) // if conflicts with an existing Appoint or Session
					{									      // index will identify conflicting Appt or Session
						cout << "\nThis will conflict with:\n";
						ap[index]->print();			      // print conflicting appt or session
						cout << "\n\nAppointment or session not modified.";

						delete ap[count];   // delete the one added
						ap[count++] = temp; // copy temp back into ap
					}
					else
						count++; // no conflict so count the last one just added - count was not incremented until now.

					break;

		case 5:		cout << "\nEnter date to check: ";
			date.get();

			found = false;
			for (i = 0; i < count; i++)
				if (date == ap[i]->get_date())
				{
				found = true;
				ap[i]->print();
				cout << endl;
				}

			if (!found)
			{
				cout << "\nYou have no appointments or sessions on ";
				date.print();
			}

			break;

		case 6:		do
		{
			cout << "\nEnter 1 to search by I.D. or 2 to search by name: ";
			cin >> choice;
			found = false;

			if (choice == 1)
			{
				cout << "\nEnter client I.D.: ";
				cin >> id;

				for (i = 0; i < count; i++)
					if (type[i] == session)
					{
					sp = (Session*)(ap[i]);
					if (!strcmp(id, sp->get_id())) // we have to look at Sessions only
					{
						sp->print();
						found = true;		 // because Appts don't have get_id() 
					}
					}

				if (!found)
					cout << "\nClient not found. ";
			}
			else if (choice == 2)
			{
				cout << "\nEnter client last name: ";
				cin >> lname;

				cout << "\nEnter client first name: ";
				cin >> fname;

				for (i = 0; i < count; i++)
					if (type[i] == session)
					{
					sp = (Session*)(ap[i]);
					if (!strcmp(lname, sp->get_lname()) && !strcmp(fname, sp->get_fname()))
					{
						sp->print();
						found = true;
					}
					}

				if (!found)
					cout << "\nClient not found. ";
			}
			else
				cout << "\nPlease, enter either 1 or 2: ";

		} while (choice < 1 || choice > 2);

			break;

		case 7:		charges = 0.0;
			found = false;

			do
			{
				cout << "\nEnter 1 to search by I.D. or 2 to search by name: ";
				cin >> choice;
				if (choice == 1)
				{
					cout << "\nEnter client I.D.: ";
					cin >> id;
					for (i = 0; i < count; i++)
						if (type[i] == session)
						{
						sp = (Session*)(ap[i]);
						if (!strcmp(id, sp->get_id()))
						{
							found = true;
							charges += sp->calc_charge();
							cout << "\nCharges for " << id << " is: " << charges;
						}
						}

					if (!found)
						cout << "\nClient not found. ";
				}
				else if (choice == 2)
				{
					cout << "\nEnter client last name: ";
					cin >> lname;

					cout << "\nEnter client first name: ";
					cin >> fname;

					for (i = 0; i < count; i++)
					{
						if (type[i] == session)
						{
							sp = (Session*)(ap[i]);
							if (!strcmp(lname, sp->get_lname()) && !strcmp(fname, sp->get_fname()))
							{
								found = true;
								charges += sp->calc_charge();
								cout << "\nCharges for " << fname << " " << lname << " is: " << charges;
							}
						}
					}
					if (!found)
						cout << "\nClient not found. ";
				}
				else
					cout << "\nPlease, enter either 1 or 2: ";

			} while (choice < 1 || choice > 2);

			break;

		case 8:		charges = 0.0;

			for (i = 0; i < count; i++)
				if (type[i] == session)
				{
				sp = (Session*)(ap[i]);
				charges += sp->calc_charge();
				}

			cout << "\nTotal charges for all clients is " << charges;

			charges = 0.0;
			break;

		case 9:		if ((index = select_appt(ap, count)) == -1)  // Specified date could not be found
					{
						cout << "\nThere are no appointments or sessions on this date.";
						break;
					}

					else if (index < count - 1)		// if the one being deleted is not the last in the array
						for (int i = index; i < count - 1; i++) //shift all Appointment objects into lower-index place in array
							(*(ap[i])) = (*(ap[i + 1]));
					else
						delete ap[count - 1]; // delete last Array element

					count--;

					break;

		case 10: 	flag = true; break;

		default:	cout << "\nInvalid entry - please, enter a number between 1 and 10.";
		}
	} while (flag == false);


	//Exam testing 
	int n;
	string beans;
	cout << "Enter number of students to take the exam: ";
	cin >> n;

	Exam exam(n);
	
	exam.read();

	cout << endl;

	exam.print();

	cout << "press ENTER to continue" << endl;

	cin.get();

	cout << endl;
}

bool conflict(Appointment *p, Appointment *ap[], int size, int& i) // i is the index of the array element with conflict
{																   // the function modifies i so the caller can get it
	Date date = p->get_date();
	Time start = p->get_start_time();
	Time end = p->get_end_time();

	for (i = 0; i < size; i++)
		if (date == ap[i]->get_date())
			if ((start == ap[i]->get_start_time()) ||
				(start < ap[i]->get_start_time()) && (end > ap[i]->get_start_time()) ||
				(start > ap[i]->get_start_time()) && (start < ap[i]->get_end_time()))
				return true;
	return false;
}

int select_appt(Appointment *ap[], int size) // returns the index of the array element if found and -1 if not found
{
	Date date;
	int choice, int_array[10];

	cout << "\nEnter appointment or session date: ";
	date.get();

	for (int i = 0, j = 0; i < size; i++){ // search for given date
		if (date == ap[i]->get_date())
		{
		int_array[j++] = i; // Store i in int_array when date matches
		cout << "\n----------- " << j << " ----------";
		ap[i]->print();
		cout << endl;
		}

		if (j == 0) // if Appt or Session not found
			return -1;

		else // Appt or Session found
		{
			do
			{
				cout << "\nSelect the appointment by entering its number: [1 - " << j << "]: ";
				cin >> choice;
			} while (choice < 1 || choice > j);

			return int_array[choice - 1];
		}
	}
	return -1;
}
