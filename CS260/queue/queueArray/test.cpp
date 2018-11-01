//comment out the first three directives if you are not using Visual Studio .Net
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "data.h"
#include "arrayqueue.h"
#include "util.h"
#include <iostream>
using namespace std;

int main()
{
	//use memory leak detection tool in Visual Studio .Net. 
	//comment it out if you are not using Visual Studio .Net
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//test constuctor, push and display
	char fileName[] = "data.dat";
	queue roster(fileName);
	cout << "\noriginal data set -- ";
	roster.display ();

	//test enqueue, peek, and dequeue
	data student("Aaa Bbb", "333333333");
	data temp;
	student.setGpa (4.0);
	if(!roster.enqueue (student))
		cout << "\nqueue is full!" << endl << endl;
	
	cout << "\nafter enqueue -- ";
	roster.display ();	

	if(!roster.peek(temp))
		cout << "\nqueue is empty!" << endl << endl ;
	else
		cout << "\nthe first student in the queue: " << temp << endl;

	if(!roster.dequeue (temp))
		cout << "\nqueue is empty!" << endl << endl;
	else
	{
		cout << "\nafter dequeue -- ";
		roster.display ();
	}
	
	
	cout << "\nThank you for testing me!" << endl << endl;
	roster.writeOut (fileName);
	
	pause();
	return 0;
}