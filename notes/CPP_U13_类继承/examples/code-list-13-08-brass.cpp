//brass.cpp -- define the class data and fucntion in brass.h
#include"code-list-13-07-brass.h"
#include<iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;

// 输出流格式控制方法
typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);


//********************************Brass 类成员方法**********************************
// 构造函数
Brass::Brass(const std::string& s, long a, double b)
{	
	fullName = s;
	acctNum = a;
	balance = b;
}

// 存款函数
void Brass::Deposit(double amt) 
{
	if (amt < 0)
		cout << "Negative deposit not allowed; "
		<< "deposit is cancelled.\n";
	else
		balance += amt;
}

// 取款函数
void Brass::Withdraw(double amt) 
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	if (amt < 0)
		cout << "Negative Withdraw not allowed; "
		<< "Withdraw is cancelled.\n";
	else if (amt <= balance)
		balance -= amt;
	else
		cout << "With amount of $" << amt
		<< " exceeds your balace.\n"
		<< "Withdraw canceled.\n";
	restore(initialState, prec);
}

// 展示账户信息
void Brass::ViewAcct() const 
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	cout << "Client: " << fullName << endl;
	cout << "Account Numbner: " << acctNum << endl;
	cout << "Balance: $" << balance << endl;

	restore(initialState, prec);
}

double Brass::Balance() const 
{
	return balance;
}

// 类析构函数
Brass::~Brass() {}

//********************************Brass 类成员方法**********************************


//********************************BrassPlus 类成员方法**********************************

BrassPlus::BrassPlus(const std::string& s, long a, double bal, double ml, double r) : Brass(s, a, bal)
{
	maxLoan = ml;
	rate = r;
	owesBank = 0.0;
}

BrassPlus::BrassPlus(const Brass& ba, double ml, double r) : Brass(ba)
{
	// 不需要重定义复制构造函数，因为这边没用动态变量
	maxLoan = ml;
	rate = r;
	owesBank = 0.0;
}

void BrassPlus::ViewAcct() const
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	Brass::ViewAcct();
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Load Rate: " << 100 * rate << "%\n";

	restore(initialState, prec);
}

void BrassPlus::Withdraw(double amt)
{
	format initialState = setFormat();
	precis prec = cout.precision(2);
	double bal = Balance();
	if (amt <= bal)
		Brass::Withdraw(amt);
	else if ((amt > bal) && (amt <= bal + maxLoan - owesBank))
	{
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		Deposit(advance);
		Brass::Withdraw(amt);

	}
	else
		cout << "Credit limit exceeded. Transaction cancelled.\n";
	restore(initialState, prec);
}

//********************************BrassPlus 类成员方法**********************************
format setFormat()
{
	return cout.setf(std::ios_base::fixed, std::ios::floatfield);
}

void restore(format f, precis p)
{
	cout.setf(f, std::ios_base::floatfield);
	cout.precision(p);
}