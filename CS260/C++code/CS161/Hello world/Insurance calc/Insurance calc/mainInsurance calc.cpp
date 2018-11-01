// Assignment #5, Maximum House Price Calculator
// Author: Aaron Rito
// Date: 8/4/13
// Sources: CS161 and ParkratPR

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

double Income, interest, R, I;
double loanamount;
double tarpay;
double payment = 0;
double maxhouse;
double minpay;

const double M = 12;
const double T= 30;
 
double readDouble();
double calculatepayment (double M, double Income);
double findR (double &loanamt);
void   abortProgram();

int main()
{
	
    cout << fixed << showpoint << setprecision(2);
    cout << "Please enter your yearly gross salary: ";
    Income = readDouble();
   
    cout << "Please enter an interest rate: ";
    interest = readDouble()/100;
    I= (interest/M); 

	
	tarpay = calculatepayment(M, Income);
	minpay = (tarpay - 10);
	R = findR(loanamount);
	maxhouse = loanamount;
		

    
    cout << "The target (30% of monthly salary) monthly payment range is: $" << tarpay << "-$" << minpay << endl;
	cout << "Your target max house price is: $" << maxhouse << endl;
	cout << "With a payment of: $" << R << endl;

    char reply;
    cout << "Please enter q to quit: ";
    cin >> reply;

    return 0;
}

// This function protects against input errors
double readDouble()
{
    double number;
    cin >> number;
    
    while (cin.fail()) {
        cin.clear();            
        cin.ignore(1000,'\n'); 
        cout << "Please enter a valid number." << endl;
        cout << "Please try again: ";
        cin >> number;
    }
    return number;
}

// calculate payment
double calculatepayment (double M, double Income)
{
	if (Income >=0) {
		tarpay = ((Income *.3)/M);
	}
	return tarpay;
}

//calculate actual payment (R)  
double findR (double &loanamt)
{
	
	loanamt = 0;
	while (payment <= minpay && payment <= tarpay ){
	  loanamt+= 100;
	  payment = (loanamt * I)/(1 - pow(1+I,-M*T));
	
	}

      
   return payment;

}

// This function aborts the program without 'flashing off the screen'.
void abortProgram()

{
    string line;
    cout << "Please press <Enter> to quit:";
    getline(cin, line);
    exit(1);
}

	