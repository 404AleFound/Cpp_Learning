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

// �ھ�̬�洢������һ�黺���� 
chaff buffer1[BUF];
// �ڶ�������һ�黺���� 
chaff* buffer2 = new chaff[BUF];

int main()
{
	using namespace std;
	// ʹ�þ�̬�洢�������� 
	chaff* pf1 = new (buffer1) chaff[N];
	// ʹ��ѭ����ֵ 
	for (int i = 0; i < N; i++) {
		strcpy(pf1[i].dross,"glasses");
		pf1[i].slag = i;
	}
	// ʹ��ѭ����ʾ 
	for (int i = 0; i < N; i++) {
		cout << "dross: " << pf1[i].dross << ", " << "slag: " << pf1[i].slag << endl;
	}
	
	// ʹ�ö��������� 
	chaff* pf2 = new (buffer2) chaff [N];
	// ʹ��ѭ����ֵ 
	for (int i = 0; i < N; i++) {
		strcpy(pf2[i].dross,"grass");
		pf2[i].slag = i;
	}
	// ʹ��ѭ����ʾ 
	for (int i = 0; i < N; i++) {
		cout << "dross: " << pf2[i].dross << ", " << "slag: " << pf2[i].slag << endl;
	}

	delete [] buffer2;
	
 } 
