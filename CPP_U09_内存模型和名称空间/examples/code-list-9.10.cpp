#include <iostream>
#include <new>

const int BUF = 512;
const int N = 5;

char buffer[BUF];

int main() {
    using namespace std;
    double* pd1, * pd2;
    int i;
    
    // ����new�ĵ�ַΪ�Զ������ 
    // ����new������pd1���ں�Զ�ĵط������ַΪ00000198C5D42DD0��λ�ڶ�̬����Ķ���
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];

    // ��λnew�����ʹ�ô��ݸ����ĵ�ַ������������Щ�ڴ浥Ԫ��ʹ�ã�Ҳ������Ϊʹ�õ��ڴ�顣
    // �⽫һЩ�ڴ��������񽻸��˳���Ա
    // ���ﴫ�ݵĵ�ַΪһ����̬����ĵ�ַ���ʸÿ��ڴ�λ��ջ��    
    pd2 = new (buffer) double[N];

    // Ϊ��ַ�ϵı�����ֵ 
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 20.0 * i;

	// ǿ������ת��(void*)������char* cin�����һ���ַ��� 
    cout << "Memory addresses:\n" << " heap: " << pd1
        << "static: " << (void*)buffer << endl;
    
    // ���pd1��pd2�������ַ�е����� 
    cout << "Memory contents:\n";
    for (int i = 0; i < N; i++) {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }

	// �´�������ָ��double��ָ�� 
    cout << "\nCalling new and placement new a second time:\n";
    double* pd3, * pd4;
    
    // �ظ���ȡ�ڴ棬��ֵ������Ĳ��� 
    pd3 = new double[N];
    pd4 = new (buffer) double[N];
    for (i = 0; i < N; i++)
        pd3[i] = pd4[i] = 1000 + 40.0 * i;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd3[i] << " at " << &pd1[i] << "; ";
        cout << pd4[i] << " at " << &pd2[i] << endl;
    }

	// ������ȡ�ڴ棬pd2�ƶ�һ������ 
    cout << "\nCalling new and placement new a third time:\n";
    delete[] pd1;
    pd1 = new double[N];
    pd2 = new (buffer + N * sizeof(double)) double[N];
    
    // ��λ�ڴ�����buffer��ͷ����ƫ��һ��������ڴ洦 
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 60.0 * i;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    
    // û��ʹ��delete��������pd2��pd4����Ϊbuffer�����Ӧ���ڴ�λ�ھ�̬�ڴ洦����ջ��
    // ����Աͨ����λnew�������pd2��pd4ָ��һ��̬�ڴ洦���ʶ���pd2��pd4����ʹ��delete�����������ѭջ���ڴ�������
    delete[] pd1;
    delete[] pd3;

    return 0;
}
