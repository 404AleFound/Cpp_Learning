#include <iostream>
#include <new>

const int BUF = 512;
const int N = 5;

char buffer[BUF];

int main() {
    using namespace std;
    double* pd1, * pd2;
    int i;
    
    // 常规new的地址为自动分配的 
    // 常规new将数组pd1放在很远的地方，其地址为00000198C5D42DD0，位于动态管理的堆中
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];

    // 定位new运算符使用传递给它的地址，它不跟踪哪些内存单元被使用，也不查找为使用的内存块。
    // 这将一些内存管理的任务交给了程序员
    // 这里传递的地址为一个静态数组的地址，故该块内存位于栈区    
    pd2 = new (buffer) double[N];

    // 为地址上的变量赋值 
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 20.0 * i;

	// 强制类型转换(void*)，对于char* cin将输出一个字符串 
    cout << "Memory addresses:\n" << " heap: " << pd1
        << "static: " << (void*)buffer << endl;
    
    // 输出pd1和pd2这两块地址中的内容 
    cout << "Memory contents:\n";
    for (int i = 0; i < N; i++) {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }

	// 新创建两个指向double的指针 
    cout << "\nCalling new and placement new a second time:\n";
    double* pd3, * pd4;
    
    // 重复拉取内存，赋值，输出的操作 
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

	// 重新拉取内存，pd2移动一定距离 
    cout << "\nCalling new and placement new a third time:\n";
    delete[] pd1;
    pd1 = new double[N];
    pd2 = new (buffer + N * sizeof(double)) double[N];
    
    // 定位在从数组buffer开头算起偏移一定距离的内存处 
    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 60.0 * i;
    cout << "Memory contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    
    // 没有使用delete运算符清除pd2和pd4，因为buffer数组对应的内存位于静态内存处，在栈区
    // 程序员通过定位new运算符将pd2和pd4指向一静态内存处，故对于pd2和pd4无需使用delete运算符，其遵循栈区内存管理规则
    delete[] pd1;
    delete[] pd3;

    return 0;
}
