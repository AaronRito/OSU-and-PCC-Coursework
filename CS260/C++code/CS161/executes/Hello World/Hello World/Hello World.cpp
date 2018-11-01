// This is the Hello World program (HelloWorld.cpp)
// Note: You should always start with a description of your program here.
// Written by: Aaron Rito
// Note: Please put your name here or both names if you are working in a pair.
// Date: 29 June 2013
// Note: Put the current date here
// Sources: None
// Note: Always cite all sources you may have used, such as other students you
// may have had help from, web sites you may have referenced, and so forth.
// If none, write None.

// The next few lines are standard boilerplate you will need...
// ...in front of virtually every C++ program you will write this term.

#include <iostream>                 //Required if your program does any I/O
#include <string>                   //Required if your program uses C++ strings

using namespace std;                //Required for ANSI C++ 1998 standard.

int main ()
{
    char reply;
    cout << "Hello World" << endl;
    
    // This section stops the program 'flashing' off the screen.
    cout << "Press q (or any other key) followed by 'Enter' to quit: ";
    cin >> reply;
    return 0;
}