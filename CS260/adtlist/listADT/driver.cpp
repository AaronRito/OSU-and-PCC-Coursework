#include <iostream>
using namespace std;
#include "list.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int fact(int n)
{
	if (n == 0 || n == 1)
		return 1;
	return n * fact(n - 1);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	List	aList;
	Data	s1("G10", 3.0);
	Data*	s2 = new Data("G30", 3.9);
	Data*	s3 = new Data("G20", 4.0);
	List	match;
	Data	s;
	
	aList.addRecursive(s1);
	aList.addRecursive(*s2);
	aList.addRecursive(*s3);

	cout << aList << endl;
	cout << "Size of the current list: " << aList.getSize() << endl;
	/*
	if (aList.search("G20", match))
	{
		cout << "find students with G20!" << endl;
		cout << match << endl;
	}

	aList.remove("G20", s);
	cout << s << " was removed!" << endl;
	cout << aList << endl;

	cout << "Current size: " << aList.size();
	aList.get(1, s);
	cout << "The 2nd element: " << s << endl;
	*/
	delete s2;
	delete s3;

	system("pause");
	return 0;
}