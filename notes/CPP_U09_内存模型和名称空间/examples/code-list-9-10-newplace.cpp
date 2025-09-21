#include <iostream>
#include <new>

const int BUF = 512;
const int N = 5;

char buffer[BUF];

int main()
{
    using namespace std;
    double* pd1, * pd2;
    int i;
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];
    // 常规new将数组pd1放在很远的地方，其地址为00000198C5D42DD0，位于动态管理的堆中
    pd2 = new (buffer) double[N];
    // 定位new运算符使用传递给它的地址，它不跟踪哪些内存单元被使用，也不查找为使用的内存块。
    // 这将一些内存管理的任务将给了程序员
    for (i = 0; i < N; i++
        pd2[i] = pd1[i] = 1000 + 20.0 * i;

    cout << "Memory addresses:\n" << " heap: " << pd1
        << "static: " << (void*)buffer << endl;
    // 强制类型转换(void*)，对于char* cin将输出一个字符串 
    
    cout << "Memory contents:\n";
    for (int i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }

    cout << "\nCalling new and placement new a second time:\n";
    double* pd3, * pd4;
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
    delete[] pd1;
    delete[] pd3;
    // 没有使用delete运算符清除pd2和pd4，因为buffer数组对应的内存位于静态内存处，在栈区
    // 程序员通过定位new运算符将pd2和pd4指向一静态内存处，故对于pd2和pd4无需使用delete运算符，其遵循栈区内存管理规则
    return 0;
}

// 返回如下：
// Calling new and placement new:
// Memory addresses:
//  heap: 00000198C5D42DD0static: 00007FF6449AF4A0
// Memory contents:
// 1000 at 00000198C5D42DD0; 1000 at 00007FF6449AF4A0
// 1020 at 00000198C5D42DD8; 1020 at 00007FF6449AF4A8
// 1040 at 00000198C5D42DE0; 1040 at 00007FF6449AF4B0
// 1060 at 00000198C5D42DE8; 1060 at 00007FF6449AF4B8
// 1080 at 00000198C5D42DF0; 1080 at 00007FF6449AF4C0

// Calling new and placement new a second time:
// Memory contents:
// 1000 at 00000198C5D42DD0; 1000 at 00007FF6449AF4A0
// 1040 at 00000198C5D42DD8; 1040 at 00007FF6449AF4A8
// 1080 at 00000198C5D42DE0; 1080 at 00007FF6449AF4B0
// 1120 at 00000198C5D42DE8; 1120 at 00007FF6449AF4B8
// 1160 at 00000198C5D42DF0; 1160 at 00007FF6449AF4C0

// Calling new and placement new a third time:
// Memory contents:
// 1000 at 00000198C5D47F60; 1000 at 00007FF6449AF4C8
// 1060 at 00000198C5D47F68; 1060 at 00007FF6449AF4D0
// 1120 at 00000198C5D47F70; 1120 at 00007FF6449AF4D8
// 1180 at 00000198C5D47F78; 1180 at 00007FF6449AF4E0
// 1240 at 00000198C5D47F80; 1240 at 00007FF6449AF4E8