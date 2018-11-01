//comment out the first three directives if you are not using Visual Studio .Net
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "util.h"
#include "data.h"
#include "arraylist.h"
#include <iostream>
using namespace std;

int main()
{
	//use memory leak detection tool in Visual Studio .Net. 
	//comment it out if you are not using Visual Studio .Net
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//test constuctor, add and display
	char fileName[] = "data.dat";
	list roster(fileName);
	cout << "\noriginal data set -- ";
	roster.display ();

	//test insert, retrieve, and remove
	data student("Aaa Bbb", "333333333");
	data temp;
	student.setGpa (4.0);
	if(	!roster.insert(student))
		cout << "data already exists in the list" << endl << endl;
	else
	{
		cout << "\nafter insertion -- ";
		roster.display ();
	}

	if(!roster.retrieve ("333333333", temp))
		cout << "\nno such data in the list" << endl << endl ;
	else
		cout << "\nthe newly added student: " << temp << endl;

	if(!roster.remove ("333333333"))
		cout << "\nno such data in the list" << endl << endl;
	else
	{
		cout << "\nafter deletion -- ";
		roster.display ();
	}
	
	//test copy constructor
	list rosterCopy(roster);
	cout << "\ncopy of the data set --";
	rosterCopy.display ();

	cout << "\nThank you for testing me!" << endl << endl;
	roster.writeOut (fileName);

	pause();	
	return 0;
}