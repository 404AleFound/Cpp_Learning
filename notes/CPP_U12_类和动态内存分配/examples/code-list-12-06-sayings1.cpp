// saying1.cpp -- a test file for string1.h and string1.cpp

#include<iostream>
#include"string1.h"

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
		<< " short sayings < empty line to quit>:\n";
	String sayings[ArSize];
	char temp[MaxLen];
	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		while (cin )
	}
}