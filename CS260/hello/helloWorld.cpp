#include <iostream>
using namespace std;
#include "currentTime.h"

void pause();

int main()
{
	cout << "Hello from CS260!" << endl << endl;
	cout << "Current time: " << getTime() << endl;

	pause();
	return 0;
}

void pause()
{
	char	ch;
	cout << "Press q followed by Enter key to continue ..." << endl;
	cin >> ch;
}