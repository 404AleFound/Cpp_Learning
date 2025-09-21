// strngbad.cpp -- StringBad class methods
#define _CRT_SECURE_NO_WARNINGS
# include <cstring>
# include "strngbad.h"
using std::cout;

// 初始化静态类成员
// 注意不要在类声明中初始化静态成员变量，这是因为声明应当仅仅描述如何分配内存，而不应当真分配内存
// 如果在声明中对静态成员变量进行了初始化，则当头文件被包括在多个文件中，会出现多个初始化语句副本，可能引发错误
// 对于静态类成员可以在声明之外使用单独语句进行初始化，这是因为静态成员的持续性要长于类对象
// 注意，初始化静态类成员时需要声明其类型，使用作用域运算符，但不必使用关键字static
int StringBad::num_strings = 0;


// 定义类方法
StringBad::StringBad(const char* s)
{
// 接受一个常规C字符串来初始化类对象
// 用于存储字符串的类成员仅仅是一个指针，及字符串并不保存在对象中，仅仅保存了指向其的指针
// strlen()函数在计数时忽略空字符，因此实际字符串长度要加1
// 每创建一个新对象，共享变量num_strings的值将增加1，从而记录String对象的总数
// len = std::strlen(s);
// str = new char[len + 1];
// 上述两条语句不能用len=str代替，因为这里使用的是引用参数，所以这个类对象的指针会指向外部传入的字符串处，并没有创建副本
// 对于新创建的对象，我们希望其能有属于自己的数据，而非依赖于其他对象

	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;
	cout << num_strings << ": \"" << str << "\"object created\n";
}

StringBad::StringBad()
{
// 构造函数与通过C字符串的构造函数类似，区别在于其提供了一个默认的字符串C++
// 每创建一个新对象，共享变量num_strings的值将增加1，从而记录String对象的总数

	len = 4;
	str = new char[4];
	std::strcpy(str, "C++");
	num_strings++;
	cout << num_strings << ": \"" << str << "\"default object created\n";
}

StringBad::~StringBad()
{
// 每删除一个对象，共享变量num_strings的值将减少1，从而记录String对象的总数
// 该析构函数使用字符串输出的方式，显示指出自身何时被调用
// 当StringBad对象过期时，str指针对应的那块数组也将过期，因为对于动态存储的成员，在此时使用delete释放动态内存
// 析构函数可以删除指向str指针，但不能删除str对应那块内存上的数据

	cout << "\"" << str << "\" object deleted, ";
	--num_strings;
	cout << num_strings << " left\n";
	delete[] str;
}

// 定义友元函数
std::ostream& operator << (std::ostream& os, const StringBad& st)
{
	os << st.str;
	return os;
}