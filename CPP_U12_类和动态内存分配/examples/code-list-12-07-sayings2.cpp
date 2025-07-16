// saying1.cpp -- a test file for string1.h and string1.cpp

#include<iostream>
#include"code-list-12-04-string1.h"

const int ArSize = 10;
const int MaxLen = 81;

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	String name;
	cout << "Hi, what's your name?\n";
	cin >> name;

	cout << name << ", please enter up to " << ArSize
		<< " short sayings <empty line to quit>:\n";
	String sayings[ArSize];
	char temp[MaxLen];
	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		// 检查是否在行末，若否则一直cin.get()直到行末为止
		// 经典的读一行并丢弃剩余字=字符的方法
		while (cin && cin.get() != '\n')
			continue;
		// 检查是否为空行
		if (!cin || temp[0] == '\0')
			break;
		else

			sayings[i] = temp;
	}

	int total = i;

	if (total > 0)
	{
		cout << "Here are your sayings:\n";
		for (i = 0; i < total; i++)
			cout << sayings[i][0] << ": " << sayings[i] << endl;

		String* shortest = &sayings[0];
		String* first = &sayings[0];
		for (i = 0; i < total; i++)
		{
			if (sayings[i].length() < shortest->length())
				shortest = &sayings[i];
			if (sayings[i] < *first)
				first = &sayings[i];
		}
		cout << "Shortest saying:\n" << *shortest << endl;
		cout << "First alphabetically:\n" << *first << endl;
		cout << "This pragrams used " << String::HowMany() << "String objects, Bye.\n";
		int choice = rand() % total;
// 为对象分配内存，程序没有为num_string成员分配内存，因为其为静态成员变量
// 为成员变量char指针和int变量分配内存
// 通过构造函数为char指针指向的字符串分配地址
		String* favorite = new String(sayings[choice]);
		cout << "My favorite saying:\n" << *favorite << endl;
		delete favorite;
// 仅仅释放保存str指针和len成员的空间，并不释放str指向的内存
// str指针指向的内存通过析构函数释放
	}
	else
		cout << "No input!";
	return 0;
}