 
#include "patient.h"
#include <iostream>
#include <string>

using namespace std;

// Q1 Patient (2 points)
// Patient() constructor assigns the following default values to class data members
// name: abc
// age: 19
// DOByear: 2000
// ID: 0
Patient::Patient()
{
	name = "abc";
	age = 19;
	DOByear = 2000;
	ID = 0;

}

// Q2 (18 points)
// 2 points for each function

// Define all the class member functions.
// While defining member functions, note that these functions will be called using 
// a 'Patient' object which will represent one patient.
// Eg-  Patient p[10]; creates 10 Patient objects
//		p[2].setAge(19); will set 3rd patient's age to 19

// setName assigns 'name_input' to class data member 'name'
void Patient::setName(string name_input)
{
	name = name_input;

}

// setAge assigns age_input to class data member 'age'
void Patient::setAge(int age_input)
{
	age = age_input;
}

// setDOByear assigns 'DOByear_input' to class data member 'DOByear'
void Patient::setDOByear(int DOByear_input)
{
	DOByear = DOByear_input;
}

// setID assigns 'ID_input' to class data member 'ID'
void Patient::setID(int ID_input)
{
	ID = ID_input;
}

// displayPatients displays the name, age, year of birth and ID of the paatient
// See expected output in question file.
void Patient::displayPatient()
{
	
	cout << "Name: " << name << endl;
	printf("Age: %d\n", age);
	printf("Year of birth: %d\n", DOByear);
	printf("ID: %d\n", ID);
	cout << endl;
	
}

// getName returns the class data member 'name'.
string Patient::getName()
{
	return name;
}

// getAge returns the class data member 'age'.
int Patient::getAge()
{
	return age;
}

// getDOByear returns the class data member 'DOByear'.
int Patient::getDOByear()
{
	return DOByear;
}

// getID returns the class data member 'ID'.
int Patient::getID()
{	
	return ID;
}
