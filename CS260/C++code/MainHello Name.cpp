


#include <iostream>                 
#include <string>

using namespace std;                

int main ()
{
    char reply;
    string name;
    string fcolor;
    
    cout << "Hello, Welcome to Aaron's program!" << endl;
    cout << "Please enter your name: ";
    cin >> name;
    cout << "Hello" << " " << name << ", what is your favorite color today?: ";
    cin >> fcolor;
    cout << "That's all for now" << " " << name << " " << "who likes the color" << " " << fcolor << ". Have a great day!" << endl;
    
   
    cout << "Press q (or any other key) followed by 'Enter' to quit: ";
    cin >> reply;
    return 0;
}