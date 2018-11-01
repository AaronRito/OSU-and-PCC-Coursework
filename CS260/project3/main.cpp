/*This program keeps track of stocks 
Author: Aaron Rito
Date: 11/13/16
CS261
*/
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
using namespace std;
#include "data.h"
#include "hashtable.h"
#include <cstring>
void displayMenu();
char readInCmd();
void executeCmd(char cmd, hashTable& list);
void readInaData(aData& s);

int main()
{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //visual studio only
		char	command;
		char	fileName[] = "data.dat";
		hashTable roster(fileName);		
		roster.monitor();
		displayMenu();
		command = readInCmd();
		while (command != 'q')
		{
			cout << "\n \n \n \n \n  " << endl;
			executeCmd(command, roster);
			pause();
			cout << "\n \n \n \n \n  " << endl;
			roster.monitor();
			displayMenu();
			command = readInCmd();
		}
		roster.writeOut(fileName);
		pause();
	}

	void displayMenu()
	{
		cout << endl << "Welcome to Aaron's stock ticker! Here's what you can do...." << endl
			<< "\t(a). Add a stock" << endl
			<< "\t(l). List stock by name" << endl
			<< "\t(s). Search for a stock" << endl
			<< "\t(m). Modify a stock" << endl
			<< "\t(d). Delete an entry" << endl
			<< "\t(q). Quit" << endl << endl;
		cout << "What would you like to do? (a, l, s, m, d, q): " << endl << endl;
	}

	char readInCmd()
	{
		char cmd;

		cin >> cmd;
		cin.ignore(MAX_CHAR, '\n');
		return tolower(cmd);
	}

	void executeCmd(char cmd, hashTable& list)
	{
		aData		stock;
		aData		match;
		aData		matches[MAX_CHAR];
		int			matchesSize = 0;
		char		symbol[MAX_CHAR];
		char		reply;

		switch (cmd)
		{
		default: cout << "illegal command!" << endl;
			break;

		case 'a':
			readInaData(stock);
			list.insert(stock);
			cout << "location added, be sure to quit the program properly to save your changes." << endl;
			list.display();
			break;

		case 'l':
			list.display();
			break;

		case 's':
			cout << "Enter the ticker name of the stock you want to search for (case sensitive!): ";
			getString(symbol, MAX_CHAR);

			if (list.retrieve(symbol, match ))
			{
				cout << "Entry found: " << match << endl;
				break;
			}
			else
			{
				cout << "No match found!" << endl;
			}
			break;
		case 'm':
			list.display();
			cout << "Enter the ticker name of the stock you want to modify (case sensitive!): ";
			getString(symbol, MAX_CHAR);

			if (list.retrieve(symbol, match))
			{
				cout << "Entry found: " << match << endl;
				char   ass[MAX_CHAR], date[MAX_CHAR], div[MAX_CHAR];
				cout << "Enter the new asset value: ";
				getString(ass, MAX_CHAR);
				cout << "Enter the new date: ";
				getString(date, MAX_CHAR);
				cout << "Enter the new year to date return %: ";
				getString(div, MAX_CHAR);
				list.modify(symbol, ass, date, div);
				list.retrieve(symbol, match);
				cout << "Entry modified: " << match << endl;
				break;
			}
			else
			{
				cout << "No match found!" << endl;
			}
			break;

		case 'd':
			list.display();
			cout << "Enter the ticker name of the stock you want to delete (case sensitive!): ";
			getString(symbol, MAX_CHAR);
			cout << "Are you sure you want to delete: " << symbol << "? (y/n)";
			cin >> reply;
			cin.ignore(MAX_CHAR, '\n');

			switch (reply) {
			case 'y':
				if (list.remove(symbol))
				{
					cout << " ' " << symbol << " ' " << "deleted from list" << endl;
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
	void readInaData(aData& s)
	{
		char	symbol[MAX_CHAR], name[MAX_CHAR], ass[MAX_CHAR], date[MAX_CHAR], div[MAX_CHAR];

		cout << "Please enter the ticker name: ";
		getString(symbol, MAX_CHAR);

		cout << "Please enter the stock name: ";
		getString(name, MAX_CHAR);

		cout << "Please enter the net asset value: ";
		getString(ass, MAX_CHAR);

		cout << "Please enter the value date: ";
		getString(date, MAX_CHAR);

		cout << "Please enter the year to date return %: ";
		getString(div, MAX_CHAR);

		s.setSymbol(symbol);
		s.setName(name);
		s.setAss(ass);
		s.setDate(date);
		s.setDiv(div);	
}