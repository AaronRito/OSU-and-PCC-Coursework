/* This program manages assignments from different courses, you can add tasks, their associated 
classes and due dates, list and remove them
Assignment: CS162 lab 2
Author: Aaron Rito
Date: 7/15/14
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <fstream>
#include "myutil.h"
#include "db.h"

void displayMenu();
char readInCmd();
void executeCmd(char cmd, Course list[], int& size);
void readInCourse(Course& s);

int main()
{
	char	command;
	Course	roster[MAX_CAP];
	int		numberOfCourses = 0;
	char	fileName[] = "data.txt";

	loadDB(fileName, roster, numberOfCourses);
	displayMenu();	
	command = readInCmd();
	while (command != 'q')
	{
		executeCmd(command, roster, numberOfCourses);
		displayMenu();
		command = readInCmd();
	}
	saveDB(fileName, roster, numberOfCourses);
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

void executeCmd(char cmd, Course list[], int& size)
{
	Course		course;	
	int i;
	int j;
	int k;
	char name[MAX_CHAR];
	int matches[MAX_CAP];
	int matchesSize;
	switch (cmd)
	{
	case 'a': 
		readInCourse(course);
		addToDB(course, list, size);
		break;
	case 'l': 
		listDB(list, size);
		break;
	case 's': 
		
		cout << "Please enter the name of the Course you want to search: ";
		getString(name, MAX_CHAR);
		
		if (searchDB(name, list, size, matches, matchesSize))
		{
			for (i = 0; i < matchesSize; i++)
				cout << "Match found: " << list[matches[i]].name << '\t' << list[matches[i]].task << '\t' << list[matches[i]].date << endl;
				
		}
			else
		{
			cout << "No match found!" << endl;
		}
		break;
	
	case 'r': 
		
		char reply;
		char task[MAX_CHAR];
		cout << "Please enter the name of the Course that has the task you want to delete: ";
		getString(name, MAX_CHAR);
		
		if (searchDB(name, list, size, matches, matchesSize))
		{
			// if only one match is returned the program asks to delete it.
			if (matchesSize < 2) {
				for (i = 0; i < matchesSize; i++)
				{	cout << matchesSize << " Match found: " << list[matches[i]].name << '\t' << list[matches[i]].task << '\t' << list[matches[i]].date << endl;
					cout << "Are you sure you want to delete it? (y/n)" << endl;
					cin >> reply;
					cin.ignore(MAX_CHAR, '\n');
					switch(reply){
					case 'y': 
						cout << "Task deleted." << endl;
								for (j=matches[i];j < size; j++)
									list[j] = list[j+1];
								size--;
				}

					case 'n':
						break;
				}	
			}
			else if(matchesSize > 1){
					// If multiple assingments from the same class are returned the program will ask which task to delete.
					for (i = 0; i < matchesSize; i++) 
					cout << "Multiple matches found: " << list[matches[i]].name << '\t' << list[matches[i]].task << '\t' << list[matches[i]].date << endl;
					cout << "Please enter the name of the task you want to delete: ";
					getString(task, MAX_CHAR);
					if (searchTask(task, list, size, name, matches, matchesSize))
						
						for (k = 0; k < matchesSize; k++)
						{	cout << "Match found: " << list[matches[k]].name << '\t' << list[matches[k]].task << '\t' << list[matches[k]].date << endl;
							cout << "Do you want to delete it? (y/n)" << endl;
							cin >> reply;
							cin.ignore(MAX_CHAR, '\n');
							switch(reply){
							case 'y': 
								cout << "Task deleted" << endl;
								for (j=matches[k];j < size; j++)
									list[j] = list[j+1];
								size--;

							case 'n':
								break;
							}
						}
			else
			{
			cout << "No match found!" << endl;
			}
				break;

	default: cout << "illegal command!" << endl;
		break;
			}
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

	strcpy(s.name, name);
	strcpy(s.task, task);
	strcpy(s.date, date);
}


