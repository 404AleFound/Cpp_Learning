// useBrass1.cpp -- testing bank account classes
#include<iostream>
#include"code-list-13-07-brass.h"

int main()
{
	using std::cout;
	using std::endl;

	Brass Piggy("Porcelot Pigg", 381299, 4000.0);
	BrassPlus Hoggy("Hoatio Hogg", 382288, 3000.0);
	Piggy.ViewAcct();
	cout << endl;
	Hoggy.ViewAcct();
	cout << endl;

	cout << "Depositing $1000 into the Hoggy Account:\n";
	Hoggy.Deposit(1000.0);
	cout << "New balance: $" << Hoggy.Balance() << endl;

	cout << "Withdrawing $4200 from the Pigg Account:\n";
	Piggy.Withdraw(4200.0);

	cout << "Piggy account balance: $" << Piggy.Balance() << endl;
	cout << "Withdrawing $4200 from the Hoggy Account:\n";
	Hoggy.Withdraw(4200.0);
	Hoggy.ViewAcct();

}