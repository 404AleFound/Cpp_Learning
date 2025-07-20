// acctabc.cpp -- bank account class methods
#include<iostream>
#include<string>
#include"code-list-13-11-acctabc.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios_base;

//！！！！！！！！！！！！！！！！渇�鷸�窃AcctAbc圭隈！！！！！！！！！！！！！！！！！
void AcctABC::Restore(Formatting& f) const
{
	cout.setf(f.flag, std::ios_base::floatfield);
	cout.precision(f.pr);
}

AcctABC::Formatting AcctABC::SetFormat() const
{
	Formatting f;
	f.flag = cout.setf(ios_base::fixed, ios_base::floatfield);
	f.pr = cout.precision(2);
	return f;
}

AcctABC::AcctABC(const std::string& s, long an, double ba)
{
	fullName = s;
	acctNum = an;
	balance = ba;
}

void AcctABC::Deposit(double amt)
{
	if (amt < 0)
		cout << "Negative deposit not allowed; "
		<< "deposit is cancelled.\n";
	else
		balance += amt;
}

void AcctABC::Withdraw(double amt)
{
	balance -= amt;
}

//！！！！！！！！！！！！！！！！！！！！塗伏窃Brass圭隈！！！！！！！！！！！！！！！！！！！！
void Brass::Withdraw(double amt)
{
	Formatting initialState = SetFormat();

	if (amt < 0)
		cout << "Negative Withdraw not allowed; "
		<< "Withdraw is cancelled.\n";
	else if (amt <= Balance())
		AcctABC::Withdraw(amt);
	else
		cout << "With amount of $" << amt
		<< " exceeds your balace.\n"
		<< "Withdraw canceled.\n";

	Restore(initialState);
}

void Brass::ViewAcct() const
{
	Formatting initialState = SetFormat();

	cout << "Client: " << Fullname() << endl;
	cout << "Account Numbner: " << AcctNum() << endl;
	cout << "Balance: $" << Balance() << endl;

	Restore(initialState);
}

//！！！！！！！！！！！！！！！！！！！！塗伏窃BrassPlus圭隈！！！！！！！！！！！！！！！！！！！！
BrassPlus::BrassPlus(const std::string& s, long a, double bal,
	double ml, double r) : AcctABC(s, a, bal)
{
	maxLoan = ml;
	rate = r;
	owesBank = 0.0;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r) : AcctABC(ba)
{
	maxLoan = ml;
	rate = r;
	owesBank = 0.0;
}

void BrassPlus::ViewAcct() const
{
	Formatting initialState = SetFormat();

	cout << "Client: " << Fullname() << endl;
	cout << "Account Numbner: " << AcctNum() << endl;
	cout << "Balance: $" << Balance() << endl;
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Load Rate: " << 100 * rate << "%\n";

	Restore(initialState);
}

void BrassPlus::Withdraw(double amt)
{
	Formatting initialState = SetFormat();

	double bal = Balance();
	if (amt <= bal)
		AcctABC::Withdraw(amt);
	else if ((amt > bal) && (amt <= bal + maxLoan - owesBank))
	{
// 柴麻処錘
		double advance = amt - bal;
// 柴麻之錘
		owesBank += advance * (1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;
// 繍処錘贋秘
		Deposit(advance);
// 函竃俶勣議署駆
		AcctABC::Withdraw(amt);
	}
	else
		cout << "Credit limit exceeded. Transaction cancelled.\n";

	Restore(initialState);
}