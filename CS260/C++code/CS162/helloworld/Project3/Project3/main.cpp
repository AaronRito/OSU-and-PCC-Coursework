// Tiernan C Smith
// July 17th of 2014
// Assignment #2 - Bank ATM Interface
// Sources: Aaron Rito(taking a parallel CS162 Class)
// Internet Sources: 
// http://www.bogotobogo.com/cplusplus/linkedlist.php#linkedlistexample1
// This will simulate a Bank ATM with the option for a Customer and Bank Employee;
;
#include <iostream>
#include "ATM.h"


using namespace std;

int main() {
	// initializing variables
	char CorBE;
	char CMSel;
	char BEMSel;

	cout << "Assignment #2 - Bank ATM Interface - Tiernan Smith" << endl
		 << "Welcome to Rising Sun's ATM" << endl
		 << "Please select one of the following" << endl
		 << "A: Customer B: Bank Employee" << endl;
	cin  >> CorBE;

	switch(CorBE) {
	case 'a':
	case 'A':	
		cout << "Please enter your Account Number" << endl;
			cin  >> aNumber;

			if(current->accountNumber == aNumber) {
				cout << "A: Deposit funds into account" << endl
					 << "B: Withdraw funds from account" << endl
					 << "C: Quit" << endl;
				cin  >> CMSel;
				
				switch(CMSel) {
				case 'a':
				case 'A':
						void DepositIntoAccount(string nName, int aNumber, float deposit);

						break;
					
				case 'b':
				case 'B':
						void WithdrawFromAccount(string nName, int aNumber, float withdrawalAmount);

						break;

				case 'c':
				case 'C':
						cout << "Press a key to exit..." >> endl;
						getchar();
						return 0;

						break;

					// default on 2nd switch for Customer
					default: 
						cout << "Invalid choice, please try again";

						break;
				}

			}

				break;

	case 'b':
	case 'B':
			cout << "A: Add a Customer" << endl
				 << "B: Remove a Customer" << endl
				 << "C: Search for a customer" << endl
				 << "D: Quit" << endl;
			cin >> BEMSel;

			switch(BEMSel) {
			case 'a':
			case 'A':
					void AddAccount(string nName, int aNumber, float iDeposit);

					break;

			case 'b':
			case 'B':
					 void RemoveAccount(string nName, int aNumber);

					break;

			case 'c':
			case 'C':
					void SearchAccount(string nName);

					break;

			case 'd':
			case 'D':
					cout << "Press a key to exit..." << endl;
					getchar();
					return 0;

					break;

				// default on 2nd switch for Bank Employee
				default: 
					cout << "Invalid choice, please try again";

					break;
			}

				break;

		// default on 1st switch
		default:
			cout << "Invalid choice, please try again";

			break;
}