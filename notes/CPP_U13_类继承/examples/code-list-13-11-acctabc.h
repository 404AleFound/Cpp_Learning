// acctabc.h -- bank account classes
#ifndef ACCTABC_H_
#define ACCTABC_H_

#include<string>
#include<iostream>

//！！！！！！！！！！！！！！！！！！！！渇�鷸�窃AcctABC！！！！！！！！！！！！！！！！！！！！
class AcctABC
{
private:
	std::string fullName;
	long acctNum;
	double balance;

protected:
	struct Formatting
	{
		std::ios_base::fmtflags flag;
		std::streamsize pr;
	};
// 響函fullName
	const std::string& Fullname() const { return fullName; }
// 響函acctNum
	long AcctNum() const { return acctNum; }
// 響函balance
	double Balance() const { return balance; }
// 鯉塀譜崔
	Formatting SetFormat() const;
	void Restore(Formatting& f) const;

public:
	AcctABC(const std::string& s = "Nullbody", long an = -1, double ba = 0.0);

	void Deposit(double amt);

	virtual void Withdraw(double amt) = 0;

	virtual void ViewAcct() const = 0;

	virtual ~AcctABC() {};
};


//！！！！！！！！！！！！！！！！！！！！塗伏窃Brass！！！！！！！！！！！！！！！！！！！！
class Brass : public AcctABC
{
public:
	Brass(const std::string& s = "Nullbody", long a = -1,double b = 0.0) : AcctABC(s, a, b) {}

	virtual void Withdraw(double amt);

	virtual void ViewAcct() const;

	virtual ~Brass() {};
};

//！！！！！！！！！！！！！！！！！！！！塗伏窃BrassPlus！！！！！！！！！！！！！！！！！！！！
class BrassPlus : public AcctABC
{
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const std::string& s = "Nullbody", long a = -1, double bal = 0.0,
		double ml = 500, double r = 0.11125);

	BrassPlus(const Brass& ba, double ml = 500, double r = 0.11125);

	virtual void ViewAcct() const;

	virtual void Withdraw(double amt);

	void ResetMax(double m) { maxLoan = m; }
	void ResetRate(double r) { rate = r; }
	void ResetOwes(double o) { owesBank = o; }
};


#endif // !ACCTABC_H_
