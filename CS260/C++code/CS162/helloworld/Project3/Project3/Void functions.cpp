// Tiernan C Smith
// July 17th of 2014
// Assignment #2 - Bank ATM Interface
// Sources: Aaron Rito(taking a parallel CS162 Class)
// Internet Sources: 
// http://www.bogotobogo.com/cplusplus/linkedlist.php#linkedlistexample1
// This will simulate a Bank ATM with the option for a Customer and Bank Employee

#include "ATM.h"
#include <fstream>
using namespace std;
 
//Adds accounts to a doubly linked list.
void ATM::AddAccount(string nName, int aNumber, float iDeposit)
{
     ofstream myfile("output.txt",ios::app);
     Account *newAccount = new Account(nName, aNumber, iDeposit);  //creates a new temporary Account pointer with 4 parameters.
         
     //checks to see if list is empty.  
     if(head == 0)
     {
         head = newAccount;  //add the node to the beginning of the list.
     }
     else
     {
         tail->next = newAccount; //adds the node end of the list.
         newAccount->prev = tail; //updates the tail node.
     }
     tail = newAccount; //adds the data to the tail list.
 
    newAccount->next = NULL;
 
     //creates a new stringstream variable in order to add to a the vector.
     stringstream ss;
     ss << "Account Name: " << nName << " was created with an Account Number: " 
		<< aNumber << endl; //used to add to the vector.

     string s = ss.s();  //convert the stringstream into the string.
     myfile << s << endl;
     newAccount->transHistory.push_back(s); //add the s string into the vector.
     myfile.close();
}

 
// This method will pass in 3 parameters and check to see if the name and number are correct 
// before removing the account.
void ATM::RemoveAccount(string nName, int aNumber)
{
     ofstream myfile("output.txt",ios::app);
     //checks to see if the account exists first.
     if (head == 0)
     {
          cout << "Account Name: " << nName << ": Account does not exist!" << endl;
          myfile << "Account Name: " << nName << ": Account does not exist!" << endl;
          myfile.close();
          return;
     }
          //create a new temporary pointer and make it equal to the beginning of the list.
          Account *current = head;
          //Iterate through the list to find the correct node.
          while(current->name != nName || current->accountNumber != aNumber)
     {
          current = current->next; //if not found yet go to the next node in the list.
          //if check fails.
          if(current == 0)
          {
               cout << "Account Name: " << nName << ": Account does not exist!" << endl;
               myfile << "Account Name: " << nName << ": Account does not exist!" << endl;
               myfile.close();
               return;
          }
      }
      //check to see if the node is at the beginning of the list.
      if (current == head)
      {
           head = current->next; //update the current pointer.
      }
      else
      {
           current->prev->next = current->next; //updates the position in the list
      }
      //check to see if node is at the end of the list.
      if(current == tail)
      {
            tail = current->prev; //update the current pointer.
      }
      else
      {
            current->next->prev = current->prev; //updates the position in the list.
      }
       
      cout << "Account name: " << nName << endl;
      myfile  << "Account name: " << nName << endl;
      myfile.close();
}
 
//Method that will withdraw funds from an account, but will check to see if the name and number is correct.
void ATM::WithdrawFromAccount(string nName, int aNumber, float withdrawalAmount)
{
     ofstream myfile("output.txt",ios::app);
     //checks to see if list is empty.
     if(head == 0)
     {
           cout << "Withdrawal: Account: " << nName << " can't be found. " << endl;
           myfile << "Withdrawal: Account: " << nName << " can't be found. " << endl;
           myfile.close();
           return;
     }
     //create a new temporary Account pointer.
     Account *current = head;
     //checks to see if the name and number are correct.
     while(current->name != nName || current->accountNumber != aNumber)
     {
           current = current->next; //iterates through the list if not correct.
            
           //if the check fails.
           if(current == 0)
           {
                cout << "Withdrawal: Account Name: " << nName << " can't be found" << endl;
                myfile << "Withdrawal: Account Name: " << nName << " can't be found. " << endl;
                myfile.close();
                return;
           }
     }
     //checks to see if the currentBalance is greater than the withdraw amount.
     if (current->currentBalance >= withdrawalAmount)
     {
           current->currentBalance = current->currentBalance - withdrawalAmount; //updates the current balance.
            
           //create a new stringstream variable in order to add to the vector.
           stringstream ss;
           ss << "Withdrawal: Account Name: " << nName << ", Account: " << aNumber << ", Withdrew $" 
			  << withdrawalAmount << " Available Balance is $" << current->currentBalance << endl;
           string s = ss.s(); //convert the stringstream to a string.
           current->transHistory.push_back(s); //adds the s string to the transHistory vector.
            
     }
     //If check fails print out that there is not enough funds.
     else
     {
           cout << "Withdrawal: Account Name: " << nName << "Account Number: " << aNumber 
		        << ": Not enough funds in bank account." << " Account Balance: $" << current->currentBalance << endl;
           stringstream ss;
           ss << "Withdrawal: Account Name: " 
		      << nName << ": Not enough funds in bank account." << endl;
           string s = ss.s();
           current->transHistory.push_back(s); //adds the s string to the vector.
           myfile << s << endl;
     } 
     myfile.close();    
}
 
//This method will deposit funds into the account and update the current balance to this new amount.
void ATM::DepositIntoAccount(string nName, int aNumber, float deposit) {
     ofstream myfile("output.txt",ios::app);
     //checks to see if list is empty.
     if(head == 0)
     {
          cout << "Deposit: Account Name: " << nName << " can't be found." <<endl;
          myfile << "Deposit: Account Name: " << nName << " can't be found." <<endl;
          myfile.close();
          return;
     }
     //creates a new temporary Account pointer.
     Account *current = head;
     //checks to see if the account name and number are correct.
     while(current->name != nName || current->accountNumber != aNumber)
     {
          current = current->next; //iterates through the list.
           
          //if check fails.
          if(current == 0)
          {
               cout << "Deposit: Account Name: " << nName << " can't be found. " << endl;
               myfile << "Deposit: Account Name: " << nName << " can't be found." <<endl;
               myfile.close();
               return;
          }
     }
     //updates currentBalace of the account.
     current->currentBalance = current->currentBalance + deposit; //adds the deposit parameter to update balance.
      
     stringstream ss;
     ss << "Deposit:" << " Account Name: " << nName << ", Account number: " << aNumber 
	    << ", Deposited $" << current->currentBalance << endl;
     string s = ss.s(); //converts the stringstream variable into a string.
     current->transHistory.push_back(s); //adds s to the vector.
     myfile.close();
}
 
// This method will return a string and print out the current balance of the account. 
// It will also check to see if the account name and number is valid.
string ATM::BalanceInquiry(string nName, int aNumber); {
     ofstream myfile("output.txt",ios::app);
     //check to see if list is empty.
     if(head == 0)
     {
          stringstream ss;
          ss << "Balance Inquiry:  Account Name: " << nName << " cannot be found." << endl;
          string s = ss.s();
          myfile << s << endl;
          myfile.close();
          return s;
     }
     //creates a new temporary pointer and set it to beginning of the list.
     Account *current = head;
     //checks to see if name and number of account are correct.
     while(current->name != nName || current->accountNumber != aNumber)
     {
           current = current->next; //iterates through the list.
           //if check fails.
           if(current == 0)
           {
               //prints out an error message.
               stringstream ss;
               ss << "Balance Inquiry:  Account Name: " << nName << " cannot be found." << endl;
               string s = ss.s();
               myfile << s << endl;
               myfile.close();
               return s;
           }
     }
     //creats a new stringstream variable
     stringstream ss;  
     ss << "Balance Inquiry: " << nName << ", Account: " << aNumber << ", Date: " 
	    <<  ", Available balance: $" << current->currentBalance << endl;
     string s = ss.s(); //converts ss to a string.
     current->transHistory.push_back(s); //add the string to the vector.
     myfile.close();
     return s; //return the string.

}

void SearchAccount string nName; {
	char repeat
	cout << "Please enter your full name: (First Last)" << endl;
	cin  >> nName;

	if(current->name == nName) {
		cout << "We have found your account" << endl;
	} else {
		cout << "We have not found your account" << endl
			 << "If you would like to try again select R" << endl
			 << "If you would like to do something else refer to menu" << endl;
		cin repeat
		
		if( repeat == 'r' || repeat == 'R') {
			void SearchAccount(string nName)
		} else {
			cin BEMSel;
		}
	}
}