// CSE240 HW 5
// Kevin Coleman / Completion Time: 5 hrs
// Visual Studios

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of patient records.
// Each record(struct) has this information: student's name, major, school year of student, ID number.
// The struct 'studentRecord' holds information of one student. School year is enum type.
// A linked list called 'list' is made to hold the list of students.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.
// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_NAME_LENGTH 25

typedef enum { freshman = 0, sophomore, junior, senior } schoolYearType; // enum type 

struct studentRecord {
	char studentName[MAX_NAME_LENGTH];
	char major[MAX_NAME_LENGTH];
	schoolYearType schoolYear;
	unsigned int IDNumber;
	struct studentRecord* next;	// pointer to next node
} *list = NULL;					// Declare linked list 'list'

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
int addSort(char* studentName_input, char* major_input, char* schoolYear_input, unsigned int IDNumber_input); // 20 points
void displayList();						// 10 points
int countNodes();						// 5 points
int deleteNode(char* studentName_input);	// 10 points
void swapNodes(struct studentRecord* node1, struct studentRecord* node2);	// 5 points



int main()
{
	char selection = 'i';		// initialized to a dummy value
	printf("\nCSE240 HW6\n");
	do
	{
		printf("\nCurrently %d student(s) on the list.", countNodes());	// NOTE: countNodes() called here
		printf("\nEnter your selection:\n");
		printf("\t a: add a new student\n");
		printf("\t d: display student list\n");
		printf("\t r: remove a student from the list\n");
		printf("\t q: quit\n");
		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the code in the function, case by case
void executeAction(char c)
{
	char studentName_input[MAX_NAME_LENGTH], major_input[MAX_NAME_LENGTH];
	unsigned int IDNumber_input, result = 0;
	char schoolYear_input[20];
	switch (c)
	{
	case 'a':	// add student
		// input student details from user
		printf("\nEnter student name: ");
		fgets(studentName_input, sizeof(studentName_input), stdin);
		studentName_input[strlen(studentName_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Enter major: ");
		fgets(major_input, sizeof(major_input), stdin);
		major_input[strlen(major_input) - 1] = '\0';	// discard the trailing '\n' char

		printf("Enter whether student is 'freshman' or 'sophomore' or 'junior' or 'senior': ");
		fgets(schoolYear_input, sizeof(schoolYear_input), stdin);
		schoolYear_input[strlen(schoolYear_input) - 1] = '\0';	// discard the trailing '\n' char
		printf("Please enter ID number: ");
		scanf("%d", &IDNumber_input);
		flushStdIn();

		// add the student to the list
		result = addSort(studentName_input, major_input, schoolYear_input, IDNumber_input);
		if (result == 0)
			printf("\nStudent is already on the list! \n\n");
		else if (result == 1)
			printf("\nStudent successfully added to the list! \n\n");

		break;

	case 'd':		// display the list
		displayList();
		break;

	case 'r':		// remove a student
		printf("\nPlease enter student name: ");
		fgets(studentName_input, sizeof(studentName_input), stdin);
		studentName_input[strlen(studentName_input) - 1] = '\0';	// discard the trailing '\n' char

		// delete the node
		result = deleteNode(studentName_input);
		if (result == 0)
			printf("\nStudent does not exist! \n\n");
		else if (result == 1)
			printf("\nStudent successfully removed from the list. \n\n");
		else
			printf("\nList is empty! \n\n");
		break;

	case 'q':		// quit
		break;
	default: printf("%c is invalid input!\n", c);
	}
}

// Q1 : addSort 
// This function is used to insert a new student into the list. You can insert the new student to the end of the linked list.
// Do not allow the student to be added to the list if that student already exists in the list. You can do that by checking the names of the students already in the list.
// If the student already exists then return 0 without adding student to the list. If the student does not exist in the list then go on to add the student at the end of the list and return 1.
// NOTE: You must convert the string 'schoolYear_input' to an enum type and store it in the list because the struct has enum type for school year.
// Sorting should happen within the list. That is, you should not create a new linked list of students having sorted students.
// Hint: One of the string library function can be useful to implement this function because the sorting needs to happen by student name which is a string.
//       Use swapNodes() to swap the nodes in the sorting logic

int addSort(char* studentName_input, char* major_input, char* schoolYear_input, unsigned int IDNumber_input) // 20 points
{
	struct studentRecord* tempList = list;	// work on a copy of 'list'
	
	//search for duplicate student
	while (tempList != NULL) {
			
		if (strcmp(studentName_input, tempList->studentName) == 0) {
			//Student already exists!
			return 0;
		}
		else {
			tempList = tempList->next;
		}
	}

	//convert school year;
	schoolYearType input; //for conversion

	//convert from string to enum.
	if (strcmp((schoolYear_input), "freshman") == 0) {
		input = freshman;
	}
	else if (strcmp(schoolYear_input, "sophomore") == 0) {
		input = sophomore;
	}
	else if (strcmp(schoolYear_input, "junior") == 0) {
		input = junior;
	}
	else if (strcmp(schoolYear_input, "senior") == 0) {
		input = senior;
	}
	//ADD STUDENT
	struct studentRecord* newStudent = (struct studentRecord*)malloc(sizeof(struct studentRecord));
	strcpy(newStudent->studentName, studentName_input);
	strcpy(newStudent->major, major_input);
	newStudent->schoolYear = input;
	newStudent->IDNumber = IDNumber_input;
	//ADD STUDENT to Front
	newStudent->next = list;
	list = newStudent;

	//reset head for future use
	tempList = list;

	//Count how big the list is to tranverse
	int count = countNodes();
	//SORT LIST
	for (int i = 0; i < count - 1; i++){
		tempList = list;
		for (int j = 0; j < count - i - 1; j++){
			if (strcmpi(tempList->studentName, tempList->next->studentName) > 0){
				swapNodes(tempList, tempList->next);
			}
			tempList = tempList->next;
		}
	}
	//successfully added to list
	return 1;	
}

// Q2 : displayList (10 points)
// This function displays the linked list of students, with all details (struct elements). 
// Parse through the linked list and print the student details one after the other. See expected output screenshots in homework question file.
// NOTE: School year is stored in the struct as enum type. You need to display a string for school year.
void displayList()
{
	struct studentRecord* tempList = list;// work on a copy of 'list'
	char* year ='\0';
		//cycle through list
		while(tempList != NULL) {
			//convert from enum to string
			switch (tempList->schoolYear) {
			case(0):
				year = "freshman";
				break;
			case(1):
				year = "sophomore";
				break;
			case(2):
				year = "junior";
				break;
			case(3):
				year = "senior";
				break;
			}
			//print student info
			printf("\n");
			printf("Student name: %s\n", tempList->studentName);
			printf("Student major: %s\n", tempList->major);
			printf("StudentYear: %s\n", year);
			printf("ID number: %d\n", tempList->IDNumber);
			//iteration
			tempList = tempList->next;
		}
	

}

// Q3: countNodes (5 points)
// This function counts the number of students on the linked list and returns the number.
// You may use this function in other functions like deleteNode(), sortList(), addNode(), if needed. 
// It can helpful to call this function in other functions, but not necessary.
// This function is called in main() to display number of students along with the user menu.
int countNodes()
{
	//helpers
	struct studentRecord* tempList = list;
	int count = 0;
	//count each node until end of list
	while (tempList != NULL) {
		tempList = tempList->next;
		count++;
	}
	//return count for sorting
	return count;	
}

// Q4 : deleteNode (10 points)
// This function deletes the node specified by the student name.
// Parse through the linked list and remove the node containing this student name.
// NOTE: After you remove the node, make sure that your linked list is not broken.
// (Hint: Visualize the list as: list......-> node1 -> node_to_remove -> node2 -> ...end. 
//        After removing "node_to_remove", the list is broken into "list ....node1" and "node2.... end". Stitch these lists.)

int deleteNode(char* studentName_input)
{
	//if list is empty
	if (list == NULL) {
		return 2;
	}

	//helpers
	struct studentRecord* tempList = list->next;				
	struct studentRecord* previous = list;
	struct studentRecord* deleteStudent;

	//if first student needs to be removed.
	if (strcmp(list->studentName, studentName_input) == 0) {
		deleteStudent = list;
		list = list->next;
		free(deleteStudent);
		//student removed
		return 1;
	}

	//cycle through and find match, remove student, stitch back together
	while (tempList != NULL) {
		if (strcmp(tempList->studentName, studentName_input) == 0) {
			deleteStudent = tempList;
			previous->next = tempList->next;
			free(deleteStudent);
			//student removed
			return 1;
		}
		tempList = tempList->next;
		previous = previous->next;
	}
	//student is not on list
	return 0;			
}


// Q5 : swapNodes (5 points)
// This function swaps the elements of parameters 'node1' and 'node2' (Here node1 does NOT mean 1st node of the list. 'node1' is just the name of the node)
// This function should not alter the 'next' element of the nodes. Only then will the nodes be swapped.
// Hint: The swap logic is similar to swapping two simple integer/string variables.
// NOTE: This function can be used in the sorting logic in addSort()

void swapNodes(struct studentRecord* node1, struct studentRecord* node2)
{
	struct studentRecord* tempStudent = (struct studentRecord*)malloc(sizeof(struct studentRecord));

	//copy to temp
	strcpy(tempStudent->studentName, node1->studentName);
	strcpy(tempStudent->major, node1->major);
	tempStudent->schoolYear = node1->schoolYear;
	tempStudent->IDNumber = node1->IDNumber;

	//copy 2 to 1
	strcpy(node1->studentName, node2->studentName);
	strcpy(node1->major, node2->major);
	node1->schoolYear = node2->schoolYear;
	node1->IDNumber = node2->IDNumber;

	//copy temp to 2
	strcpy(node2->studentName, tempStudent->studentName);
	strcpy(node2->major, tempStudent->major);
	node2->schoolYear = tempStudent->schoolYear;
	node2->IDNumber = tempStudent->IDNumber;

	//swap complete
}


