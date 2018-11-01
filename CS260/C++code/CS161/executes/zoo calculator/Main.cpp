// This is Aaron Rito's Assigment #3, Zoo Calculator
// Author: Aaron Rito
// Date: 7-13-2013
// Sources: CS161

// Zoo Members get free admission and half off train and bird tickets. At least 1 adult must be in party.


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main ()
{
    // Variable declarations
    double adult, kids, train, birds;
    double guests;
	double totalprice;
    char reply;

	const double discount1= 0, discount2 =.5; 

    
    cout << fixed << setprecision(2);
    cout << "Welcome to Aaron's Zoo Calculator" << endl;
    cout << "How many adults (age 14 or over) are in your party? ";
    cin >> adult;
    if (adult == 0.0) {
        cout << " cannot be zero" << endl;
        cout << "Press q to quit: ";
        cin >> reply;
        exit(1);         
    }
    cout << "How many children (age 5 to 13) are in your party? ";
    cin >> kids;
    cout << "Do you have a family membership? (y/n): ";
    cin >> reply;
    if (reply == 'y' || reply == 'Y') {
        cout << "How many guests in your party?";
	    cin >> guests;
		 cout << "How many train tickets would you like? ";
    cin >> train;
    cout << "How many bird show tickets would you like? ";
    cin >> birds; 

    // If a member, calculate the discount 

    if (guests < 2) {
        totalprice= (( adult *(18)+ kids *(7.5)+ guests*(18))*discount1) + ( (train* (6) +birds*(5))*discount2);
      
        cout << "Your total fee is $"  << totalprice << endl;
		cout << "Thank you for using Aaron's zoo calculator" << endl;
    } else if (guests > 2) {
        
        totalprice= ( (adult*18+ kids*7.5)*discount1) + ( (train* (6) +birds*(5))*discount2)+ (guests*(18)-36);
		cout << "Your total fee is $"  << totalprice << endl; }
	// if not a member, calculate the price
    } else if (reply == 'n' || reply == 'N') {
		cout << "How many train tickets would you like? ";
    cin >> train;
    cout << "How many bird show tickets would you like? ";
    cin >> birds; 
    totalprice=adult*18+ kids*7.5+ train*6 +birds*5;
	cout << "Your total fee is $"  << totalprice << endl;
	cout << "Thank you for using Aaron's zoo calculator" << endl;
	
	}  
	
	cout << "Press q to quit: ";
    cin >> reply;
    return 0;
}