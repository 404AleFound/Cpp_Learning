// vegnews.cpp -- using new and delete with classes
// a test file for strngbad.h and strngbad.cpp

#include<iostream>
#include"strngbad.h"

using std::cout;

void callme1(StringBad&);
void callme2(StringBad);

int main()
{
	using std::endl;
	{
		cout << "Starting an inner block.\n";
		StringBad headline1("Celert Stalks at Midnight");
		StringBad headline2("Lettuce Prey");
		StringBad sports("Spianch Leaves Bowl for Dollars");
		cout << "headline1: " << headline1 << endl;
		cout << "headline2: " << headline2 << endl;
		cout << "sports: " << sports << endl;
		callme1(headline1);
		cout << "headline1: " << headline1 << endl;
		callme2(headline2);
// 这里callme2()按值传递headline2从而导致析构函数被调用，使得headline2中的数据被删除
// 注意由于复制构造函数使得sb.str = headline2.str，在离开函数后析构函数清除了sb.str对应的那块内存上的数据
// 而由于是浅复制，headline2.str与sb.str指向同一块内存，从而导致headline2.str对应的数据失踪，变为乱码
// 即headline2.str指向的内存被sb的析构函数一并释放了，同一块内存被释放了两次。
// 解决方法是定义一个显示复制构造函数，替代默认版本，采用深复制代替浅复制。
		cout << "headline2: " << headline2 << endl;
		cout << "Initialize one object to another:\n";
		StringBad sailor = sports;
		cout << "sailor: " << sailor << endl;
		cout << "Assign one object to another:\n";
		StringBad knot;
		knot = headline1;
	}

	cout << "End of main()\n";

	return 0;
}

void callme1(StringBad& rsb)
{
	cout << "String passed by reference:\n";
	cout << " \"" << rsb << "\"\n";
}

void callme2(StringBad sb)
{
// 这里参数为按值传递，那么sb的构造将使用类默认的复制构造函数，而非自定义的构造函数
// 默认的复制构造函数不会对静态成员变量加1
	cout << "String passed by value:\n";
	cout << " \"" << sb << "\"\n";
// sb的作用域到此为止，因此sb将会调用析构函数释放

}