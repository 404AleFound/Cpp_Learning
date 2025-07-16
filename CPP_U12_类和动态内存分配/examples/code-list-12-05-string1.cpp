// strngbad.cpp -- StringBad class methods
#define _CRT_SECURE_NO_WARNINGS
# include <cstring>
# include "code-list-12-04-string1.h"
using std::cout;
using std::cin;


int String::num_strings = 0;

// ===============定义类方法===============
String::String(const char* s)
{
// 删除显式输出
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;
}

String::String()
{
// 不使用字符串"C++"作为默认构造函数的值
// 注意这边使用str = new char[1]，而非str = new char
// 为了和析构函数delete [] str;保持兼容
	len = 0;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

String::String(const String& s)
{
// 新增复制构造函数，注意使用深拷贝
	num_strings++;
	len = s.len;
	str = new char[len + 1];
	std::strcpy(str, s.str);
}

String::~String()
{
// 删除显示输出
	--num_strings;
	delete [] str;
}
// ===========================================


// ===============定义重载的运算符===============
String& String::operator=(const String & s)
{
// 将一个String赋值给另一个String对象，注意同样使用深拷贝
// 由于是赋值，所以静态成员num_strings不需要加1
// 如果自己给自己赋值，则不进行任何操作，同时返回类对象指针this
// 在正式赋值前，为避免内存浪费，被赋值的对象中的动态内存需要使用delete运算符删除
	if (this == &s)
		return *this;
	delete[] str;
	len = s.len;
	str = new char[len + 1];
	std::strcpy(str, s.str);
	return *this;
}

String& String::operator=(const char* s)
{
// 由于参数为C字符串，所以必定不可能是自己对自己赋值
// 同样需要先释放原有的内存
	delete[] str;
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	return *this;
}

char& String::operator[](int i)
{
// 使用中括号来访问String对象中的字符
// 实际使用时，第一个参数位于两个中括号之前，另一个参数位于两个中括号之间
// 例如在寻找String对象opera[4]时，将会查找函数String::operator[](4)，若找到则调用
	return str[i];
}

const char& String::operator[](int i) const
{
// 在重载时，C++提供区分常量和非常量函数的特征标，因此可以提供这样一个仅供const String对象使用的operator[]()版本
// 对于cout，cin等变量来说，需要输入一个const值，而若没有定义这样一个[]的重载，则输出opera[4]这样的变量时
// 是一个可以修改的左值，是无法被某些函数接受的，因此重定义了这样一个函数
	return str[i];
}
// ============================================


// ===============通过友元函数重载================
bool operator<(const String& st1, const String& st2)
{
// 执行比较操作的方法有3个。如果按字母顺序，最简单的方式是使用现成的运算符strcmp
// strcmp()函数中，若第一个参数按字母排序在第二个参数之前，则返回一个负值
// strcmp()函数中，若第一个参数按字母排序在第二个参数之后，则返回一个正值
// strcmp()函数中，若第一个参数按字母排序与第二个参数相同，则返回零
// 将比较函数作为友元函数，可以使得String对象可以和C字符串进行比较
	return std::strcmp(st1.str, st2.str) < 0;
}

bool operator>(const String& st1, const String& st2)
{
	return std::strcmp(st1.str, st2.str) > 0;
}

bool operator==(const String& st1, const String& st2)
{
	return std::strcmp(st1.str, st2.str) == 0;
}

std::ostream& operator <<(ostream& os, const String& st)
{
	os << st.str;
	return os;
}

std::istream& operator >>(istream& is, String& st)
{
// istream操作方法
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);
	if (is)
		st = temp;
	while (is && is.get() != '\n')
		continue;
	return is;
}
// ============================================


// ==================静态函数===================
int String::HowMany()
{
// 可以将成员函数声明为静态的（函数声明必须包含关键字static，但如果函数定义是独立的，则其中不能包含关键字static），这样做会带来两个后果
// 1. 不能通过对象调用该静态成员函数，实际上静态成员函数甚至不能使用this指针。
//	如果静态成员函数实在公有部分声明的，则可以使用类名和作用解析域来调用它。int count = String::HowMany()
// 2. 由于静态成员函数不与特定的对象相关联，因此只能使用静态数据成员，而不能使用其他非静态数据成员
	return num_strings;
}
// ============================================

