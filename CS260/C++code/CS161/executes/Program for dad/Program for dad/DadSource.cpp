// This is my program for Dad (DadSource.cpp)
// Written by: Aaron Rito
// Date: 30 June 2013
// Sources: None


#include <iostream>                 
#include <string>

using namespace std;                

int main ()
{
    char reply;
    string name;
    string fcolor;
    
    cout << "Hello Dad, Welcome to my program just for you!" << endl;
    cout << "How was your ride yesterday? ";
    cin >> name;
    cout << "That's great that your ride was" << " " << name << ". What is the tempature in State College today?";
    cin >> fcolor;
    cout << " Wow!" << " " << fcolor << ", that must be hard to ride in!" << "Glad to hear your ride was " << name << " even though it was " << fcolor << " outside. I wanted to send you this program to say thanks for all the help you've been giving me and tell you that I'm working really hard. I got an 87% on one quiz and an 80% on another. Still training my brain to think different. Hope you have a good Sunday!" << endl;
    
   
    cout << "Press q (or any other key) followed by 'Enter' to quit: ";
    cin >> reply;
    return 0;
}