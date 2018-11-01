// Tiernan C Smith
// July 17th of 2014
// Assignment #2 - Bank ATM Interface
// Sources: Aaron Rito(taking a parallel CS162 Class)
// Internet Sources: 
// http://www.bogotobogo.com/cplusplus/linkedlist.php#linkedlistexample1
// This will simulate a Bank ATM with the option for a Customer and Bank Employee
//ATM.H

#include <fstream>
#include <vector>
 
#ifndef ATM_H
#define ATM_H
 
using namespace std;
 
//New Account class that will add variables to a doubly linked list node.
class Account {
public:
     //local variable declarations. 
    string name;
    int accountNumber;
    float currentBalance;
    Account *next; //create a pointer that points to next node in list.
    Account *prev; //creates a pointer that points to previous node in list.
     
    //default consuctor.
    Account()
    {
        next = 0;
        prev = 0;
    }
    //Consuctor that takes in 4 parameters
    Account(string nName, int nAccount, float cBalance)
    {
        name = nName;
        accountNumber = nAccount;
        currentBalance = cBalance;
    }
};
 
//creates a new class ATM that will add, 
// delete, withdraw, deposit, and check balance.
class ATM
{
public:
     
    Account *head;  //pointer to the first node.
    Account *tail; //pointer to the last node.
 
    //default consuctor sets head and tail to 0.
    ATM()
    {
         //list is empty.
        head = 0;
        tail = 0;
    }
     
    //method declarations.
    void AddAccount(string nName, int aNumber, float iDeposit);
    void RemoveAccount(string nName, int aNumber);
	void SearchAccount(string nName);
    void WithdrawFromAccount(string nName, int aNumber, float withdrawalAmount);
    void DepositIntoAccount(string nName, int aNumber, float deposit);
    string BalanceInquiry(string nName, int aNumber);
     
    //Desuctor
    ~ATM()
    {
        //checks if there's items in the list.
        while(head != 0)
        {
            Account *next = head->next; //updates the head pointer to point to the next node.
            delete head; //deletes the node in the beginning of the list.
            head = next; //updates next pointer to equal the first node in the list.
        }
     }
};

#endif