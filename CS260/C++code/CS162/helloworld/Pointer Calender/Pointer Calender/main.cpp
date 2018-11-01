/* This program manages assignments from different courses, you can add tasks, their associated 
classes and due dates, list and remove them
Assignment: CS162 lab 3
Author: Aaron Rito
Date: 7/20/14
*/
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <fstream>
#include "myutil.h"
#include "db.h"
#include "course.h"

void displayMenu();
char readInCmd();
void executeCmd(char cmd, TaskList& list);
void readInCourse(Course& s);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char	command;
	TaskList roster;
	char	fileName[] = "data.txt";

	roster.loadDB(fileName);
	displayMenu();	
	command = readInCmd();
	while (command != 'q'){

		executeCmd(command, roster);
		displayMenu();
		command = readInCmd();
	}
	roster.saveDB(fileName);
	pause();
}
void displayMenu()
{
	cout << endl << "Welcome to Aaron's Calender planner! Here's what you can do...." << endl
		<< "\t(a). Add a Task" << endl
		<< "\t(l). List Tasks" << endl
		<< "\t(r). Remove Task" << endl
		<< "\t(s). Search Tasks" << endl 
		<< "\t(q). Quit" << endl << endl;
}

char readInCmd()
{
	char cmd;

	cout << "What would you like to do? (enter the command letter: a, l, r, s, q): ";
	cin >> cmd;
	cin.ignore(MAX_CHAR, '\n');
	return tolower(cmd);
}

void executeCmd(char cmd, TaskList& list)
{
	Course		course;	
	Course		matches[MAX_CAP];
	int			p = 0;
	int			matchesSize = 0;
	char		name[MAX_CHAR];
	char		pos[MAX_CHAR];
	char		reply;

	switch (cmd)
	{
	default: cout << "illegal command!" << endl;
		break;
	case 'a': 
		readInCourse(course);
		list.addToDB(course);
		cout << "Task added, be sure to quit the program properly to save your data." << endl;
		break;
	case 'l': 
		list.listDB();
		break;
	case 's': 
		cout << "Enter the name of the course you want to search for (case sensitive!): ";
		getString(name, MAX_CHAR);
		
		if (list.searchDB(name)){
				
				break;
		}
		   else {
				
			   cout << "No match found!" << endl;
			}
		break;
	
	case 'r': 
		list.listDB();
		cout << "Enter the number of the task you want to delete (1-10):" << endl;
		getString(pos, MAX_CHAR);
		p = atoi (pos);
		cout << "Are you sure you want to delete entry #" << pos << " (y/n)? " << endl;
		cin >> reply;
		cin.ignore(MAX_CHAR, '\n');
		
				switch (reply){
					case 'y':
						if (list.delIt(p)){
						cout << "Delete successful. " << endl;
						break;
						}
						else {
							cout << "Delete failed." << endl;	
							break;
						}

					case 'n':
						cout << "Abort delete" << endl;
						break;
	
					default: cout << "illegal command!" << endl;
					break;
				}

	}	
}

void readInCourse(Course& s)
{
	char	name[MAX_CHAR];
	char	task[MAX_CHAR];
	char	date[MAX_CHAR];

	cout << "Please enter the course name: ";
	getString(name, MAX_CHAR);

	cout << "Please enter the task: ";
	getString(task, MAX_CHAR);

	cout << "Please enter the due date: ";
	getString(date, MAX_CHAR);

	s.setName(name);
	s.setTask(task);
	s.setDate(date);
}


