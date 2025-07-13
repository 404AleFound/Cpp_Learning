// autoscp.cpp -- illustrating scope of automatic variables

#include <iostream>

void oil(int x);
int main()
    
{
    using namespace std;
    int texas = 31;
    int year = 2011;
    
    cout << "t1: In main(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t1: In main(), year = " << year << ", &year = ";
    cout << &year << endl;
    
    oil(texas);
    
    cout << "t2: In main(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t2: In main(), year = " << year << ", &year = ";
    cout << &year << endl;

    return 0;
}

void oil(int x)
{
    using namespace std;
    int texas = 5;

    cout << "t1: In oil(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t1: In oil(), x = " << x << ", &x = ";
    cout << &x << endl;

    {
        int texas = 113;
        cout << "In block, texas = " << texas << ", &texas = ";
        cout << &texas << endl;
        cout << "In block, x = " << x << ", &x = ";
        cout << &x << endl;
    }

    cout << "t2: In oil(), texas = " << texas << ", &texas = ";
    cout << &texas << endl;
    cout << "t2: In oil(), x = " << x << ", &x = ";
    cout << &x << endl;

}


// 解析：
// 1. 当在同一段代码块中，存在两个名称相同，但是作用域不同的变量时。新的变量会覆盖旧的变量，在该段代码块结束后，新变量小时，变量自动回到旧变量。
// 2. 自动变量仅仅在创建时的代码块中可用，不同代码块之间不能互用自动变量。

// 输出：
// t1: In main(), texas = 31, &texas = 000000A7040FFB44
// t1: In main(), year = 2011, &year = 000000A7040FFB64
// t1: In oil(), texas = 5, &texas = 000000A7040FFA04
// t1: In oil(), x = 31, &x = 000000A7040FFB20
// In block, texas = 113, &texas = 000000A7040FFA24
// In block, x = 31, &x = 000000A7040FFB20
// t2: In oil(), texas = 5, &texas = 000000A7040FFA04
// t2: In oil(), x = 31, &x = 000000A7040FFB20
// t2: In main(), texas = 31, &texas = 000000A7040FFB44
// t2: In main(), year = 2011, &year = 000000A7040FFB64
