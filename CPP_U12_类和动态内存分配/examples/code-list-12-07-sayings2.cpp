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
		// ����Ƿ�����ĩ��������һֱcin.get()ֱ����ĩΪֹ
		// ����Ķ�һ�в�����ʣ����=�ַ��ķ���
		while (cin && cin.get() != '\n')
			continue;
		// ����Ƿ�Ϊ����
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
// Ϊ��������ڴ棬����û��Ϊnum_string��Ա�����ڴ棬��Ϊ��Ϊ��̬��Ա����
// Ϊ��Ա����charָ���int���������ڴ�
// ͨ�����캯��Ϊcharָ��ָ����ַ��������ַ
		String* favorite = new String(sayings[choice]);
		cout << "My favorite saying:\n" << *favorite << endl;
		delete favorite;
// �����ͷű���strָ���len��Ա�Ŀռ䣬�����ͷ�strָ����ڴ�
// strָ��ָ����ڴ�ͨ�����������ͷ�
	}
	else
		cout << "No input!";
	return 0;
}