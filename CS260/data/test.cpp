#include <iostream>
using namespace std;
#include "data.h"
#include "util.h"

//comment out the first three directives if you are not using Visual Studio .Net
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void pause();
const int MAX_CHAR = 101;

int main()
{
	//use memory leak detection tool in Visual Studio .Net. 
	//comment it out if you are not using Visual Studio .Net
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	
	

	data student1;
	data student2("Sally White", "G30");
	data student3(student2);

	//test the overloaded operator= and <<
	student1 = student2;		//create a deep copy since we overload '=' with deep copy logic
	student2.setGpa (4.0f);

	
	cout << "Student 1: " << student1 << endl
		<< "Student 2: " << student2 << endl 
		<< "Student 3: " << student3 << endl << endl;
	

	//you should test every function defined in data class here
	char	id[MAX_CHAR];
	student1.setPccId ("G10");
	student1.getPccId (id);
	cout << "Student 1 id: " << id << endl;

	pause();
	return 0;
}











/*
	//test the constructors
	
	data student3(student2);	//our copy constructor makes student3 a deep copy of student2

	
*/