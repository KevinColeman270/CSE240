
#include <string>
using namespace std;

class Patient {
private:
	string name;		// data members
	int age, DOByear, ID;


public:
	Patient();			 // constructor

	// member functions. Function definition in student.cpp
	void setName(string name_input);
	void setAge(int age_input);
	void setDOByear(int DOByear_input);
	void setID(int ID_input);
	void displayPatient();
	string getName();
	int getAge();
	int getDOByear();
	int getID();
};

