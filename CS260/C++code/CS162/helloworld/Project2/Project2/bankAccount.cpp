#include "bankAccount.h"
#include "myutil.h"

BankAccount::BankAccount()
{
	balance = 0;
}

BankAccount::BankAccount(double initAmount)

{
	balance = initAmount;
}

BankAccount::~BankAccount()
{
	cout << "destructor is invoked" << endl;
}
double BankAccount::getBalance() const
{
	return balance;
}

void BankAccount::print() const
{
	cout << "Balance: " << balance << endl;
}

void BankAccount::deposit(double amount)
{
	balance += amount;
}

bool BankAccount::withdraw(double amount)
{
	if (amount <= balance)
	{
		balance -= amount;
		return true;
	}
	return false;
}

int BankAccount::getMaxLimit()
{
	return MAX_LIMIT;
}