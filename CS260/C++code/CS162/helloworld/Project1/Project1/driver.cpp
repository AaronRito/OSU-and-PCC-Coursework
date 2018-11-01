#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <fstream>
#include "myutil.h"
#include "db.h"

void displayMenu();
char readInCmd();
void executeCmd(char cmd, StudentList& list);
void readInStudent(Student& s);
float getGpa();

int main()
{
	char		command;
	StudentList	roster;
	char		fileName[] = "data.txt";

	roster.loadDB(fileName);
	displayMenu();	
	command = readInCmd();
	while (command != 'q')
	{
		executeCmd(command, roster);
		displayMenu();
		command = readInCmd();
	}
	roster.saveDB(fileName);
	pause();
}
void displayMenu()
{
	cout << endl << "Welcome to Roster 1.0!" << endl
		<< "\ta. add a student" << endl
		<< "\tl. list students" << endl
		<< "\tr. remove student" << endl
		<< "\ts. search student" << endl 
		<< "\tq. quit" << endl << endl;
}

char readInCmd()
{
	char cmd;

	cout << "Please enter the command (a, l, r, s, q): ";
	cin >> cmd;
	cin.ignore(MAX_CHAR, '\n');
	return tolower(cmd);
}

void executeCmd(char cmd, StudentList& list)
{
	Student		student;	

	switch (cmd)
	{
	case 'a': 
		readInStudent(student);
		list.addToDB(student);
		break;
	case 'l': 
		list.listDB();
		break;
	case 's': 
		char name[MAX_CHAR];
		cout << "Please enter the name of the student you want to search: ";
		getString(name, MAX_CHAR);
		if (list.searchDB(name, student))
		{
			student.getName(name);
			cout << "Match found: " << name << '\t' << student.getGpa() << endl;
		}
		else
		{
			cout << "No match found!" << endl;
		}
		break;
	case 'r': cout << "remove is invoked" << endl;
		break;
	default: cout << "illegal command!" << endl;
		break;
	}
}

void readInStudent(Student& s)
{
	float	gpa;
	char	name[MAX_CHAR];

	cout << "Please enter the gpa: ";
	gpa = getGpa();

	cout << "Please enter the name: ";
	getString(name, MAX_CHAR);

	s.setGpa(gpa);
	s.setName(name);
}


/*
This function returns a floating point between 0 and 4 inclusive.
return: 0 <= gpa <= 4.0
*/
float getGpa()
{
	float	gpa;
	gpa = getFloat();
	while (gpa < 0 || gpa > 4.0)
	{
		cout << "Gpa has to be between 0 and 4.0. Please try again: ";
		gpa = getFloat();
	}
	return gpa;
}
