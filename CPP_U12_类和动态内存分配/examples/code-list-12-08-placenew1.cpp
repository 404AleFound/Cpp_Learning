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
// 申请一块512字节的动态内存，指针buffer指向第一块内存处
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

// delete pc3错误
// delete可以和常规new运算符配合使用，但是不能和new定位运算符配合使用
// 由于pc1和pc3并没有接收到new运算符返回的地址，
// 另一方面pc1，pc3和buffer指向同一块内存，而该内存是通过new[]，创建的，因此也不能使用delete
// 最后，new/delete知道使用buffer申请了一块内存，但是不知道定位运算符new对其进行了何种操作，故应当释放buffer
	delete pc2;
	delete pc4;
	delete[] buffer;
	cout << "Done.\n";
	return 0;
}