// main driver
// names generated through 
// www.behindthename.com/
 
#include <fstream>
#include "ATM.h"; // include header file
 
using namespace std;
 
int main()
{
     
    ATM *account;  //create a new ATM object
    account = new ATM(); //pass in default parameters for new doubly linked list.

    ofstream myfile;
    myfile.open("output.txt");
     
    //Add account method calls.
    account->AddAccount("Sylvanus Cartwright", 0, 6000000);
    account->AddAccount("Pansy Pemberton", 1, 5000000);   
    account->AddAccount("Delta Gardner", 2, 4000000);
    account->AddAccount("Edmund Boon", 3, 2000000);
    account->AddAccount("Lucetta Saunders", 4, 1500000);
    account->AddAccount("Val Drake", 5, 10000000);
    account->AddAccount("Kimberleigh Jeffers", 6, 8000000);
    account->AddAccount("Linzi Whittemore", 7, 7000000);
    account->AddAccount("Brice Traviss", 8, 10000000.);
    account->AddAccount("Fleur Wade", 9, 10000000.);
    account->AddAccount("Cass Simms", 10, 6000000);
 
    //Balance Inquiry method calls.
    account->BalanceInquiry("Val Drake", 3);
    account->BalanceInquiry("Brice Traviss", 7);
    account->BalanceInquiry("Fleur Wade", 9);
    account->BalanceInquiry("Edmund Boon", 3);
    account->BalanceInquiry("Val Drake", 5);
    account->BalanceInquiry("Delta Gardner", 12);
     
    //Deposit into account method calls.
     account->DepositIntoAccount("Sylvanus Cartwright",0,200000);
     account->DepositIntoAccount("Linzi Whittemore", 7, 200000);
     account->DepositIntoAccount("Sylvanus Cartwright",0,200000);
     account->DepositIntoAccount("Cass Simms", 10, 2000000);
     account->DepositIntoAccount("Pansy Pemberton", 1, 2000000);
     account->DepositIntoAccount("Fleur Wade", 9, 1000000);
 
    //Withdraw from account method calls.
    account->WithdrawFromAccount("Sylvanus Cartwright",0,200000000);
    account->WithdrawFromAccount("Linzi Whittemore", 7, 500000);
    account->WithdrawFromAccount("Brice Traviss",  8, 1000000);
    account->WithdrawFromAccount("Cass Simms",10, 1000000);
    account->WithdrawFromAccount("Fleur Wade",  9, 300000);
 
    //Balance Inquiry method calls.
    account->BalanceInquiry("Sylvanus Cartwright", 0);    
    account->BalanceInquiry("Rafa_Nadal",  10);
    account->BalanceInquiry("Linzi Whittemore", 7);
    account->BalanceInquiry("Brice Traviss",  8);
    account->BalanceInquiry("Cass Simms",  10);
    account->BalanceInquiry("Fleur Wade",  9);

    //Remove accounts
    account->RemoveAccount("Brice Traviss", 8);
    account->RemoveAccount("Sylvanus Cartwright", 0);
    account->RemoveAccount("Delta Gardner", 10);
 
    myfile.close();
    delete account; // delete account object.
    system("Pause");
     
    return 0;
}
