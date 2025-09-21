// brass.h -- bank acount classes
#ifndef BRASS_H_
#define BRASS_H_
#include<string>


class Brass
{
private:
	std::string fullName;
	long acctNum;
	double balance;
public:
// 构造函数
	Brass(const std::string& s = "Nullbody", long a = -1,
		double b = 0.0);
// 存款函数
	void Deposit(double amt);
// 取款函数
	virtual void Withdraw(double amt);
// 展示账户信息
	virtual void ViewAcct() const;
// 返回余额函数
	double Balance() const;
// 类析构函数
	virtual ~Brass() {};
};


class BrassPlus : public Brass 
{
// 在Brass类的基础上构建BrassPlus类的派生类
// 新增BrassPlus三个成员数据
// 对虚函数ViewAcct()，Withdraw()重新定义，使其适合BrassPlus类对象
// 添加对应的派生类的构造函数
// 添加一些用于重置的成员函数
private:
	double maxLoan;
	double rate;
	double owesBank;
public:
	BrassPlus(const std::string& s = "Nullbody", long a = -1, double bal = 0.0, double ml = 500, double r = 0.11125);
	BrassPlus(const Brass& ba, double ml = 500, double r = 0.11125);

	virtual void ViewAcct() const;
	virtual void Withdraw(double amt);

	void ResetMax(double m) { maxLoan = m; }
	void ResetRate(double r) { rate = r; }
	void ResetOwes(double o) { owesBank = o; }
};


#endif // !BRASS_H_
