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
// ���캯��
	Brass(const std::string& s = "Nullbody", long a = -1,
		double b = 0.0);
// ����
	void Deposit(double amt);
// ȡ���
	virtual void Withdraw(double amt);
// չʾ�˻���Ϣ
	virtual void ViewAcct() const;
// ��������
	double Balance() const;
// ����������
	virtual ~Brass() {};
};


class BrassPlus : public Brass 
{
// ��Brass��Ļ����Ϲ���BrassPlus���������
// ����BrassPlus������Ա����
// ���麯��ViewAcct()��Withdraw()���¶��壬ʹ���ʺ�BrassPlus�����
// ��Ӷ�Ӧ��������Ĺ��캯��
// ���һЩ�������õĳ�Ա����
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
