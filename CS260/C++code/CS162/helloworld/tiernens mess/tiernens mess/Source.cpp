/*
Tiernan C Smith
July 17th of 2014
Assignment #2 - Bank ATM Interface
This will simulate a Bank ATM with the option for a Customer and Bank Employee
*/;


#include <stdlib.h>;
#include <iostream>;
using namespace std;

const int SIZE = 100;

int main() {
	
	// Initialize Variables
	char CorBE;  // Customer or Bank Employee
	char MselC;  // Menu Select for Customers
	char MselBE;  // Menu Select for Bank Employee
	char TC; // Transfer Choice
	char TF; // Transfer 
	char WF; // Withdrawal From
	char DC; // Deposit Choice
	char YN;
	double Balance = 00.00;
	double Deposit = 00.00;
	double Withdraw = 00.00;
	double Transfer = 00.00;
	double Checking = 00.00;
	double Savings = 00.00;
	double CreditCard = 00.00;
	double InstantAccess = 00.00;
	bool TorF;   // True or False?

	//struct Database {
	//	char name[SIZE]
	//	float amount
	//} account[SIZE];	
	//enum AccountType {
	//	unknown = -1, Checking, Savings, CreditCard, Instant Access
	//};

	// Prompt and User Input
	cout << "Assignment #2 - Bank ATM Interface - Tiernan Smith" << endl
		 << "Welcome to Rising Sun's ATM" << endl
		 << "Please select one of the following" << endl
		 << "A: Customer B: Bank Employee" << endl;
	cin  >> CorBE;

	// Customer or Bank Employee?
	switch(CorBE) {
		case 'a':
		case 'A':
			cout << "A) Check Balance" << endl
				 << "B) Deposit"       << endl
				 << "C) Withdraw"      << endl
				 << "D) Transfer Funds"<< endl
				 << "E) Quit"          << endl;
			cin  >> MselC;
			break;

		case 'b':
		case 'B':
			cout << "A) Check Balance"   << endl
			     << "B) Deposit"         << endl
			     << "C) Withdraw"        << endl
			     << "D) Transfer Funds"  << endl
                 << "E) Add Customer"    << endl
			     << "F) Delete Customer" << endl
			     << "G) Search Database" << endl
		         << "H) Quit"            << endl;
			 cin >> MselBE;
			 break;

		case 'e':
		case 'E':
		case 'h':
		case 'H':
			cout << "Are you sure? [Y/N]" << endl;
			exit('Y');
			break;

		// Error checking 1st switch
		default:
			cout << "Invalid input, please type in a valid input" << endl;
			TorF = false;
			break;
	}

	switch(MselC) {
		case 'a':
		case 'A':
			Balance = Checking + Savings;
			cout << "Your current account balance is:" << Balance       << endl
			     << "Checking: " << Checking << " Savings: " << Savings << endl
			     << "Select another option, or e to quit"               << endl;		
			break;
				 
		case 'b':
		case 'B':
			cout << "Please select which account you would like to deposit to" << endl
			     << "A: Checking, B: Savings"                                  << endl;
			cin  >> DC;

		switch(DC) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Deposit(00.00)" << endl;
				cin  >> Deposit;
				Checking = Checking + Deposit;
				cout << "Checking: " << Checking << endl
				     << "Select another option, or e to quit" << endl;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Deposit(00.00)" << endl;
				cin  >> Deposit;
				Savings = Savings + Deposit;
				cout << "Savings: " << Checking << endl
					 << "Select another option, or e to quit" << endl;
				break;
			
			case 'e':
			case 'E':
				cout << "Are you sure? [Y/N]" << endl;
				cin  >> YN;
				if(YN == 'y' && 'Y') {
					exit('Y');
				} else {
					break;
				}

			// Error checking 2nd switch
			default:
				cout << "Invalid input, please type in a valid input" << endl;
				TorF = false;
				break;
		}
	break;
		
	case 'c':
	case 'C':
		cout << "Please select which account you would like to withdraw from" << endl
			 << " A: Checking, B: Savings, C: Credit Card, D: Instant Access" << endl;
		cin  >> WF;
		switch(WF) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				Checking = Checking - Withdraw;
				cout << "Checking : " << Checking << endl
					 << "Select another option, or e to quit" << endl;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				Savings = Savings - Withdraw;
				cout << "Savings : " << Savings << endl
					 << "Select another option, or e to quit" << endl;
				break;

			case 'c':
			case 'C':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				CreditCard = CreditCard - Withdraw;
				cout << "CreditCard : " << CreditCard << endl
					 << "Select another option, or e to quit" << endl;
				break;
				
			case 'd':
			case 'D':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				InstantAccess = InstantAccess - Withdraw;
				cout << "Instant Access : " << InstantAccess << endl
					 << "Select another option, or e to quit" << endl;
				break;

			case 'e':
			case 'E':
				cout << "Are you sure? [Y/N]" << endl;
				exit('Y');
				break;

			// Error checking 2nd switch
			default:
				cout << "Invalid input, please type in a valid input" << endl;
				TorF = false;
				break;		
			}
	break;

	case 'd':
	case 'D':
		cout << "Please select which account you would like to transfer from" << endl
			 << "A: Checking, B: Savings, C: Credit Card, D: Instant Access"  << endl;
		cin  >> TF;
		switch(TF) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin	 >> Transfer;
				Checking = Checking - Transfer;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin  >> Transfer;
				Savings = Savings - Transfer;
				break;

			case 'c':
			case 'C':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin  >> Transfer;
				CreditCard = CreditCard - Transfer;
				break;

			case 'd':
			case 'D':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin  >> Transfer;
				InstantAccess = InstantAccess - Transfer;
				break;
					
			// Error check on 2nd switch
		default:
			cout << "Invalid input, please type in a valid input" << endl;
			TorF = false;
			break;
		}	
	cout << "Please select which account you would like to transfer to" << endl
		 << "A: Checking, B: Savings, C: Credit Card, D: Instant Access" << endl;
	cin  >> TC;
	switch(TC) {
		case'a':
		case'A':
			Checking = Checking + Transfer;
			cout << "Checking : " << Checking << endl
				 << "Select another option, or e to quit" << endl;
			break;

		case 'b':
		case 'B':
			Savings = Savings + Transfer;
			cout << "Savings : " << Savings << endl
				 << "Select another option, or e to quit" << endl;
			break;

		case 'c':
		case 'C':
			CreditCard = CreditCard + Transfer;
			cout << "Credit Card : " << CreditCard << endl
				 << "Select another option, or e to quit" << endl;
			break;

		case 'd':
		case 'D':
			InstantAccess = InstantAccess + Transfer;
			cout << "InstantAccess : " << InstantAccess << endl
				 << "Select another option, or e to quit" << endl;
			break;
					
		// Error check on 2nd switch
		default:
			cout << "Invalid input, please type in a valid input" << endl;
			TorF = false;
			break;
		}
	// Error checking 1st switch
	default:
		cout << "Invalid input, please type in a valid input" << endl;
		TorF = false;
		break;
		}

		switch (MselBE) {
		case 'a':
		case 'A':
			Balance = Checking + Savings;
			cout << "Your current account balance is:" << Balance       << endl
			     << "Checking: " << Checking << " Savings: " << Savings << endl
			     << "Select another option, or e to quit"               << endl;		
			break;

		case 'b':
		case 'B':
			cout << "Please select which account you would like to deposit to" << endl
			     << "A: Checking, B: Savings"                                  << endl;
			cin  >> DC;

		switch(DC) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Deposit(00.00)" << endl;
				cin  >> Deposit;
				Checking = Checking + Deposit;
				cout << "Checking: " << Checking << endl
				     << "Select another option, or e to quit" << endl;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Deposit(00.00)" << endl;
				cin  >> Deposit;
				Savings = Savings + Deposit;
				cout << "Savings: " << Checking << endl
					 << "Select another option, or e to quit" << endl;
				break;
			
			// Error checking 2nd switch
			default:
				cout << "Invalid input, please type in a valid input" << endl;
				TorF = false;
				break;
		}
	break;
		
	case 'c':
	case 'C':
		cout << "Please select which account you would like to withdraw from" << endl
			 << " A: Checking, B: Savings, C: Credit Card, D: Instant Access" << endl;
		cin  >> WF;
		switch(WF) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				Checking = Checking - Withdraw;
				cout << "Checking : " << Checking << endl
					 << "Select another option, or e to quit" << endl;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				Savings = Savings - Withdraw;
				cout << "Savings : " << Savings << endl
					 << "Select another option, or e to quit" << endl;
				break;

			case 'c':
			case 'C':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				CreditCard = CreditCard - Withdraw;
				cout << "CreditCard : " << CreditCard << endl
					 << "Select another option, or e to quit" << endl;
				break;
				
			case 'd':
			case 'D':
				cout << "Please type the amount that you would like to Withdraw(00.00)" << endl;
				cin  >> Withdraw;
				InstantAccess = InstantAccess - Withdraw;
				cout << "Instant Access : " << InstantAccess << endl
					 << "Select another option, or e to quit" << endl;
				break;
			// Error checking 2nd switch
			case 'e':
			case 'E':
				cout << "Are you sure? [Y/N]" << endl;
				exit('Y');
				break;

			default:
				cout << "Invalid input, please type in a valid input" << endl;
				TorF = false;
				break;		

			}
	break;

	case 'd':
	case 'D':
		cout << "Please select which account you would like to transfer from" << endl
			 << "A: Checking, B: Savings, C: Credit Card, D: Instant Access"  << endl;
		cin  >> TF;
		switch(TF) {
			case 'a':
			case 'A':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin	 >> Transfer;
				Checking = Checking - Transfer;
				break;

			case 'b':
			case 'B':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin  >> Transfer;
				Savings = Savings - Transfer;
				break;

			case 'c':
			case 'C':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin >> Transfer;
				CreditCard = CreditCard - Transfer;
				break;

			case 'd':
			case 'D':
				cout << "Please type the amount that you would like to Transfer(00.00)" << endl;
				cin >> Transfer;
				InstantAccess = InstantAccess - Transfer;
				break;
					
			// Error check on 2nd switch
			default:
				cout << "Invalid input, please type in a valid input" << endl;
				TorF = false;
				break;
			}	
	cout << "Please select which account you would like to transfer to" << endl
		 << "A: Checking, B: Savings, C: Credit Card, D: Instant Access" << endl;
	cin  >> TC;
	switch(TC) {
		case'a':
		case'A':
			Checking = Checking + Transfer;
			cout << "Checking : " << Checking << endl
				 << "Select another option, or h to quit" << endl;
			break;

		case 'b':
		case 'B':
			Savings = Savings + Transfer;
			cout << "Savings : " << Savings << endl
				 << "Select another option, or h to quit" << endl;
			break;

		case 'c':
		case 'C':
			CreditCard = CreditCard + Transfer;
			cout << "Credit Card : " << CreditCard << endl
				 << "Select another option, or h to quit" << endl;
			break;

		case 'd':
		case 'D':
			InstantAccess = InstantAccess + Transfer;
			cout << "InstantAccess : " << InstantAccess << endl
				 << "Select another option, or h to quit" << endl;
			break;

		case 'h':
		case 'H':
			cout << "Are you sure? [Y/N]" << endl;
			exit('Y');
			break;
			
					
		// Error check on 2nd switch
		default:
			cout << "Invalid input, please type in a valid input" << endl;
			TorF = false;
			break;
		}

	// Add - this
	case 'e':
	case 'E':

		break;

	//Remove - this
	case 'f':
	case 'F':

		break;

	// Search - this
	case 'g':
	case 'G':
		
		break;

	case 'h':
	case 'H':
		cout << "Are you sure? [Y/N]" << endl;
		exit('Y');
		break;

	// Error check on 1st switch
	default:
		cout << "Invalid input, please type in a valid input" << endl;
		TorF = false;
		break;
	}

	// Pause and Exit - having issues w/ this
	system("pause");
	return 0;

}
