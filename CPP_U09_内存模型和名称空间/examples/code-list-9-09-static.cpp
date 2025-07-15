// static.cpp -- using a static local variable
#include <iostream>

const int ArSize = 10;

void strcount(const char* str);

int main()
{
    using namespace std;
    char input[ArSize];
    char next;

    cout << "Enter a line:\n";
    cin.get(input, ArSize);
// cin.get(input, ArSize)将一直读取输入直到到达行尾或者读取了ArSize-1个字符为止。
// 它把换行符留在输入队列中。

    while (cin)
    {
        cin.get(next);
// 该程序使用cin.get(next)读取行输入后的字符。
        while (next != '\n')
            cin.get(next);
// 如果next是换行符则说明cin.get(input, ArSize)读取了整行；否则说明行中还有字符没有被读取。
// 随后，程序使用一个循环来丢弃余下的字符，不过可以修改代码，使得下一轮输入读取行中余下的字符。
        strcount(input);
        cout << "Enter next line (empty line to quit):\n";
// 程序在试图使用get(char*, int)读取空行时，将导致cin为false，以此来结束循环。
        cin.get(input, ArSize);
    }
    cout << "Bye\n";
    return 0;
}

void strcount(const char* str)
{
    using namespace std;
    static int total = 0;
// 静态变量total只在程序运行时被设置为0，
// 以后在两次函数调用之间，其值将保持不变，因此能够记录读取的字符总数。
    int count = 0;

    cout << "\"" << str << "\" contains ";
    while (*str++)//equal to while (*(str++))
        count++;
    total += count;
    cout << count << " characters\n";
    cout << total << " characters total\n";
}

// 输出如下：
// Enter a line:
// ffffffffffffffffffff
// "fffffffff" contains 9 characters
// 9 characters total
// Enter next line (empty line to quit):
// aaaaaaaaaaaaaaaaaaaaaaaa
// "aaaaaaaaa" contains 9 characters
// 18 characters total
// Enter next line (empty line to quit):
// ffffffffffffffff
// "fffffffff" contains 9 characters
// 27 characters total
// Enter next line (empty line to quit):
// aaaaaaaaaaaaaaaaaaaaaaaa
// "aaaaaaaaa" contains 9 characters
// 36 characters total
// Enter next line (empty line to quit):

// Bye