// file1.cpp
#include <iostream>
#include "coordin.h"
// 使用""则优先在工程文件中查找，若找不到，则之后再系统变量中查找。
// 使用<>仅在系统变量中查找。
using namespace std;

int main()
{
    rect rplace;
    polar pplace;

    std::cout << "Enter the x and y values: ";
    while (std::cin >> rplace.x >> rplace.y)
    {
        pplace = rect2polar(rplace);
        show_polar(pplace);
        std::cout << "Next two number (q to quit):";
    }
    std::cout << "Done.\n";
    return 0;
}