/* This program will tally the cost of your groceries.
Author: Aaron Rito
Date: 6/27/14
Class: CS162 W night section*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctype.h>
#include <cstring>
using namespace std;

const int MAX_CHAR = 100;

void abortProgram();
void pause();
float getFloat();
float getPrice();
void getString(char str[], int capacity);

int main()
{
	float		price;
	float		total = 0;
	char		name[MAX_CHAR];
	char		reply;
	reply		= ' ';

	cout << "Welcome to Aaron's Grocery Run." << endl; 

	while (reply != 'q' && reply != 'Q') {
		
		cout << endl << "What would you like to do? (A)dd Item, (C)heckout, (Q)uit:" << endl; 
		cin  >> reply ;
		cin.ignore();
		cout.setf(ios::fixed, ios::floatfield);
		cout.setf(ios::showpoint);
		cout.precision(2);

		if (reply == 'a' || reply == 'A') {
			cout << "Please enter the item name: " << endl;
			getString(name, MAX_CHAR);
			cout << "Please enter the item price (without the $ sign, ex. 4.95): ";
			price = getPrice();
			cout << "You entered " << name << ", it's price is: $" << price << endl;
			if (price == !0)
				total = price;
				total += price;
			cout << "Your current total is: $" << total << endl;
			}
	
		else if  (reply == 'q' || reply == 'Q') { 
			abortProgram();
		}
		else if  (reply == 'c' || reply == 'C') { 
			cout << "Thank you for using Aaron's Grocery run, your total price is: $" << total << endl;
			abortProgram();
		}
	}
	pause();
	return 0;
}
/*
This functions returns a string from parameter.
in: capacity
out: str
*/
void getString(char str[], int capacity)
{
	cin.get(str, capacity, '\n');
	while (!cin)
	{
		cin.clear();
		cin.ignore(MAX_CHAR, '\n');
		cout << "Please enter a valid item name ex. 'apple':  ";
		cin.get(str, capacity, '\n');
	}
	cin.ignore(MAX_CHAR, '\n');
}
/*
This function returns a floating point that is not 0
*/
float getPrice()
{
	float	price;
	price = getFloat();
	while (price < 0 )
	{
		cout << "Please enter a valid price ex. 4.95 : ";
		price = getFloat();
	}
	return price;
}
/*
This function returns an legal floating point number.
return: float 
*/
float getFloat()
{
	float	value;
	cin >> value;
	while (!cin)
	{
		cin.clear(); //clear the flag
		cin.ignore(MAX_CHAR, '\n'); //empty the buffer
		cout << "Please enter a valid price ex. 4.95 : ";
		cin >> value;
	}
	cin.ignore(MAX_CHAR, '\n');
	return value;
}
void pause()
{
	char ch;
	cout << "press any key to continue ..." << endl;
	cin >> ch;
}

	//abort the program 

void abortProgram()

{
	char ch;
	cout << "Press any character, then enter to quit ..." << endl;
	cin >> ch;
    exit(1);
}
	

