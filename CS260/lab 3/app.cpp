#include <iostream>
#include "linkedlist.h"

using namespace std;

void pause();

void find(LinkedList& list, char ch)
{
	if (list.find(ch))
		cout << "found ";
	else
		cout << "did not find ";
	cout << ch << endl;
}

int main()
{
	LinkedList	list;

	list.add('x');
	list.add('y');
	list.add('z');
	cout << list;
	find(list, 'y');

	list.del('y');
	cout << list;
	find(list, 'y');

	list.del('x');
	cout << list;
	find(list, 'x');

	list.del('z');
	cout << list;
	find(list, 'z');
	pause();
	return 0;
}
void pause()
{
	char ch;
	cout << "press any key to continue ..." << endl;
	cin >> ch;
}