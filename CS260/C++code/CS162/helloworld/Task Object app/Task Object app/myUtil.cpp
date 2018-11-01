#include "myutil.h"
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
		cout << "Enter a string: ";
		cin.get(str, capacity, '\n');
	}
	cin.ignore(MAX_CHAR, '\n');
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
		cout << "Illegal float! Please try again: ";
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
