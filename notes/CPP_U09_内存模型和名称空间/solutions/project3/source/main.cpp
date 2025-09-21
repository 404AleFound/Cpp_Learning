#include <iostream>
#include <cstring>
#include <new>

const int BUF = 512;
const int N = 2;

struct chaff
{
    char dross[20];
    int slag;
};

// 在静态存储区申请一块缓冲区 
chaff buffer1[BUF];
// 在堆区申请一块缓冲区 
chaff* buffer2 = new chaff[BUF];

int main()
{
	using namespace std;
	// 使用静态存储区缓冲区 
	chaff* pf1 = new (buffer1) chaff[N];
	// 使用循环赋值 
	for (int i = 0; i < N; i++) {
		strcpy(pf1[i].dross,"glasses");
		pf1[i].slag = i;
	}
	// 使用循环显示 
	for (int i = 0; i < N; i++) {
		cout << "dross: " << pf1[i].dross << ", " << "slag: " << pf1[i].slag << endl;
	}
	
	// 使用堆区缓冲区 
	chaff* pf2 = new (buffer2) chaff [N];
	// 使用循环赋值 
	for (int i = 0; i < N; i++) {
		strcpy(pf2[i].dross,"grass");
		pf2[i].slag = i;
	}
	// 使用循环显示 
	for (int i = 0; i < N; i++) {
		cout << "dross: " << pf2[i].dross << ", " << "slag: " << pf2[i].slag << endl;
	}

	delete [] buffer2;
	
 } 
