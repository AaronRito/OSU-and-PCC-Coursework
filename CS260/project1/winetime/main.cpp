/* This program manages a database of wineries using a doubly threaded linked list. They can be displayed by name or rank.
Author: Aaron Rito
Date: 10/6/2016
CS260
*/
//#define CRTDBG_MAP_ALLOC //visual studio only
#include <stdlib.h>
#include <crtdbg.h>
//#define _CRT_SECURE_NO_WARNINGS //visual studio only
#include <iostream>
using namespace std;
#include <fstream>
#include "myutil.h"
#include "db.h"
#include "winery.h"

void displayMenu();
char readInCmd();
void executeCmd(char cmd, list& list);
void readInwinery(winery& s);

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //visual studio only
	char	command;
	list roster;
	char	fileName[] = "data.txt";

	roster.loadDB(fileName);
	displayMenu();	
	command = readInCmd();
	while (command != 'q')
	{
		cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n  " <<endl;
		executeCmd(command, roster);
		pause();
		cout << "\n \n \n \n \n \n \n \n \n \n \n \n \n " << endl;
		displayMenu();
		command = readInCmd();
	}
	roster.saveDB(fileName);
	pause();
}

void displayMenu()
{
	cout << endl << "Welcome to Aaron's Winery ranker! Here's what you can do...." << endl
		<< "\t(a). Add a location" << endl
		<< "\t(l). List locations by name" << endl
		<< "\t(r). List locations by rank" << endl
		<< "\t(s). Search locations" << endl
		<< "\t(d). Delete location" << endl
		<< "\t(q). Quit" << endl << endl;
	cout<< "What would you like to do? (a, l, r, s, d, q): " << endl << endl;
}

char readInCmd()
{
	char cmd;

	cin >> cmd;
	cin.ignore(MAX_CHAR, '\n');
	return tolower(cmd);
}

void executeCmd(char cmd, list& list)
{
	winery		wine;	
	winery		match;
	winery		matches[MAX_CAP];
	int			matchesSize = 0;
	char		name[MAX_CHAR];
	char		reply;

	switch (cmd)
	{
	default: cout << "illegal command!" << endl;
		break;

	case 'a': 
		readInwinery(wine);
		list.addToDB(wine);
		cout << "location added, be sure to quit the program properly to save your changes." << endl;
		list.listName();
		break;

	case 'l': 
		list.listName();
		break;

	case 'r':
		list.listRank();
		break;

	case 's': 
		cout << "Enter the name of the winery you want to search for (case sensitive!): ";
		getString(name, MAX_CHAR);
		
		if (list.searchDB(name))
		{
				break;
		}
		   else 
		   {
			   cout << "No match found!" << endl;
		   }
		break;
	
	case 'd': 
		list.listName();
		cout << "Enter the name of the winery you want to delete (case sensitive!): ";
		getString(name, MAX_CHAR);
		cout << "Are you sure you want to delete: " << name << "? (y/n)";
		cin >> reply;
		cin.ignore(MAX_CHAR, '\n');

		switch (reply) {
		case 'y':
			if (list.remove(name))
			{
				cout << " ' " << name << " ' " << "deleted from list" << endl;
				break;
			}
			else
			{
				cout << "No match found!" << endl;
			}
			break;

		case 'n':
			cout << "Abort delete" << endl;
			break;

		default: cout << "illegal command!" << endl;
			break;
		}
	}	
}
// get data from the user
void readInwinery(winery& s)
{
	char	name[MAX_CHAR], location[MAX_CHAR], date[MAX_CHAR], rank[MAX_CHAR], acre[MAX_CHAR];

	cout << "Please enter the winery name: ";
	getString(name, MAX_CHAR);

	cout << "Please enter the location: ";
	getString(location, MAX_CHAR);

	cout << "Please enter the founding date: ";
	getString(date, MAX_CHAR);

	cout << "Please enter the rank in stars (ex. ***** or **): ";
	getString(rank, MAX_CHAR);

	cout << "Please enter the acreage of the winery: ";
	getString(acre, MAX_CHAR);

	s.setName(name);
	s.setlocation(location);
	s.setDate(date);
	s.setRank(rank);
	s.setAcre(acre);
}


