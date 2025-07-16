// palcenew1.cpp -- new, placement new, no delete
#include<iostream>
#include<new>
#include<string>

using namespace std;

const int BUF = 512;

class JustTesting
{
private:
	string words;
	int number;
public:
	JustTesting(const string & s = "Just Testing", int n = 0)
	{
		words = s; 
		number = n; 
		cout << words << " constructed\n";
	}

	~JustTesting()
	{
		cout << words << " destroyed\n";
	}

	void Show() const
	{
		cout << words << ", " << number << endl;
	}
};

int main()
{
// ����һ��512�ֽڵĶ�̬�ڴ棬ָ��bufferָ���һ���ڴ洦
	char* buffer = new char[BUF];
	JustTesting* pc1, * pc2;

	pc1 = new (buffer) JustTesting;
	pc2 = new JustTesting("Heap1", 20);

	cout << "Memory block addresses:\n" << "buffer: "
		<< (void*)buffer << " heap: " << pc2 << endl;
	cout << "Memory contents:\n";
	cout << pc1 << ": ";
	pc1->Show();
	cout << pc2 << ": ";
	pc2->Show();

	JustTesting* pc3, * pc4;
	pc3 = new (buffer) JustTesting("Bad Idea", 6);
	pc4 = new JustTesting("Heap2", 10);

	cout << "Memory contents:\n";
	cout << pc3 << ": ";
	pc3->Show();
	cout << pc4 << ": ";
	pc4->Show();

// delete pc3����
// delete���Ժͳ���new��������ʹ�ã����ǲ��ܺ�new��λ��������ʹ��
// ����pc1��pc3��û�н��յ�new��������صĵ�ַ��
// ��һ����pc1��pc3��bufferָ��ͬһ���ڴ棬�����ڴ���ͨ��new[]�������ģ����Ҳ����ʹ��delete
// ���new/delete֪��ʹ��buffer������һ���ڴ棬���ǲ�֪����λ�����new��������˺��ֲ�������Ӧ���ͷ�buffer
	delete pc2;
	delete pc4;
	delete[] buffer;
	cout << "Done.\n";
	return 0;
}