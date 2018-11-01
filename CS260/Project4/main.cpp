/*This program keeps track of vendors
Author: Aaron Rito
Date: 12/2/16
CS261
*/
#include <stdlib.h>
#include <iostream>
using namespace std;
#include "data.h"
#include "BST.h"
#include <cstring>
void displayMenu();
char readInCmd();
void executeCmd(char cmd, BST& list);
void readInaData(aData& s);

int main()
{	
		char	command;
		char	fileName[] = "data.dat";
		BST roster(fileName);		
		displayMenu();
		command = readInCmd();
		while (command != 'q')
		{
			cout << "\n \n \n \n \n  " << endl;
			executeCmd(command, roster);
			pause();
			cout << "\n \n \n \n \n  " << endl;
			displayMenu();
			command = readInCmd();
		}
		roster.writeOut(fileName);
		pause();
	}

	void displayMenu()
	{
		cout << endl << "Welcome to Aaron's vendor tracker! This program prints best in full screen. Here's what you can do...." << endl
			<< "\t(a). Add a vendor" << endl
			<< "\t(l). List vendors by name" << endl
			<< "\t(m). List vendors by product" << endl
			<< "\t(s). Search for a vendor by name" << endl
			<< "\t(p). Search for a vendor by product" << endl
			<< "\t(d). Delete an entry" << endl
			<< "\t(q). Quit" << endl << endl;
		cout << "What would you like to do? (a, l, m, s, p, d, q): " << endl << endl;
	}

	char readInCmd()
	{
		char cmd;

		cin >> cmd;
		cin.ignore(MAX_CHAR, '\n');
		return tolower(cmd);
	}

	void executeCmd(char cmd, BST& list)
	{
		aData		vendor;
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
			readInaData(vendor);
			list.insert(vendor);
			cout << "location added, be sure to quit the program properly to save your changes." << endl;
			list.displayName();
			break;

		case 'l':
			list.displayName();
			break;
		
		case 'm':
			list.displayProd();
			break;

		case 's':
			list.displayName();
			cout << "Enter the name of the vendor you want to search for (case sensitive!): ";
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
		case 'p':
			list.displayProd();
			cout << "Enter the name of the product you want to search for(case sensitive!): ";
			getString(symbol, MAX_CHAR);

			if (list.retrieveProd(symbol, match))
			{
				cout << "Entry found: " << match << endl;
				break;
			}
			else
			{
				cout << "No match found!" << endl;
			}
			break;

		case 'd':
			list.displayName();
			cout << "Enter the name of the vendor you want to delete (case sensitive!): ";
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
		char name[MAX_CHAR], phone[MAX_CHAR], prod[MAX_CHAR], evt[MAX_CHAR];

		cout << "Please enter the vendor name: ";
		getString(name, MAX_CHAR);

		cout << "Please enter the phone #: ";
		getString(phone, MAX_CHAR);

		cout << "Please enter the product: ";
		getString(prod, MAX_CHAR);

		cout << "Please enter the events: ";
		getString(evt, MAX_CHAR);
	
		s.setName(name);
		s.setPhone(phone);
		s.setProd(prod);
		s.setEvt(evt);	
}