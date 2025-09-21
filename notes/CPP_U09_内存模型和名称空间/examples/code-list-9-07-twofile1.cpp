// twofile1.cpp -- variables with external and internal linkage
// link with code-list-9-08-twofile2.cpp

#include <iostream>

int tom = 3;
int dick = 30;
static int harry = 300;

void remote_access();

int main()
{
	using namespace std;
    cout << "main() reports the following addresses:\n";
    cout << &tom << " = &tom, " << &dick << " = &dick, ";
    cout << &harry << " = &harry\n";
    remote_access();
    return 0;
}

// 输出如下：
// main() reports the following addresses:
// 00007FF6F6F5E00C = &tom, 00007FF6F6F5E010 = &dick, 00007FF6F6F5E014 = &harry
// remote_access() reports the following addresses:
// 00007FF6F6F5E00C = &tom, 00007FF6F6F5E004 = &dick, 00007FF6F6F5E000 = &harry