#include "myutil.h"
#include "bankAccount.h"
int main()
{
	BankAccount a1;
	BankAccount a2(100);

	//a1.balance = 1000;
	cout << "Balance in a1: " << a1.getBalance() << endl;
	a1.deposit(1000);
	if (!a1.withdraw(5000))
	{
		cout << "Withdraw failed!" << endl;
	}
	cout << "Current balance in a1: " << a1.getBalance() << endl;
	a2.deposit(100);
	cout << "Current balance in a2: " << a2.getBalance() << endl;
	a1.print();
	a2.print();
	cout << "Max limit: " << BankAccount::getMaxLimit() << endl;
	pause();
	return 0;
}