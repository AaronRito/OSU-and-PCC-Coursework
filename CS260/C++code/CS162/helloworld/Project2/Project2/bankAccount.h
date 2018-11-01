#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

class BankAccount
{
public:
	//constructors
	BankAccount();
	BankAccount(double initAmount);

	//destructor
	~BankAccount();

	//member functions
	double getBalance() const;			//accessor 
	void deposit(double amount);		//mutator
	bool withdraw(double amount);		//mutator
	void print() const;
	static int getMaxLimit();
private:
	double balance;						//instance variable
	static const int MAX_LIMIT = 10000;	//class variable
};
#endif